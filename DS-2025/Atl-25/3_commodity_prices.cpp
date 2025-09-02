/*
 * Atlassian Interview: Commodity Prices
 * 
 * PROBLEM STATEMENT:
 * You are given a stream of data points consisting of <timestamp, commodityPrice>.
 * You need to return the maxCommodityPrice at any point in time. The timestamps 
 * in the stream can be out of order, and there can be duplicate timestamps.
 * When duplicate timestamps exist, update the commodityPrice at that timestamp.
 * 
 * Requirements:
 * - Create an in-memory solution tailored for frequent reads and writes
 * - Handle out-of-order timestamps
 * - Handle duplicate timestamps (upsert operation)
 * - Optimize getMaxCommodityPrice to O(1) if possible
 * 
 * SOLUTION APPROACH:
 * 1. Use map<timestamp, price> for chronological ordering
 * 2. Use multiset<price> for efficient max price retrieval
 * 3. For O(1) max price: maintain maxPrice variable with careful updates
 * 4. Upsert logic:
 *    - If timestamp exists: remove old price from multiset, add new price
 *    - Update maxPrice variable intelligently
 * 5. Advanced: Support multiple commodities with separate trackers
 * 
 * Time Complexity: O(log n) for upsert, O(1) for getMax (optimized)
 * Space Complexity: O(n)
 */

#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class CommodityPriceTracker {
private:
    map<int, double> timestampToPrice;  // timestamp -> price
    multiset<double> prices;            // For efficient max finding
    unordered_map<int, double> oldPrices; // For tracking old prices during updates
    double maxPrice;                    // O(1) max price tracking
    bool hasData;
    
public:
    CommodityPriceTracker() : maxPrice(0.0), hasData(false) {}
    
    // Upsert operation - handles out of order and duplicate timestamps
    void upsertPrice(int timestamp, double price) {
        // Check if timestamp already exists
        if (timestampToPrice.count(timestamp)) {
            double oldPrice = timestampToPrice[timestamp];
            
            // Remove old price from multiset
            auto it = prices.find(oldPrice);
            if (it != prices.end()) {
                prices.erase(it);
            }
            
            // Update max price if needed
            if (oldPrice == maxPrice && prices.empty()) {
                maxPrice = price;
            } else if (oldPrice == maxPrice && !prices.empty()) {
                maxPrice = max(price, *prices.rbegin());
            } else if (price > maxPrice) {
                maxPrice = price;
            }
        } else {
            // New timestamp
            if (!hasData || price > maxPrice) {
                maxPrice = price;
                hasData = true;
            }
        }
        
        // Update data structures
        timestampToPrice[timestamp] = price;
        prices.insert(price);
    }
    
    // Get maximum commodity price - O(1) optimized version
    double getMaxCommodityPrice() {
        if (!hasData) {
            throw runtime_error("No price data available");
        }
        return maxPrice;
    }
    
    // Alternative O(log n) version using multiset
    double getMaxCommodityPriceFromSet() {
        if (prices.empty()) {
            throw runtime_error("No price data available");
        }
        return *prices.rbegin();
    }
    
    // Get price at specific timestamp
    double getPriceAtTimestamp(int timestamp) {
        if (timestampToPrice.count(timestamp)) {
            return timestampToPrice[timestamp];
        }
        throw runtime_error("No price data for timestamp: " + to_string(timestamp));
    }
    
    // Get all prices in chronological order
    vector<pair<int, double>> getAllPricesChronological() {
        vector<pair<int, double>> result;
        for (const auto& entry : timestampToPrice) {
            result.push_back({entry.first, entry.second});
        }
        return result;
    }
    
    // Get price history within time range
    vector<pair<int, double>> getPriceHistory(int startTime, int endTime) {
        vector<pair<int, double>> result;
        
        auto start_it = timestampToPrice.lower_bound(startTime);
        auto end_it = timestampToPrice.upper_bound(endTime);
        
        for (auto it = start_it; it != end_it; ++it) {
            result.push_back({it->first, it->second});
        }
        
        return result;
    }
    
    // Remove price data for a specific timestamp
    void removePrice(int timestamp) {
        if (timestampToPrice.count(timestamp)) {
            double price = timestampToPrice[timestamp];
            
            // Remove from multiset
            auto it = prices.find(price);
            if (it != prices.end()) {
                prices.erase(it);
            }
            
            // Remove from map
            timestampToPrice.erase(timestamp);
            
            // Update max price
            if (prices.empty()) {
                hasData = false;
                maxPrice = 0.0;
            } else if (price == maxPrice) {
                maxPrice = *prices.rbegin();
            }
        }
    }
    
    // Get statistics
    struct PriceStats {
        double min_price;
        double max_price;
        double avg_price;
        int total_entries;
        int earliest_timestamp;
        int latest_timestamp;
    };
    
    PriceStats getStatistics() {
        if (prices.empty()) {
            throw runtime_error("No price data available for statistics");
        }
        
        PriceStats stats;
        stats.min_price = *prices.begin();
        stats.max_price = *prices.rbegin();
        stats.total_entries = prices.size();
        stats.earliest_timestamp = timestampToPrice.begin()->first;
        stats.latest_timestamp = timestampToPrice.rbegin()->first;
        
        double sum = 0.0;
        for (double price : prices) {
            sum += price;
        }
        stats.avg_price = sum / stats.total_entries;
        
        return stats;
    }
    
    // Debug function
    void printAllData() {
        cout << "\n=== Commodity Price Data ===" << endl;
        cout << "Timestamp -> Price:" << endl;
        for (const auto& entry : timestampToPrice) {
            cout << entry.first << " -> $" << entry.second << endl;
        }
        cout << "Current Max Price: $" << maxPrice << endl;
        cout << "Total Entries: " << prices.size() << endl;
    }
};

