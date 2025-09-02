/*
 * Atlassian Interview: Popular Content
 * 
 * PROBLEM STATEMENT:
 * You are given a stream of content IDs along with associated actions to be performed.
 * Content examples: videos, pages, posts, etc. There are two actions:
 * - increasePopularity: increases content popularity by 1 (likes, comments)
 * - decreasePopularity: decreases content popularity by 1 (spam removal, unlike)
 * 
 * Requirements:
 * - Content IDs are positive integers
 * - Implement a class that returns the mostPopular content ID at any time
 * - If no content has popularity > 0, return -1
 * - Handle real-time updates efficiently
 * 
 * SOLUTION APPROACH:
 * 1. Use unordered_map<contentId, popularity> for content tracking
 * 2. Use map<popularity, set<contentId>> for efficient popularity-based queries
 * 3. For O(1) getMostPopular: cache mostPopularContent and maxPopularity
 * 4. Update logic:
 *    - Remove content from old popularity bucket
 *    - Add to new popularity bucket
 *    - Update cached max values intelligently
 * 5. Handle edge cases: content with 0 popularity (remove from tracking)
 * 
 * Time Complexity: O(log n) for operations, O(1) for getMostPopular (optimized)
 * Space Complexity: O(n)
 */

#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>

using namespace std;

class PopularContentTracker {
private:
    unordered_map<int, int> contentPopularity;  // content_id -> popularity_score
    map<int, set<int>> popularityToContents;    // popularity_score -> set of content_ids
    int maxPopularity;
    int mostPopularContent;
    bool hasPopularContent;
    
public:
    PopularContentTracker() : maxPopularity(0), mostPopularContent(-1), hasPopularContent(false) {}
    
    void increasePopularity(int contentId) {
        int oldPopularity = contentPopularity[contentId];
        int newPopularity = oldPopularity + 1;
        
        // Remove from old popularity bucket
        if (oldPopularity > 0) {
            popularityToContents[oldPopularity].erase(contentId);
            if (popularityToContents[oldPopularity].empty()) {
                popularityToContents.erase(oldPopularity);
            }
        }
        
        // Update content popularity
        contentPopularity[contentId] = newPopularity;
        popularityToContents[newPopularity].insert(contentId);
        
        // Update max popularity tracking
        if (newPopularity > maxPopularity || !hasPopularContent) {
            maxPopularity = newPopularity;
            mostPopularContent = contentId;
            hasPopularContent = true;
        } else if (newPopularity == maxPopularity && contentId < mostPopularContent) {
            // Tie-breaking: prefer smaller content ID
            mostPopularContent = contentId;
        }
    }
    
    void decreasePopularity(int contentId) {
        if (contentPopularity.count(contentId) == 0 || contentPopularity[contentId] <= 0) {
            return; // Content doesn't exist or already at 0 popularity
        }
        
        int oldPopularity = contentPopularity[contentId];
        int newPopularity = oldPopularity - 1;
        
        // Remove from old popularity bucket
        popularityToContents[oldPopularity].erase(contentId);
        if (popularityToContents[oldPopularity].empty()) {
            popularityToContents.erase(oldPopularity);
        }
        
        if (newPopularity > 0) {
            // Update content popularity
            contentPopularity[contentId] = newPopularity;
            popularityToContents[newPopularity].insert(contentId);
        } else {
            // Remove content with 0 or negative popularity
            contentPopularity.erase(contentId);
        }
        
        // Update max popularity tracking
        updateMaxPopularity();
    }
    
    int getMostPopularContent() {
        if (!hasPopularContent) {
            return -1;
        }
        
        // Double-check that our cached most popular content is still valid
        if (contentPopularity.count(mostPopularContent) == 0 || 
            contentPopularity[mostPopularContent] <= 0) {
            updateMaxPopularity();
        }
        
        return hasPopularContent ? mostPopularContent : -1;
    }
    
    // Get all content IDs with the highest popularity
    vector<int> getAllMostPopularContent() {
        if (!hasPopularContent) {
            return {};
        }
        
        updateMaxPopularity();
        
        if (popularityToContents.count(maxPopularity)) {
            vector<int> result(popularityToContents[maxPopularity].begin(), 
                             popularityToContents[maxPopularity].end());
            return result;
        }
        
        return {};
    }
    
