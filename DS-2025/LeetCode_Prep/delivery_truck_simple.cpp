/**
 * Professional Delivery Truck Optimization Solution
 * 
 * Problem: Given delivery requests with time windows and truck capacity,
 * determine the maximum number of deliveries possible.
 * 
 * Time Complexity: O(n log n) - dominated by sorting
 * Space Complexity: O(n) - for event storage
 * 
 * Optimizations for fast compilation and execution:
 * - Minimal includes
 * - Efficient data structures
 * - Single-pass algorithms where possible
 * - Avoid unnecessary memory allocations
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class DeliveryOptimizer {
private:
    struct Delivery {
        int start, end, packages;
        int id;
        
        Delivery(int s, int e, int p, int i = 0) : start(s), end(e), packages(p), id(i) {}
    };

public:
    /**
     * Fast Event-Based Solution
     * Uses sweep line algorithm to track capacity changes
     * 
     * @param deliveries: vector of [start_time, end_time, package_count]
     * @param capacity: truck capacity
     * @return maximum deliveries possible
     */
    static int maxDeliveries(const std::vector<std::vector<int>>& deliveries, int capacity) {
        if (deliveries.empty() || capacity <= 0) return 0;
        
        // Convert to internal format and sort by end time (greedy approach)
        std::vector<Delivery> tasks;
        tasks.reserve(deliveries.size());
        
        for (int i = 0; i < deliveries.size(); ++i) {
            tasks.emplace_back(deliveries[i][0], deliveries[i][1], deliveries[i][2], i);
        }
        
        // Sort by end time for greedy selection
        std::sort(tasks.begin(), tasks.end(), [](const Delivery& a, const Delivery& b) {
            return a.end < b.end;
        });
        
        int count = 0;
        int lastEndTime = -1;
        
        for (const auto& task : tasks) {
            // Check if we can take this delivery (no overlap with previous)
            if (task.start >= lastEndTime && task.packages <= capacity) {
                count++;
                lastEndTime = task.end;
            }
        }
        
        return count;
    }
    
    /**
     * Advanced Solution: Handle overlapping deliveries
     * Uses event-based sweep line to track capacity usage
     */
    static int maxDeliveriesAdvanced(const std::vector<std::vector<int>>& deliveries, int capacity) {
        if (deliveries.empty() || capacity <= 0) return 0;
        
        // Create events for capacity tracking
        std::map<int, int> events; // time -> capacity_change
        
        std::vector<Delivery> tasks;
        tasks.reserve(deliveries.size());
        
        for (int i = 0; i < deliveries.size(); ++i) {
            tasks.emplace_back(deliveries[i][0], deliveries[i][1], deliveries[i][2], i);
        }
        
        // Sort by start time, then by package count (prefer smaller packages)
        std::sort(tasks.begin(), tasks.end(), [](const Delivery& a, const Delivery& b) {
            if (a.start != b.start) return a.start < b.start;
            return a.packages < b.packages;
        });
        
        std::vector<bool> selected(tasks.size(), false);
        int count = 0;
        
        for (int i = 0; i < tasks.size(); ++i) {
            if (selected[i]) continue;
            
            // Check if we can fit this delivery
            if (tasks[i].packages <= capacity) {
                // Simulate adding this delivery
                events.clear();
                events[tasks[i].start] += tasks[i].packages;
                events[tasks[i].end] -= tasks[i].packages;
                
                // Check all other selected deliveries for conflicts
                bool canAdd = true;
                int currentCapacity = 0;
                
                // Add already selected deliveries to events
                for (int j = 0; j < i; ++j) {
                    if (selected[j]) {
                        events[tasks[j].start] += tasks[j].packages;
                        events[tasks[j].end] -= tasks[j].packages;
                    }
                }
                
                // Check capacity constraints
                for (const auto& event : events) {
                    currentCapacity += event.second;
                    if (currentCapacity > capacity) {
                        canAdd = false;
                        break;
                    }
                }
                
                if (canAdd) {
                    selected[i] = true;
                    count++;
                }
            }
        }
        
        return count;
    }
    
    /**
     * Debug helper - visualize the solution
     */
    static void printSolution(const std::vector<std::vector<int>>& deliveries, 
                             const std::vector<int>& solution) {
        std::cout << "Selected deliveries:\n";
        for (int idx : solution) {
            std::cout << "Delivery " << idx << ": [" 
                     << deliveries[idx][0] << ", " << deliveries[idx][1] 
                     << "] packages: " << deliveries[idx][2] << "\n";
        }
    }
};

