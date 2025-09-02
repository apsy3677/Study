/*
 * Atlassian Interview: Middleware Router
 * 
 * PROBLEM STATEMENT:
 * Implement a middleware router for web service that returns different strings based on path.
 * 
 * Basic Interface:
 * - addRoute(path: String, result: String): Unit
 * - callRoute(path: String): String
 * 
 * Example: Router.addRoute("/bar", "result") → Router.callRoute("/bar") returns "result"
 * 
 * Scale-ups:
 * 1. Wildcards using ordered checking: Support "*" in paths with priority-based matching
 * 2. Path Parameters: Support "{param}" in paths and extract parameter values
 * 
 * SOLUTION APPROACH:
 * 1. Use Trie (prefix tree) for efficient path matching
 * 2. RouteNode structure: exact children, wildcard child, parameter child
 * 3. Matching priority: exact match > parameter match > wildcard match
 * 4. For parameters: extract parameter names and values during matching
 * 5. Advanced: middleware support with function chains
 * 6. Ordered checking: store routes in insertion order for deterministic wildcard behavior
 * 
 * Time Complexity: O(1) for exact match, O(n) for wildcard/param matching
 * Space Complexity: O(n) where n is number of routes
 */

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

class RouteNode {
public:
    string result;
    bool hasResult;
    unordered_map<string, RouteNode*> children;
    RouteNode* wildcardChild;
    RouteNode* paramChild;
    string paramName;
    
    RouteNode() : hasResult(false), wildcardChild(nullptr), paramChild(nullptr) {}
    
    ~RouteNode() {
        for (auto& child : children) {
            delete child.second;
        }
        delete wildcardChild;
        delete paramChild;
    }
};

class MiddlewareRouter {
private:
    RouteNode* root;
    vector<pair<string, string>> orderedRoutes; // For wildcard priority checking
    
    vector<string> splitPath(const string& path) {
        vector<string> segments;
        stringstream ss(path);
        string segment;
        
        while (getline(ss, segment, '/')) {
            if (!segment.empty()) {
                segments.push_back(segment);
            }
        }
        
        return segments;
    }
    
    bool isWildcard(const string& segment) {
        return segment == "*";
    }
    
    bool isParam(const string& segment) {
        return segment.length() > 2 && segment[0] == '{' && segment.back() == '}';
    }
    
    string extractParamName(const string& segment) {
        return segment.substr(1, segment.length() - 2);
    }
    
public:
    MiddlewareRouter() {
        root = new RouteNode();
    }
    
    ~MiddlewareRouter() {
        delete root;
    }
    
    // Part (a): Basic exact matching
    void addRoute(const string& path, const string& result) {
        vector<string> segments = splitPath(path);
        RouteNode* current = root;
        
        for (const string& segment : segments) {
            if (isWildcard(segment)) {
                if (!current->wildcardChild) {
                    current->wildcardChild = new RouteNode();
                }
                current = current->wildcardChild;
            } else if (isParam(segment)) {
                if (!current->paramChild) {
                    current->paramChild = new RouteNode();
                    current->paramChild->paramName = extractParamName(segment);
                }
                current = current->paramChild;
            } else {
                if (current->children.find(segment) == current->children.end()) {
                    current->children[segment] = new RouteNode();
                }
                current = current->children[segment];
            }
        }
        
        current->result = result;
        current->hasResult = true;
        
        // Store for ordered checking (Scale Up 1)
        orderedRoutes.push_back({path, result});
    }
    
    string callRoute(const string& path) {
        vector<string> segments = splitPath(path);
        unordered_map<string, string> params;
        
        string result = findRoute(root, segments, 0, params);
        
        // If path parameters were found, you could return them too
        // For now, just return the result
        return result;
    }
    
