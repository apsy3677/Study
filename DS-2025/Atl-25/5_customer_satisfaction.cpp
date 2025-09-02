/*
 * Atlassian Interview: Customer Satisfaction System
 * 
 * PROBLEM STATEMENT:
 * Design a customer support ticketing system where customers rate support agents out of 5.
 * 
 * Requirements:
 * a) Basic functionality: Accept ratings, show all agents with average ratings (highest to lowest)
 * b) Tie handling: Handle cases where two agents have same average rating
 * c) Monthly tracking: Show best agents each month
 * d) Export functionality: Export agent ratings per month in CSV, JSON, or XML
 * e) Alternative views: Return unsorted ratings, total ratings without average
 * 
 * SOLUTION APPROACH:
 * 1. Use unordered_map<agentId, AgentRating> for agent data storage
 * 2. AgentRating struct tracks: totalRating, ratingCount, averageRating
 * 3. For monthly tracking: nested map<agentId, map<monthYear, MonthlyRating>>
 * 4. Tie-breaking strategies: alphabetical, rating count, first seen
 * 5. Export formats: stringstream for CSV/JSON generation
 * 6. Sorting: custom comparators for different ranking needs
 * 
 * Time Complexity: O(1) for addRating, O(n log n) for sorted results
 * Space Complexity: O(n)
 */

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

struct AgentRating {
    string agentId;
    double totalRating;
    int ratingCount;
    double averageRating;
    
    AgentRating(string id = "") : agentId(id), totalRating(0.0), ratingCount(0), averageRating(0.0) {}
    
    void addRating(int rating) {
        totalRating += rating;
        ratingCount++;
        averageRating = totalRating / ratingCount;
    }
    
    double getAverageRating() const {
        return ratingCount > 0 ? averageRating : 0.0;
    }
};

struct MonthlyRating {
    int month;
    int year;
    double totalRating;
    int ratingCount;
    
    MonthlyRating(int m = 0, int y = 0) : month(m), year(y), totalRating(0.0), ratingCount(0) {}
    
    void addRating(int rating) {
        totalRating += rating;
        ratingCount++;
    }
    
    double getAverageRating() const {
        return ratingCount > 0 ? totalRating / ratingCount : 0.0;
    }
    
    string getMonthYearString() const {
        return to_string(month) + "/" + to_string(year);
    }
};

class CustomerSatisfactionSystem {
private:
    unordered_map<string, AgentRating> agents;
    unordered_map<string, unordered_map<string, MonthlyRating>> monthlyRatings; // agentId -> monthYear -> rating
    
    string getMonthYearKey(int month, int year) {
        return to_string(month) + "-" + to_string(year);
    }
    
public:
    // Part (a): Basic rating functionality
    void addRating(const string& agentId, int rating) {
        if (rating < 1 || rating > 5) {
            cout << "Error: Rating must be between 1 and 5" << endl;
            return;
        }
        
        if (agents.find(agentId) == agents.end()) {
            agents[agentId] = AgentRating(agentId);
        }
        
        agents[agentId].addRating(rating);
    }
    
    vector<pair<string, double>> getAllAgentsRanked() {
        vector<pair<string, double>> result;
        
        for (const auto& entry : agents) {
            result.push_back({entry.first, entry.second.getAverageRating()});
        }
        
        // Sort by average rating (highest to lowest)
        sort(result.begin(), result.end(), 
             [](const pair<string, double>& a, const pair<string, double>& b) {
                 return a.second > b.second;
             });
        
        return result;
    }
    
    // Part (b): Handle ties with different strategies
    enum TieBreakingStrategy {
        AGENT_ID_ASC,    // Alphabetical by agent ID
        AGENT_ID_DESC,   // Reverse alphabetical
        RATING_COUNT,    // More ratings wins
        FIRST_SEEN       // First agent added wins
    };
    
    vector<pair<string, double>> getAllAgentsRankedWithTieBreaking(TieBreakingStrategy strategy) {
        vector<pair<string, double>> result;
        
        for (const auto& entry : agents) {
            result.push_back({entry.first, entry.second.getAverageRating()});
        }
        
        // Sort with tie-breaking
        sort(result.begin(), result.end(), 
             [this, strategy](const pair<string, double>& a, const pair<string, double>& b) {
                 if (abs(a.second - b.second) < 0.001) { // Consider equal if very close
                     switch (strategy) {
                         case AGENT_ID_ASC:
                             return a.first < b.first;
                         case AGENT_ID_DESC:
                             return a.first > b.first;
                         case RATING_COUNT:
                             return agents.at(a.first).ratingCount > agents.at(b.first).ratingCount;
                         case FIRST_SEEN:
                             return false; // Maintain original order for equal ratings
                     }
                 }
                 return a.second > b.second;
             });
        
        return result;
    }
    