    // Get top K popular content
    vector<pair<int, int>> getTopKPopularContent(int k) {
        vector<pair<int, int>> result; // {content_id, popularity}
        
        auto it = popularityToContents.rbegin();
        int count = 0;
        
        while (it != popularityToContents.rend() && count < k) {
            int popularity = it->first;
            if (popularity <= 0) break;
            
            for (int contentId : it->second) {
                if (count >= k) break;
                result.push_back({contentId, popularity});
                count++;
            }
            ++it;
        }
        
        return result;
    }
    
    // Get popularity of specific content
    int getPopularity(int contentId) {
        if (contentPopularity.count(contentId)) {
            return contentPopularity[contentId];
        }
        return 0;
    }
    
    // Get all content with popularity > 0
    vector<pair<int, int>> getAllPopularContent() {
        vector<pair<int, int>> result;
        
        for (const auto& entry : contentPopularity) {
            if (entry.second > 0) {
                result.push_back({entry.first, entry.second});
            }
        }
        
        // Sort by popularity (descending), then by content_id (ascending)
        sort(result.begin(), result.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.second == b.second) return a.first < b.first;
            return a.second > b.second;
        });
        
        return result;
    }
    
    // Reset all data
    void reset() {
        contentPopularity.clear();
        popularityToContents.clear();
        maxPopularity = 0;
        mostPopularContent = -1;
        hasPopularContent = false;
    }
    
    // Debug function
    void printState() {
        cout << "\n=== Popular Content State ===" << endl;
        cout << "Content Popularity:" << endl;
        
        auto allContent = getAllPopularContent();
        for (const auto& entry : allContent) {
            cout << "Content " << entry.first << ": " << entry.second << " points" << endl;
        }
        
        cout << "Most Popular Content: " << getMostPopularContent() << endl;
        cout << "Max Popularity: " << maxPopularity << endl;
        cout << "Total Content with >0 popularity: " << allContent.size() << endl;
    }

private:
    void updateMaxPopularity() {
        if (popularityToContents.empty()) {
            hasPopularContent = false;
            mostPopularContent = -1;
            maxPopularity = 0;
            return;
        }
        
        // Find the highest popularity with content that has positive popularity
        auto it = popularityToContents.rbegin();
        while (it != popularityToContents.rend()) {
            if (it->first > 0 && !it->second.empty()) {
                maxPopularity = it->first;
                mostPopularContent = *it->second.begin(); // Get smallest content ID
                hasPopularContent = true;
                return;
            }
            ++it;
        }
        
        // No content with positive popularity
        hasPopularContent = false;
        mostPopularContent = -1;
        maxPopularity = 0;
    }
};

// Advanced version with categories
class CategorizedPopularContentTracker {
private:
    unordered_map<string, PopularContentTracker> categoryTrackers;
    PopularContentTracker globalTracker;
    
public:
    void increasePopularity(int contentId, const string& category = "global") {
        categoryTrackers[category].increasePopularity(contentId);
        if (category != "global") {
            globalTracker.increasePopularity(contentId);
        }
    }
    
    void decreasePopularity(int contentId, const string& category = "global") {
        categoryTrackers[category].decreasePopularity(contentId);
        if (category != "global") {
            globalTracker.decreasePopularity(contentId);
        }
    }
    
    int getMostPopularContent(const string& category = "global") {
        if (category == "global") {
            return globalTracker.getMostPopularContent();
        }
        
        if (categoryTrackers.count(category)) {
            return categoryTrackers[category].getMostPopularContent();
        }
        
        return -1;
    }
    
    vector<pair<int, int>> getTopKInCategory(const string& category, int k) {
        if (categoryTrackers.count(category)) {
            return categoryTrackers[category].getTopKPopularContent(k);
        }
        return {};
    }
    
    vector<string> getAllCategories() {
        vector<string> result;
        for (const auto& entry : categoryTrackers) {
            result.push_back(entry.first);
        }
        return result;
    }
};