// Advanced version with multiple commodities
class MultiCommodityTracker {
private:
    unordered_map<string, CommodityPriceTracker> commodities;
    
public:
    void upsertPrice(const string& commodity, int timestamp, double price) {
        commodities[commodity].upsertPrice(timestamp, price);
    }
    
    double getMaxPrice(const string& commodity) {
        if (commodities.count(commodity)) {
            return commodities[commodity].getMaxCommodityPrice();
        }
        throw runtime_error("Commodity not found: " + commodity);
    }
    
    // Get max price across all commodities
    pair<string, double> getGlobalMaxPrice() {
        string maxCommodity;
        double maxPrice = -1;
        
        for (const auto& entry : commodities) {
            try {
                double price = entry.second.getMaxCommodityPrice();
                if (price > maxPrice) {
                    maxPrice = price;
                    maxCommodity = entry.first;
                }
            } catch (const runtime_error&) {
                // Skip commodities with no data
            }
        }
        
        if (maxPrice == -1) {
            throw runtime_error("No commodity data available");
        }
        
        return {maxCommodity, maxPrice};
    }
    
    vector<string> getAllCommodities() {
        vector<string> result;
        for (const auto& entry : commodities) {
            result.push_back(entry.first);
        }
        return result;
    }
};

// Test functions
void testBasicFunctionality() {
    cout << "\n=== Testing Basic Functionality ===" << endl;
    
    CommodityPriceTracker tracker;
    
    // Test normal order
    tracker.upsertPrice(1000, 100.5);
    tracker.upsertPrice(1001, 105.2);
    tracker.upsertPrice(1002, 98.7);
    
    cout << "Max price after sequential inserts: $" << tracker.getMaxCommodityPrice() << endl;
    
    tracker.printAllData();
}

void testOutOfOrderInserts() {
    cout << "\n=== Testing Out-of-Order Inserts ===" << endl;
    
    CommodityPriceTracker tracker;
    
    // Insert out of order
    tracker.upsertPrice(1005, 120.0);
    tracker.upsertPrice(1001, 110.0);
    tracker.upsertPrice(1003, 115.0);
    tracker.upsertPrice(1002, 108.0);
    
    cout << "Max price: $" << tracker.getMaxCommodityPrice() << endl;
    
    auto chronological = tracker.getAllPricesChronological();
    cout << "Chronological order:" << endl;
    for (const auto& entry : chronological) {
        cout << "Time " << entry.first << ": $" << entry.second << endl;
    }
}

void testDuplicateTimestamps() {
    cout << "\n=== Testing Duplicate Timestamps ===" << endl;
    
    CommodityPriceTracker tracker;
    
    tracker.upsertPrice(1000, 100.0);
    tracker.upsertPrice(1001, 105.0);
    tracker.upsertPrice(1000, 95.0);  // Update existing timestamp
    tracker.upsertPrice(1001, 110.0); // Update with higher price
    
    cout << "Max price after updates: $" << tracker.getMaxCommodityPrice() << endl;
    
    tracker.printAllData();
}

void testStatistics() {
    cout << "\n=== Testing Statistics ===" << endl;
    
    CommodityPriceTracker tracker;
    
    vector<pair<int, double>> testData = {
        {1000, 100.0}, {1001, 105.0}, {1002, 98.0}, 
        {1003, 120.0}, {1004, 95.0}, {1005, 110.0}
    };
    
    for (const auto& data : testData) {
        tracker.upsertPrice(data.first, data.second);
    }
    
    auto stats = tracker.getStatistics();
    cout << "Statistics:" << endl;
    cout << "Min Price: $" << stats.min_price << endl;
    cout << "Max Price: $" << stats.max_price << endl;
    cout << "Avg Price: $" << stats.avg_price << endl;
    cout << "Total Entries: " << stats.total_entries << endl;
    cout << "Time Range: " << stats.earliest_timestamp << " - " << stats.latest_timestamp << endl;
}

void testMultiCommodity() {
    cout << "\n=== Testing Multi-Commodity Tracker ===" << endl;
    
    MultiCommodityTracker tracker;
    
    // Add different commodities
    tracker.upsertPrice("GOLD", 1000, 1800.50);
    tracker.upsertPrice("SILVER", 1000, 25.30);
    tracker.upsertPrice("OIL", 1000, 75.20);
    
    tracker.upsertPrice("GOLD", 1001, 1820.75);
    tracker.upsertPrice("SILVER", 1001, 24.80);
    tracker.upsertPrice("OIL", 1001, 78.50);
    
    cout << "Gold max price: $" << tracker.getMaxPrice("GOLD") << endl;
    cout << "Silver max price: $" << tracker.getMaxPrice("SILVER") << endl;
    cout << "Oil max price: $" << tracker.getMaxPrice("OIL") << endl;
    
    auto globalMax = tracker.getGlobalMaxPrice();
    cout << "Global max: " << globalMax.first << " at $" << globalMax.second << endl;
}

int main() {
    testBasicFunctionality();
    testOutOfOrderInserts();
    testDuplicateTimestamps();
    testStatistics();
    testMultiCommodity();
    
    return 0;
}