    // Part (c): Monthly tracking
    void addRatingForMonth(const string& agentId, int rating, int month, int year) {
        if (rating < 1 || rating > 5) {
            cout << "Error: Rating must be between 1 and 5" << endl;
            return;
        }
        
        // Add to overall rating
        addRating(agentId, rating);
        
        // Add to monthly tracking
        string monthKey = getMonthYearKey(month, year);
        if (monthlyRatings[agentId].find(monthKey) == monthlyRatings[agentId].end()) {
            monthlyRatings[agentId][monthKey] = MonthlyRating(month, year);
        }
        
        monthlyRatings[agentId][monthKey].addRating(rating);
    }
    
    vector<pair<string, double>> getBestAgentsForMonth(int month, int year) {
        vector<pair<string, double>> result;
        string monthKey = getMonthYearKey(month, year);
        
        for (const auto& agentEntry : monthlyRatings) {
            const string& agentId = agentEntry.first;
            const auto& agentMonthlyData = agentEntry.second;
            
            if (agentMonthlyData.find(monthKey) != agentMonthlyData.end()) {
                double avgRating = agentMonthlyData.at(monthKey).getAverageRating();
                result.push_back({agentId, avgRating});
            }
        }
        
        // Sort by average rating (highest to lowest)
        sort(result.begin(), result.end(), 
             [](const pair<string, double>& a, const pair<string, double>& b) {
                 return a.second > b.second;
             });
        
        return result;
    }
    
    // Part (d): Export functionality
    string exportAgentRatingsCSV() {
        stringstream csv;
        csv << "Agent_ID,Average_Rating,Total_Ratings,Rating_Count\n";
        
        auto rankedAgents = getAllAgentsRanked();
        for (const auto& agent : rankedAgents) {
            const AgentRating& rating = agents[agent.first];
            csv << agent.first << ","
                << fixed << setprecision(2) << agent.second << ","
                << rating.totalRating << ","
                << rating.ratingCount << "\n";
        }
        
        return csv.str();
    }
    
    string exportMonthlyRatingsCSV() {
        stringstream csv;
        csv << "Agent_ID,Month,Year,Average_Rating,Rating_Count\n";
        
        for (const auto& agentEntry : monthlyRatings) {
            const string& agentId = agentEntry.first;
            const auto& monthlyData = agentEntry.second;
            
            for (const auto& monthEntry : monthlyData) {
                const MonthlyRating& monthRating = monthEntry.second;
                csv << agentId << ","
                    << monthRating.month << ","
                    << monthRating.year << ","
                    << fixed << setprecision(2) << monthRating.getAverageRating() << ","
                    << monthRating.ratingCount << "\n";
            }
        }
        
        return csv.str();
    }
    
    string exportAgentRatingsJSON() {
        stringstream json;
        json << "{\n  \"agents\": [\n";
        
        auto rankedAgents = getAllAgentsRanked();
        for (size_t i = 0; i < rankedAgents.size(); i++) {
            const auto& agent = rankedAgents[i];
            const AgentRating& rating = agents[agent.first];
            
            json << "    {\n";
            json << "      \"agent_id\": \"" << agent.first << "\",\n";
            json << "      \"average_rating\": " << fixed << setprecision(2) << agent.second << ",\n";
            json << "      \"total_rating\": " << rating.totalRating << ",\n";
            json << "      \"rating_count\": " << rating.ratingCount << "\n";
            json << "    }";
            
            if (i < rankedAgents.size() - 1) json << ",";
            json << "\n";
        }
        
        json << "  ]\n}";
        return json.str();
    }
    
    // Part (e): Alternative views
    vector<pair<string, double>> getAllAgentsUnsorted() {
        vector<pair<string, double>> result;
        
        for (const auto& entry : agents) {
            result.push_back({entry.first, entry.second.getAverageRating()});
        }
        
        return result;
    }
    
    vector<pair<string, double>> getAllAgentsTotalRatings() {
        vector<pair<string, double>> result;
        
        for (const auto& entry : agents) {
            result.push_back({entry.first, entry.second.totalRating});
        }
        
        // Sort by total rating (highest to lowest)
        sort(result.begin(), result.end(), 
             [](const pair<string, double>& a, const pair<string, double>& b) {
                 return a.second > b.second;
             });
        
        return result;
    }
    
