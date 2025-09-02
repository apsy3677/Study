/*
 * Atlassian Interview: Find the Closest Org for Target Employees
 * 
 * PROBLEM STATEMENT:
 * You are maintaining the Atlassian employee directory. At Atlassian, there are multiple 
 * groups, and each group can have one or more subgroups. Every employee is part of a group.
 * Design a system that can find the closest common parent group given a target set of 
 * employees in the organization.
 * 
 * Parts:
 * a) Basic implementation: Find closest common parent group for target employees
 * b) Handle shared groups/employees: Provide ONE closest common group when hierarchy 
 *    has shared groups or employees across different groups
 * c) Thread safety: Handle dynamic updates (4 methods) in separate threads while 
 *    getCommonGroupForEmployees is being called, ensuring latest state is always reflected
 * d) Single level: Company consists of single level groups with no subgroups
 * 
 * SOLUTION APPROACH:
 * 1. Use adjacency list representation for the hierarchy tree
 * 2. For each employee, maintain mapping to their direct group
 * 3. To find common ancestor:
 *    - Get all ancestor groups for each employee (BFS/DFS from employee to root)
 *    - Find intersection of ancestor sets
 *    - Return the deepest (closest to employees) common ancestor
 * 4. Thread safety: Use read-write locks (shared_mutex) for concurrent access
 * 5. Optimization: Cache ancestor paths and use depth-based comparison
 * 
 * Time Complexity: O(n + m) where n = employees, m = groups
 * Space Complexity: O(n + m)
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <mutex>
#include <shared_mutex>

using namespace std;

class Employee {
public:
    int id;
    string name;
    Employee(int id, string name) : id(id), name(name) {}
};

class Group {
public:
    int id;
    string name;
    vector<int> employees;
    vector<int> subGroups;
    int parentGroup;
    
    Group(int id, string name) : id(id), name(name), parentGroup(-1) {}
};

class OrgHierarchy {
private:
    unordered_map<int, Employee> employees;
    unordered_map<int, Group> groups;
    unordered_map<int, int> employeeToGroup; // employee_id -> group_id
    mutable shared_mutex rwLock; // For thread safety (part c)
    
public:
    // Part (a): Basic implementation
    void addEmployee(int empId, string name, int groupId) {
        unique_lock<shared_mutex> lock(rwLock);
        employees[empId] = Employee(empId, name);
        employeeToGroup[empId] = groupId;
        if (groups.find(groupId) != groups.end()) {
            groups[groupId].employees.push_back(empId);
        }
    }
    
    void addGroup(int groupId, string name, int parentId = -1) {
        unique_lock<shared_mutex> lock(rwLock);
        groups[groupId] = Group(groupId, name);
        if (parentId != -1) {
            groups[groupId].parentGroup = parentId;
            groups[parentId].subGroups.push_back(groupId);
        }
    }
    
    // Find closest common parent group
    int findClosestCommonGroup(vector<int>& employeeIds) {
        shared_lock<shared_mutex> lock(rwLock);
        
        if (employeeIds.empty()) return -1;
        
        // Get all groups for first employee
        unordered_set<int> ancestorGroups = getAncestorGroups(employeeIds[0]);
        
        // Find intersection with other employees' ancestor groups
        for (int i = 1; i < employeeIds.size(); i++) {
            unordered_set<int> currentAncestors = getAncestorGroups(employeeIds[i]);
            unordered_set<int> intersection;
            
            for (int groupId : ancestorGroups) {
                if (currentAncestors.count(groupId)) {
                    intersection.insert(groupId);
                }
            }
            ancestorGroups = intersection;
        }
        
        // Find the lowest level (closest) common group
        int closestGroup = -1;
        int maxDepth = -1;
        
        for (int groupId : ancestorGroups) {
            int depth = getDepthFromRoot(groupId);
            if (depth > maxDepth) {
                maxDepth = depth;
                closestGroup = groupId;
            }
        }
        
        return closestGroup;
    }
    
    // Part (b): Handle shared groups/employees
    vector<int> findAllClosestCommonGroups(vector<int>& employeeIds) {
        shared_lock<shared_mutex> lock(rwLock);
        
        vector<int> result;
        unordered_map<int, int> groupCount;
        
        // Count how many employees belong to each group (including ancestors)
        for (int empId : employeeIds) {
            unordered_set<int> ancestorGroups = getAncestorGroups(empId);
            for (int groupId : ancestorGroups) {
                groupCount[groupId]++;
            }
        }
        
        // Find groups that contain all employees
        int maxDepth = -1;
        for (auto& [groupId, count] : groupCount) {
            if (count == employeeIds.size()) {
                int depth = getDepthFromRoot(groupId);
                if (depth > maxDepth) {
                    maxDepth = depth;
                    result.clear();
                    result.push_back(groupId);
                } else if (depth == maxDepth) {
                    result.push_back(groupId);
                }
            }
        }
        
        return result;
    }
    
    // Part (d): Single level groups implementation
    int findCommonGroupSingleLevel(vector<int>& employeeIds) {
        shared_lock<shared_mutex> lock(rwLock);
        
        unordered_map<int, int> groupCount;
        
        for (int empId : employeeIds) {
            if (employeeToGroup.count(empId)) {
                groupCount[employeeToGroup[empId]]++;
            }
        }
        
        // Find group with all employees
        for (auto& [groupId, count] : groupCount) {
            if (count == employeeIds.size()) {
                return groupId;
            }
        }
        
        return -1; // No common group
    }
    
private:
    unordered_set<int> getAncestorGroups(int employeeId) {
        unordered_set<int> ancestors;
        
        if (employeeToGroup.count(employeeId)) {
            int currentGroup = employeeToGroup[employeeId];
            
            while (currentGroup != -1) {
                ancestors.insert(currentGroup);
                if (groups.count(currentGroup) && groups[currentGroup].parentGroup != -1) {
                    currentGroup = groups[currentGroup].parentGroup;
                } else {
                    break;
                }
            }
        }
        
        return ancestors;
    }
    
    int getDepthFromRoot(int groupId) {
        int depth = 0;
        int current = groupId;
        
        while (current != -1 && groups.count(current)) {
            if (groups[current].parentGroup != -1) {
                current = groups[current].parentGroup;
                depth++;
            } else {
                break;
            }
        }
        
        return depth;
    }
    
public:
    // Part (c): Thread-safe update methods
    void updateEmployeeGroup(int empId, int newGroupId) {
        unique_lock<shared_mutex> lock(rwLock);
        
        // Remove from old group
        if (employeeToGroup.count(empId)) {
            int oldGroupId = employeeToGroup[empId];
            auto& oldEmployees = groups[oldGroupId].employees;
            oldEmployees.erase(remove(oldEmployees.begin(), oldEmployees.end(), empId), 
                             oldEmployees.end());
        }
        
        // Add to new group
        employeeToGroup[empId] = newGroupId;
        groups[newGroupId].employees.push_back(empId);
    }
    
    void updateGroupParent(int groupId, int newParentId) {
        unique_lock<shared_mutex> lock(rwLock);
        
        // Remove from old parent
        if (groups[groupId].parentGroup != -1) {
            int oldParentId = groups[groupId].parentGroup;
            auto& subGroups = groups[oldParentId].subGroups;
            subGroups.erase(remove(subGroups.begin(), subGroups.end(), groupId), 
                          subGroups.end());
        }
        
        // Add to new parent
        groups[groupId].parentGroup = newParentId;
        if (newParentId != -1) {
            groups[newParentId].subGroups.push_back(groupId);
        }
    }
    
    void removeEmployee(int empId) {
        unique_lock<shared_mutex> lock(rwLock);
        
        if (employeeToGroup.count(empId)) {
            int groupId = employeeToGroup[empId];
            auto& groupEmployees = groups[groupId].employees;
            groupEmployees.erase(remove(groupEmployees.begin(), groupEmployees.end(), empId), 
                               groupEmployees.end());
            employeeToGroup.erase(empId);
        }
        
        employees.erase(empId);
    }
    
    void removeGroup(int groupId) {
        unique_lock<shared_mutex> lock(rwLock);
        
        if (groups.count(groupId)) {
            // Move employees to parent group if exists
            int parentId = groups[groupId].parentGroup;
            if (parentId != -1) {
                for (int empId : groups[groupId].employees) {
                    employeeToGroup[empId] = parentId;
                    groups[parentId].employees.push_back(empId);
                }
                
                // Move subgroups to parent
                for (int subGroupId : groups[groupId].subGroups) {
                    groups[subGroupId].parentGroup = parentId;
                    groups[parentId].subGroups.push_back(subGroupId);
                }
            }
            
            groups.erase(groupId);
        }
    }
    
    // Debug/Display functions
    void printHierarchy() {
        shared_lock<shared_mutex> lock(rwLock);
        
        cout << "\n=== Organization Hierarchy ===" << endl;
        for (auto& [groupId, group] : groups) {
            if (group.parentGroup == -1) { // Root groups
                printGroupRecursive(groupId, 0);
            }
        }
    }
    
private:
    void printGroupRecursive(int groupId, int level) {
        string indent(level * 2, ' ');
        cout << indent << "Group " << groupId << ": " << groups[groupId].name << endl;
        
        // Print employees
        for (int empId : groups[groupId].employees) {
            cout << indent << "  Employee " << empId << ": " << employees[empId].name << endl;
        }
        
        // Print subgroups
        for (int subGroupId : groups[groupId].subGroups) {
            printGroupRecursive(subGroupId, level + 1);
        }
    }
};

// Test function
void testOrgHierarchy() {
    OrgHierarchy org;
    
    // Create hierarchy
    org.addGroup(1, "Engineering", -1);
    org.addGroup(2, "Frontend", 1);
    org.addGroup(3, "Backend", 1);
    org.addGroup(4, "DevOps", 1);
    org.addGroup(5, "React Team", 2);
    org.addGroup(6, "Angular Team", 2);
    
    // Add employees
    org.addEmployee(101, "Alice", 5);
    org.addEmployee(102, "Bob", 5);
    org.addEmployee(103, "Charlie", 6);
    org.addEmployee(104, "David", 3);
    org.addEmployee(105, "Eve", 4);
    
    org.printHierarchy();
    
    // Test finding common groups
    vector<int> employees1 = {101, 102}; // Both in React team
    vector<int> employees2 = {101, 103}; // React and Angular - should find Frontend
    vector<int> employees3 = {101, 104}; // React and Backend - should find Engineering
    
    cout << "\nCommon group for employees {101, 102}: " << org.findClosestCommonGroup(employees1) << endl;
    cout << "Common group for employees {101, 103}: " << org.findClosestCommonGroup(employees2) << endl;
    cout << "Common group for employees {101, 104}: " << org.findClosestCommonGroup(employees3) << endl;
}

int main() {
    testOrgHierarchy();
    return 0;
}
