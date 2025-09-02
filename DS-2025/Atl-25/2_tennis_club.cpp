/*
 * Atlassian Interview: Expanding Tennis Club
 * 
 * PROBLEM STATEMENT:
 * Implement a tennis court booking system that efficiently assigns bookings to courts
 * while minimizing the number of courts needed and handling maintenance requirements.
 * 
 * Parts:
 * a) Basic assignment: Given a list of tennis court bookings with start/finish times,
 *    assign each booking to a specific court ensuring no overlaps and minimum courts used
 * b) Maintenance time: After each booking, a fixed time X is needed for court maintenance
 * c) Periodic maintenance: Courts need Y maintenance time after X bookings
 * d) Simplified version: Find minimum number of courts needed (without specific assignment)
 * e) Conflict detection: Check if two bookings conflict with each other
 * 
 * SOLUTION APPROACH:
 * 1. Sort bookings by start time for optimal processing
 * 2. Use min-heap to track when courts become available
 * 3. For each booking:
 *    - Check if any existing court is available (accounting for maintenance time)
 *    - If available, assign to earliest available court
 *    - If not, create new court
 * 4. For minimum courts calculation: Use sweep line algorithm with events
 * 5. Maintenance handling: Add maintenance time to court availability
 * 6. Periodic maintenance: Track usage count per court
 * 
 * Time Complexity: O(n log n) for sorting, O(n) for assignment
 * Space Complexity: O(n)
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

class BookingRecord {
public:
    int id;
    int start_time;
    int finish_time;
    
    BookingRecord(int id, int start, int finish) 
        : id(id), start_time(start), finish_time(finish) {}
};

class Court {
public:
    int id;
    int last_finish_time;
    int usage_count;
    bool needs_maintenance;
    int maintenance_end_time;
    
    Court(int id) : id(id), last_finish_time(0), usage_count(0), 
                   needs_maintenance(false), maintenance_end_time(0) {}
};

class CourtAssignment {
public:
    int booking_id;
    int court_id;
    int start_time;
    int finish_time;
    
    CourtAssignment(int bid, int cid, int start, int finish)
        : booking_id(bid), court_id(cid), start_time(start), finish_time(finish) {}
};

class TennisClub {
private:
    vector<Court> courts;
    int next_court_id;
    int maintenance_time;
    int durability; // Number of bookings before maintenance needed
    
public:
    TennisClub(int maintenance_time = 0, int durability = INT_MAX) 
        : next_court_id(1), maintenance_time(maintenance_time), durability(durability) {}
    
    // Part (a): Basic court assignment
    vector<CourtAssignment> assignCourts(vector<BookingRecord>& bookings) {
        vector<CourtAssignment> assignments;
        
        // Sort bookings by start time
        sort(bookings.begin(), bookings.end(), 
             [](const BookingRecord& a, const BookingRecord& b) {
                 return a.start_time < b.start_time;
             });
        
        // Min heap to track when courts become available
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> available_courts;
        
        for (const auto& booking : bookings) {
            // Check if any court becomes available
            while (!available_courts.empty() && 
                   available_courts.top().first <= booking.start_time) {
                available_courts.pop();
            }
            
            int court_id;
            if (available_courts.empty()) {
                // Create new court
                court_id = next_court_id++;
                courts.push_back(Court(court_id));
            } else {
                // Use existing court
                auto earliest = available_courts.top();
                available_courts.pop();
                court_id = earliest.second;
            }
            
            // Assign booking to court
            assignments.push_back(CourtAssignment(booking.id, court_id, 
                                                booking.start_time, booking.finish_time));
            
            // Update court availability
            available_courts.push({booking.finish_time, court_id});
            
            // Update court state
            for (auto& court : courts) {
                if (court.id == court_id) {
                    court.last_finish_time = booking.finish_time;
                    break;
                }
            }
        }
        
        return assignments;
    }
    
    // Part (b): With maintenance time after each booking
    vector<CourtAssignment> assignCourtsWithMaintenance(vector<BookingRecord>& bookings) {
        vector<CourtAssignment> assignments;
        
        sort(bookings.begin(), bookings.end(), 
             [](const BookingRecord& a, const BookingRecord& b) {
                 return a.start_time < b.start_time;
             });
        
        // Min heap: (available_time, court_id)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> available_courts;
        
        for (const auto& booking : bookings) {
            // Check available courts
            while (!available_courts.empty() && 
                   available_courts.top().first <= booking.start_time) {
                available_courts.pop();
            }
            
            int court_id;
            if (available_courts.empty()) {
                court_id = next_court_id++;
                courts.push_back(Court(court_id));
            } else {
                auto earliest = available_courts.top();
                available_courts.pop();
                court_id = earliest.second;
            }
            
            assignments.push_back(CourtAssignment(booking.id, court_id, 
                                                booking.start_time, booking.finish_time));
            
            // Court becomes available after booking + maintenance time
            int next_available = booking.finish_time + maintenance_time;
            available_courts.push({next_available, court_id});
            
            // Update court
            for (auto& court : courts) {
                if (court.id == court_id) {
                    court.last_finish_time = next_available;
                    break;
                }
            }
        }
        
        return assignments;
    }
    
    // Part (c): With periodic maintenance after X bookings
    vector<CourtAssignment> assignCourtsWithPeriodicMaintenance(
        vector<BookingRecord>& bookings, int maintenance_duration, int usage_limit) {
        
        vector<CourtAssignment> assignments;
        
        sort(bookings.begin(), bookings.end(), 
             [](const BookingRecord& a, const BookingRecord& b) {
                 return a.start_time < b.start_time;
             });
        
        // Min heap: (available_time, court_id)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> available_courts;
        
        for (const auto& booking : bookings) {
            // Check available courts
            while (!available_courts.empty() && 
                   available_courts.top().first <= booking.start_time) {
                available_courts.pop();
            }
            
            int court_id;
            if (available_courts.empty()) {
                court_id = next_court_id++;
                courts.push_back(Court(court_id));
            } else {
                auto earliest = available_courts.top();
                available_courts.pop();
                court_id = earliest.second;
            }
            
            assignments.push_back(CourtAssignment(booking.id, court_id, 
                                                booking.start_time, booking.finish_time));
            
            // Update court usage
            Court* court = nullptr;
            for (auto& c : courts) {
                if (c.id == court_id) {
                    court = &c;
                    break;
                }
            }
            
            court->usage_count++;
            int next_available = booking.finish_time + maintenance_time;
            
            // Check if periodic maintenance is needed
            if (court->usage_count >= usage_limit) {
                next_available = booking.finish_time + maintenance_duration;
                court->usage_count = 0; // Reset after maintenance
                court->needs_maintenance = false;
            }
            
            court->last_finish_time = next_available;
            available_courts.push({next_available, court_id});
        }
        
        return assignments;
    }
    
    // Part (d): Find minimum number of courts needed
    int findMinimumCourtsNeeded(vector<BookingRecord>& bookings) {
        if (bookings.empty()) return 0;
        
        vector<pair<int, int>> events; // (time, type) where type: 1=start, -1=end
        
        for (const auto& booking : bookings) {
            events.push_back({booking.start_time, 1});
            events.push_back({booking.finish_time + maintenance_time, -1});
        }
        
        // Sort events, prioritize end events over start events at same time
        sort(events.begin(), events.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first == b.first) return a.second < b.second;
            return a.first < b.first;
        });
        
        int current_courts = 0;
        int max_courts = 0;
        
        for (const auto& event : events) {
            current_courts += event.second;
            max_courts = max(max_courts, current_courts);
        }
        
        return max_courts;
    }
    
    // Part (e): Check if two bookings conflict
    bool bookingsConflict(const BookingRecord& booking1, const BookingRecord& booking2) {
        // Consider maintenance time for conflict detection
        int end1 = booking1.finish_time + maintenance_time;
        int end2 = booking2.finish_time + maintenance_time;
        
        return !(end1 <= booking2.start_time || end2 <= booking1.start_time);
    }
    
    // Helper function to print assignments
    void printAssignments(const vector<CourtAssignment>& assignments) {
        cout << "\n=== Court Assignments ===" << endl;
        for (const auto& assignment : assignments) {
            cout << "Booking " << assignment.booking_id 
                 << " -> Court " << assignment.court_id
                 << " (" << assignment.start_time << "-" << assignment.finish_time << ")" << endl;
        }
        cout << "Total courts used: " << getMaxCourtId(assignments) << endl;
    }
    
private:
    int getMaxCourtId(const vector<CourtAssignment>& assignments) {
        int max_id = 0;
        for (const auto& assignment : assignments) {
            max_id = max(max_id, assignment.court_id);
        }
        return max_id;
    }
};

// Test functions
void testBasicAssignment() {
    cout << "\n=== Testing Basic Court Assignment ===" << endl;
    
    TennisClub club;
    vector<BookingRecord> bookings = {
        BookingRecord(1, 9, 10),   // 9-10
        BookingRecord(2, 9, 11),   // 9-11 (overlaps with 1)
        BookingRecord(3, 10, 12),  // 10-12 (can use court 1)
        BookingRecord(4, 11, 13),  // 11-13 (can use court 2)
        BookingRecord(5, 12, 14)   // 12-14 (can use court 1)
    };
    
    auto assignments = club.assignCourts(bookings);
    club.printAssignments(assignments);
    
    cout << "Minimum courts needed: " << club.findMinimumCourtsNeeded(bookings) << endl;
}

void testMaintenanceAssignment() {
    cout << "\n=== Testing Assignment with Maintenance ===" << endl;
    
    TennisClub club(30); // 30 minute maintenance after each booking
    vector<BookingRecord> bookings = {
        BookingRecord(1, 9, 10),   // 9-10, available at 10:30
        BookingRecord(2, 10, 11),  // 10-11, needs new court
        BookingRecord(3, 11, 12),  // 11-12, can use court 1 (available at 10:30)
    };
    
    auto assignments = club.assignCourtsWithMaintenance(bookings);
    club.printAssignments(assignments);
}

void testPeriodicMaintenance() {
    cout << "\n=== Testing Periodic Maintenance ===" << endl;
    
    TennisClub club(15); // 15 min maintenance after each booking
    vector<BookingRecord> bookings = {
        BookingRecord(1, 9, 10),
        BookingRecord(2, 11, 12),   // Same court after maintenance
        BookingRecord(3, 13, 14),   // Same court, triggers periodic maintenance
        BookingRecord(4, 15, 16),   // Needs to wait for longer maintenance
    };
    
    auto assignments = club.assignCourtsWithPeriodicMaintenance(bookings, 60, 2); // 60 min maintenance every 2 bookings
    club.printAssignments(assignments);
}

void testBookingConflicts() {
    cout << "\n=== Testing Booking Conflicts ===" << endl;
    
    TennisClub club(15);
    BookingRecord b1(1, 9, 10);
    BookingRecord b2(2, 10, 11);   // Conflicts due to maintenance time
    BookingRecord b3(3, 10, 11);   // Also conflicts
    BookingRecord b4(4, 11, 12);   // No conflict (starts after maintenance)
    
    cout << "Booking 1 conflicts with Booking 2: " << club.bookingsConflict(b1, b2) << endl;
    cout << "Booking 1 conflicts with Booking 3: " << club.bookingsConflict(b1, b3) << endl;
    cout << "Booking 1 conflicts with Booking 4: " << club.bookingsConflict(b1, b4) << endl;
}

int main() {
    testBasicAssignment();
    testMaintenanceAssignment();
    testPeriodicMaintenance();
    testBookingConflicts();
    
    return 0;
}