    // Additional utility functions
    void printAgentStatistics(const string& agentId) {
        if (agents.find(agentId) == agents.end()) {
            cout << "Agent not found: " << agentId << endl;
            return;
        }
        
        const AgentRating& rating = agents[agentId];
        cout << "\n=== Agent " << agentId << " Statistics ===" << endl;
        cout << "Average Rating: " << fixed << setprecision(2) << rating.getAverageRating() << endl;
        cout << "Total Rating Points: " << rating.totalRating << endl;
        cout << "Number of Ratings: " << rating.ratingCount << endl;
        
        // Monthly breakdown
        if (monthlyRatings.find(agentId) != monthlyRatings.end()) {
            cout << "\nMonthly Breakdown:" << endl;
            for (const auto& monthEntry : monthlyRatings[agentId]) {
                const MonthlyRating& monthRating = monthEntry.second;
                cout << monthRating.getMonthYearString() << ": " 
                     << fixed << setprecision(2) << monthRating.getAverageRating()
                     << " (" << monthRating.ratingCount << " ratings)" << endl;
            }
        }
    }
    
    void printTopAgents(int count = 5) {
        cout << "\n=== Top " << count << " Agents ===" << endl;
        auto rankedAgents = getAllAgentsRanked();
        
        for (int i = 0; i < min(count, (int)rankedAgents.size()); i++) {
            const auto& agent = rankedAgents[i];
            const AgentRating& rating = agents[agent.first];
            cout << (i + 1) << ". " << agent.first 
                 << " - " << fixed << setprecision(2) << agent.second
                 << " (" << rating.ratingCount << " ratings)" << endl;
        }
    }
};

// Test functions
void testBasicRating() {
    cout << "\n=== Testing Basic Rating System ===" << endl;
    
    CustomerSatisfactionSystem system;
    
    // Add some ratings
    system.addRating("Agent001", 5);
    system.addRating("Agent001", 4);
    system.addRating("Agent002", 5);
    system.addRating("Agent003", 3);
    system.addRating("Agent003", 4);
    system.addRating("Agent003", 5);
    
    system.printTopAgents();
}

void testTieBreaking() {
    cout << "\n=== Testing Tie Breaking ===" << endl;
    
    CustomerSatisfactionSystem system;
    
    // Create agents with same average rating
    system.addRating("AgentB", 4);
    system.addRating("AgentB", 4);
    system.addRating("AgentA", 3);
    system.addRating("AgentA", 5);
    system.addRating("AgentC", 4);
    system.addRating("AgentC", 4);
    
    cout << "With alphabetical tie-breaking:" << endl;
    auto results = system.getAllAgentsRankedWithTieBreaking(CustomerSatisfactionSystem::AGENT_ID_ASC);
    for (const auto& agent : results) {
        cout << agent.first << ": " << fixed << setprecision(2) << agent.second << endl;
    }
}

void testMonthlyTracking() {
    cout << "\n=== Testing Monthly Tracking ===" << endl;
    
    CustomerSatisfactionSystem system;
    
    // Add ratings for different months
    system.addRatingForMonth("Agent001", 5, 1, 2024);
    system.addRatingForMonth("Agent001", 4, 1, 2024);
    system.addRatingForMonth("Agent001", 3, 2, 2024);
    system.addRatingForMonth("Agent002", 5, 1, 2024);
    system.addRatingForMonth("Agent002", 5, 2, 2024);
    
    cout << "Best agents for January 2024:" << endl;
    auto january = system.getBestAgentsForMonth(1, 2024);
    for (const auto& agent : january) {
        cout << agent.first << ": " << fixed << setprecision(2) << agent.second << endl;
    }
    
    system.printAgentStatistics("Agent001");
}

void testExportFunctionality() {
    cout << "\n=== Testing Export Functionality ===" << endl;
    
    CustomerSatisfactionSystem system;
    
    system.addRating("Agent001", 5);
    system.addRating("Agent001", 4);
    system.addRating("Agent002", 3);
    system.addRating("Agent002", 4);
    
    cout << "CSV Export:" << endl;
    cout << system.exportAgentRatingsCSV() << endl;
    
    cout << "JSON Export:" << endl;
    cout << system.exportAgentRatingsJSON() << endl;
}

int main() {
    testBasicRating();
    testTieBreaking();
    testMonthlyTracking();
    testExportFunctionality();
    
    return 0;
}