    // Scale Up 2: Path parameters
    pair<string, unordered_map<string, string>> callRouteWithParams(const string& path) {
        vector<string> segments = splitPath(path);
        unordered_map<string, string> params;
        
        string result = findRoute(root, segments, 0, params);
        
        return {result, params};
    }
    
private:
    string findRoute(RouteNode* node, const vector<string>& segments, int index, 
                    unordered_map<string, string>& params) {
        if (index == segments.size()) {
            return node->hasResult ? node->result : "NOT_FOUND";
        }
        
        const string& segment = segments[index];
        
        // 1. Try exact match first (highest priority)
        if (node->children.find(segment) != node->children.end()) {
            string result = findRoute(node->children[segment], segments, index + 1, params);
            if (result != "NOT_FOUND") {
                return result;
            }
        }
        
        // 2. Try parameter match
        if (node->paramChild) {
            params[node->paramChild->paramName] = segment;
            string result = findRoute(node->paramChild, segments, index + 1, params);
            if (result != "NOT_FOUND") {
                return result;
            }
            params.erase(node->paramChild->paramName); // Backtrack
        }
        
        // 3. Try wildcard match (lowest priority)
        if (node->wildcardChild) {
            string result = findRoute(node->wildcardChild, segments, index + 1, params);
            if (result != "NOT_FOUND") {
                return result;
            }
        }
        
        return "NOT_FOUND";
    }
    
public:
    // Scale Up 1: Ordered wildcard checking
    string callRouteWithOrdering(const string& path) {
        // For ordered checking, we'll iterate through routes in order they were added
        for (const auto& route : orderedRoutes) {
            if (matchesPattern(route.first, path)) {
                return route.second;
            }
        }
        return "NOT_FOUND";
    }
    
private:
    bool matchesPattern(const string& pattern, const string& path) {
        vector<string> patternSegments = splitPath(pattern);
        vector<string> pathSegments = splitPath(path);
        
        if (patternSegments.size() != pathSegments.size()) {
            return false;
        }
        
        for (size_t i = 0; i < patternSegments.size(); i++) {
            const string& patternSeg = patternSegments[i];
            const string& pathSeg = pathSegments[i];
            
            if (patternSeg == "*" || isParam(patternSeg)) {
                continue; // Wildcard or parameter matches anything
            }
            
            if (patternSeg != pathSeg) {
                return false;
            }
        }
        
        return true;
    }
    
public:
    // Debugging and utility functions
    void printAllRoutes() {
        cout << "\n=== All Registered Routes ===" << endl;
        for (const auto& route : orderedRoutes) {
            cout << route.first << " -> " << route.second << endl;
        }
    }
    
    void testRoute(const string& path) {
        cout << "\nTesting route: " << path << endl;
        
        // Test basic routing
        string result = callRoute(path);
        cout << "Basic result: " << result << endl;
        
        // Test with parameters
        auto paramResult = callRouteWithParams(path);
        cout << "With params result: " << paramResult.first << endl;
        if (!paramResult.second.empty()) {
            cout << "Parameters extracted:" << endl;
            for (const auto& param : paramResult.second) {
                cout << "  " << param.first << " = " << param.second << endl;
            }
        }
        
        // Test ordered checking
        string orderedResult = callRouteWithOrdering(path);
        cout << "Ordered result: " << orderedResult << endl;
    }
};

// Advanced router with middleware support
class AdvancedRouter {
private:
    MiddlewareRouter router;
    vector<function<bool(const string&)>> middlewares;
    
public:
    void addMiddleware(function<bool(const string&)> middleware) {
        middlewares.push_back(middleware);
    }
    
    void addRoute(const string& path, const string& result) {
        router.addRoute(path, result);
    }
    
    string callRoute(const string& path) {
        // Execute middlewares first
        for (const auto& middleware : middlewares) {
            if (!middleware(path)) {
                return "MIDDLEWARE_BLOCKED";
            }
        }
        
        return router.callRoute(path);
    }
    