// Test functions
void testBasicOperations() {
    cout << "\n=== Testing Basic Operations ===" << endl;
    
    PopularContentTracker tracker;
    
    // Test empty state
    cout << "Most popular content (empty): " << tracker.getMostPopularContent() << endl;
    
    // Add some content
    tracker.increasePopularity(101);
    tracker.increasePopularity(102);
    tracker.increasePopularity(101); // Increase again
    
    cout << "Most popular after increases: " << tracker.getMostPopularContent() << endl;
    tracker.printState();
}

void testDecreaseOperations() {
    cout << "\n=== Testing Decrease Operations ===" << endl;
    
    PopularContentTracker tracker;
    
    // Build up popularity
    tracker.increasePopularity(201);
    tracker.increasePopularity(201);
    tracker.increasePopularity(202);
    tracker.increasePopularity(203);
    tracker.increasePopularity(203);
    tracker.increasePopularity(203);
    
    cout << "Before decreases:" << endl;
    tracker.printState();
    
    // Decrease popularity
    tracker.decreasePopularity(203); // Still most popular
    tracker.decreasePopularity(203);
    tracker.decreasePopularity(203); // Now equal with 201
    
    cout << "After decreases:" << endl;
    tracker.printState();
    
    // Decrease until empty
    tracker.decreasePopularity(201);
    tracker.decreasePopularity(201);
    tracker.decreasePopularity(202);
    
    cout << "Most popular after clearing: " << tracker.getMostPopularContent() << endl;
}

void testSpamDetection() {
    cout << "\n=== Testing Spam Detection Scenario ===" << endl;
    
    PopularContentTracker tracker;
    
    // Simulate normal activity
    tracker.increasePopularity(301); // Video gets likes
    tracker.increasePopularity(301);
    tracker.increasePopularity(302); // Another video
    tracker.increasePopularity(301);
    
    cout << "Normal activity:" << endl;
    tracker.printState();
    
    // Simulate spam detection and removal
    cout << "\nSpam detected on content 301, removing fake engagement:" << endl;
    tracker.decreasePopularity(301);
    tracker.decreasePopularity(301);
    
    tracker.printState();
}

void testTopKContent() {
    cout << "\n=== Testing Top K Content ===" << endl;
    
    PopularContentTracker tracker;
    
    // Add various content with different popularity
    vector<pair<int, int>> testData = {
        {401, 5}, {402, 3}, {403, 8}, {404, 1}, {405, 8}, {406, 2}
    };
    
    for (const auto& data : testData) {
        for (int i = 0; i < data.second; i++) {
            tracker.increasePopularity(data.first);
        }
    }
    
    cout << "All content:" << endl;
    tracker.printState();
    
    cout << "\nTop 3 content:" << endl;
    auto topK = tracker.getTopKPopularContent(3);
    for (const auto& entry : topK) {
        cout << "Content " << entry.first << ": " << entry.second << " points" << endl;
    }
}

void testCategorizedTracker() {
    cout << "\n=== Testing Categorized Tracker ===" << endl;
    
    CategorizedPopularContentTracker tracker;
    
    // Add content to different categories
    tracker.increasePopularity(501, "video");
    tracker.increasePopularity(502, "video");
    tracker.increasePopularity(501, "video");
    
    tracker.increasePopularity(601, "blog");
    tracker.increasePopularity(602, "blog");
    tracker.increasePopularity(602, "blog");
    tracker.increasePopularity(602, "blog");
    
    cout << "Most popular video: " << tracker.getMostPopularContent("video") << endl;
    cout << "Most popular blog: " << tracker.getMostPopularContent("blog") << endl;
    cout << "Most popular globally: " << tracker.getMostPopularContent("global") << endl;
    
    cout << "\nTop 2 videos:" << endl;
    auto topVideos = tracker.getTopKInCategory("video", 2);
    for (const auto& entry : topVideos) {
        cout << "Video " << entry.first << ": " << entry.second << " points" << endl;
    }
}

int main() {
    testBasicOperations();
    testDecreaseOperations();
    testSpamDetection();
    testTopKContent();
    testCategorizedTracker();
    
    return 0;
}