// Fast test cases for quick validation
namespace QuickTests {
    void runBasicTests() {
        std::cout << "Running quick validation tests...\n";
        
        // Test 1: Non-overlapping deliveries
        std::vector<std::vector<int>> test1 = {{1, 3, 2}, {4, 6, 3}, {7, 9, 1}};
        int result1 = DeliveryOptimizer::maxDeliveries(test1, 5);
        std::cout << "Test 1 (non-overlapping): " << result1 << " (expected: 3)\n";
        
        // Test 2: Capacity constraint
        std::vector<std::vector<int>> test2 = {{1, 3, 5}, {2, 4, 3}, {5, 7, 2}};
        int result2 = DeliveryOptimizer::maxDeliveries(test2, 4);
        std::cout << "Test 2 (capacity limit): " << result2 << " (expected: 2)\n";
        
        // Test 3: Overlapping deliveries
        std::vector<std::vector<int>> test3 = {{1, 4, 2}, {2, 5, 2}, {3, 6, 1}};
        int result3 = DeliveryOptimizer::maxDeliveriesAdvanced(test3, 3);
        std::cout << "Test 3 (overlapping): " << result3 << " (expected: 2)\n";
        
        std::cout << "Tests completed.\n\n";
    }
}

/**
 * Performance optimized main function
 * Uses fast I/O and minimal allocations
 */
int main() {
    // Fast I/O setup
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cout << "=== Professional Delivery Truck Optimizer ===\n\n";
    
    // Run quick tests first
    QuickTests::runBasicTests();
    
    // Example usage
    std::vector<std::vector<int>> deliveries = {
        {1, 3, 2},   // Delivery 0: time 1-3, 2 packages
        {2, 5, 3},   // Delivery 1: time 2-5, 3 packages  
        {4, 6, 1},   // Delivery 2: time 4-6, 1 package
        {5, 8, 2},   // Delivery 3: time 5-8, 2 packages
        {7, 9, 1}    // Delivery 4: time 7-9, 1 package
    };
    
    int capacity = 4;
    
    std::cout << "Problem Setup:\n";
    std::cout << "Truck capacity: " << capacity << " packages\n";
    std::cout << "Available deliveries:\n";
    for (int i = 0; i < deliveries.size(); ++i) {
        std::cout << "  " << i << ": [" << deliveries[i][0] << ", " 
                 << deliveries[i][1] << "] " << deliveries[i][2] << " packages\n";
    }
    
    // Solve using different approaches
    int simple = DeliveryOptimizer::maxDeliveries(deliveries, capacity);
    int advanced = DeliveryOptimizer::maxDeliveriesAdvanced(deliveries, capacity);
    
    std::cout << "\nResults:\n";
    std::cout << "Greedy approach (non-overlapping): " << simple << " deliveries\n";
    std::cout << "Advanced approach (overlapping): " << advanced << " deliveries\n";
    
    std::cout << "\nOptimization complete!\n";
    return 0;
}

/**
 * BUILD OPTIMIZATION NOTES:
 * 
 * 1. Compilation Speed Improvements:
 *    - Minimal includes (only necessary headers)
 *    - Avoid heavy template instantiations
 *    - Use forward declarations where possible
 *    - Disable unnecessary compiler features
 * 
 * 2. Runtime Performance:
 *    - Fast I/O with sync_with_stdio(false)
 *    - Reserve memory for vectors to avoid reallocations
 *    - Use emplace_back instead of push_back
 *    - Prefer range-based loops and const references
 * 
 * 3. Memory Efficiency:
 *    - Stack allocation over heap when possible
 *    - Clear containers when no longer needed
 *    - Use move semantics for large objects
 * 
 * 4. Compiler Flags for Fast Builds:
 *    - Use -O2 for good optimization without long compile times
 *    - Consider -j flag for parallel compilation
 *    - Use precompiled headers for repeated includes
 * 
 * Suggested compile command:
 * g++ -O2 -std=c++17 -Wall -Wextra delivery_truck_simple.cpp -o delivery_truck
 */