    pair<string, unordered_map<string, string>> callRouteWithParams(const string& path) {
        // Execute middlewares first
        for (const auto& middleware : middlewares) {
            if (!middleware(path)) {
                return {"MIDDLEWARE_BLOCKED", {}};
            }
        }
        
        return router.callRouteWithParams(path);
    }
};

// Test functions
void testBasicRouting() {
    cout << "\n=== Testing Basic Routing ===" << endl;
    
    MiddlewareRouter router;
    
    router.addRoute("/bar", "result");
    router.addRoute("/foo", "foo_result");
    router.addRoute("/bar/baz", "nested_result");
    
    router.printAllRoutes();
    
    cout << "\nTesting exact matches:" << endl;
    cout << "callRoute(\"/bar\"): " << router.callRoute("/bar") << endl;
    cout << "callRoute(\"/foo\"): " << router.callRoute("/foo") << endl;
    cout << "callRoute(\"/bar/baz\"): " << router.callRoute("/bar/baz") << endl;
    cout << "callRoute(\"/nonexistent\"): " << router.callRoute("/nonexistent") << endl;
}

void testWildcardRouting() {
    cout << "\n=== Testing Wildcard Routing ===" << endl;
    
    MiddlewareRouter router;
    
    router.addRoute("/api/*", "api_wildcard");
    router.addRoute("/api/users", "specific_users");
    router.addRoute("/files/*/download", "file_download");
    
    router.printAllRoutes();
    
    router.testRoute("/api/users");      // Should match specific first
    router.testRoute("/api/posts");      // Should match wildcard
    router.testRoute("/files/123/download"); // Should match pattern
}

void testPathParameters() {
    cout << "\n=== Testing Path Parameters ===" << endl;
    
    MiddlewareRouter router;
    
    router.addRoute("/users/{id}", "user_profile");
    router.addRoute("/users/{id}/posts/{postId}", "user_post");
    router.addRoute("/api/v{version}/users", "versioned_api");
    
    router.printAllRoutes();
    
    router.testRoute("/users/123");
    router.testRoute("/users/456/posts/789");
    router.testRoute("/api/v2/users");
}

void testComplexRouting() {
    cout << "\n=== Testing Complex Routing ===" << endl;
    
    MiddlewareRouter router;
    
    // Mix of exact, wildcard, and parameter routes
    router.addRoute("/api/users/{id}", "user_by_id");
    router.addRoute("/api/users", "all_users");
    router.addRoute("/api/*/status", "status_wildcard");
    router.addRoute("/api/health/status", "health_status");
    router.addRoute("/files/{category}/*/download", "file_download");
    
    router.printAllRoutes();
    
    router.testRoute("/api/users");
    router.testRoute("/api/users/123");
    router.testRoute("/api/health/status");
    router.testRoute("/api/service/status");
    router.testRoute("/files/images/photo1.jpg/download");
}

void testAdvancedRouter() {
    cout << "\n=== Testing Advanced Router with Middleware ===" << endl;
    
    AdvancedRouter router;
    
    // Add authentication middleware
    router.addMiddleware([](const string& path) {
        cout << "Auth middleware checking: " << path << endl;
        // Block access to admin routes
        return path.find("/admin") == string::npos;
    });
    
    // Add logging middleware
    router.addMiddleware([](const string& path) {
        cout << "Logging middleware: Request to " << path << endl;
        return true; // Always allow
    });
    
    router.addRoute("/api/users", "users_list");
    router.addRoute("/admin/users", "admin_users");
    router.addRoute("/public/info", "public_info");
    
    cout << "\nTesting with middleware:" << endl;
    cout << "Result for /api/users: " << router.callRoute("/api/users") << endl;
    cout << "Result for /admin/users: " << router.callRoute("/admin/users") << endl;
    cout << "Result for /public/info: " << router.callRoute("/public/info") << endl;
}

int main() {
    testBasicRouting();
    testWildcardRouting();
    testPathParameters();
    testComplexRouting();
    testAdvancedRouter();
    
    return 0;
}
