/*
 * Atlassian Interview: Cost Explorer
 * 
 * PROBLEM STATEMENT:
 * You are working on the payments team at Atlassian. A customer subscribes to Jira and 
 * wants to explore how much it will cost them to use the product for the rest of the year.
 * 
 * Requirements:
 * - Develop a CostExplorer that calculates total cost a customer pays in a unit year
 * - At any day of the year, provide provisional report with monthly/yearly cost estimates
 * - Support multiple plans for a product (Level 0)
 * 
 * CostExplorer should provide:
 * 1. Monthly cost: Generate bill for each month, including future months for unit year
 * 2. Yearly cost estimated: Total cost for the unit year
 * 3. Plan comparison: Compare different subscription plans
 * 4. Upgrade/downgrade scenarios: Cost impact of plan changes
 * 
 * SOLUTION APPROACH:
 * 1. Define Plan structure: planType, pricing (monthly/yearly), user limits, features
 * 2. Subscription tracking: planType, billingCycle, startDate, userCount
 * 3. Cost calculation:
 *    - Monthly billing: charge every month
 *    - Yearly billing: charge full amount at start month
 * 4. Report generation: iterate through months, calculate costs per subscription
 * 5. Plan comparison: analyze cost differences for given user count
 * 6. Export functionality: CSV, JSON formats for reports
 * 
 * Time Complexity: O(1) for cost calculations, O(n) for reports
 * Space Complexity: O(n) where n is number of plans/months
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

enum BillingCycle {
    MONTHLY,
    YEARLY
};

enum PlanType {
    FREE,
    STANDARD,
    PREMIUM,
    ENTERPRISE
};

struct Plan {
    PlanType type;
    string name;
    double monthlyPrice;
    double yearlyPrice;
    int userLimit;
    bool hasCustomFields;
    bool hasAdvancedReporting;
    
    Plan(PlanType t, string n, double mp, double yp, int ul, bool cf = false, bool ar = false)
        : type(t), name(n), monthlyPrice(mp), yearlyPrice(yp), userLimit(ul), 
          hasCustomFields(cf), hasAdvancedReporting(ar) {}
};

struct Subscription {
    PlanType planType;
    BillingCycle billingCycle;
    int startMonth;
    int startYear;
    int userCount;
    bool isActive;
    
    Subscription(PlanType pt, BillingCycle bc, int sm, int sy, int uc)
        : planType(pt), billingCycle(bc), startMonth(sm), startYear(sy), 
          userCount(uc), isActive(true) {}
};

struct MonthlyCost {
    int month;
    int year;
    double amount;
    string planName;
    int userCount;
    BillingCycle billingCycle;
    
    MonthlyCost(int m, int y, double a, string pn, int uc, BillingCycle bc)
        : month(m), year(y), amount(a), planName(pn), userCount(uc), billingCycle(bc) {}
};

class CostExplorer {
private:
    unordered_map<PlanType, Plan> plans;
    vector<Subscription> subscriptions;
    int currentMonth;
    int currentYear;
    
public:
    CostExplorer() {
        initializePlans();
        
        // Set current date (in real implementation, get from system)
        time_t now = time(0);
        tm* ltm = localtime(&now);
        currentMonth = ltm->tm_mon + 1; // tm_mon is 0-11
        currentYear = ltm->tm_year + 1900;
    }
    
    void initializePlans() {
        plans[FREE] = Plan(FREE, "Free", 0.0, 0.0, 10);
        plans[STANDARD] = Plan(STANDARD, "Standard", 7.0, 70.0, 100, true);
        plans[PREMIUM] = Plan(PREMIUM, "Premium", 14.0, 140.0, 1000, true, true);
        plans[ENTERPRISE] = Plan(ENTERPRISE, "Enterprise", 25.0, 250.0, INT_MAX, true, true);
    }
    
    // Add a subscription
    void addSubscription(PlanType planType, BillingCycle billingCycle, 
                        int startMonth, int startYear, int userCount) {
        subscriptions.push_back(Subscription(planType, billingCycle, 
                                           startMonth, startYear, userCount));
    }
    
    // Level 0: Multiple Plans for a Product
    void addSubscription(PlanType planType, BillingCycle billingCycle, int userCount) {
        addSubscription(planType, billingCycle, currentMonth, currentYear, userCount);
    }
    
    // Calculate monthly cost for a specific subscription
    double calculateMonthlyCost(const Subscription& subscription, int month, int year) {
        if (!subscription.isActive) return 0.0;
        
        // Check if subscription is active in this month
        if (year < subscription.startYear || 
            (year == subscription.startYear && month < subscription.startMonth)) {
            return 0.0;
        }
        
        const Plan& plan = plans[subscription.planType];
        
        if (subscription.billingCycle == MONTHLY) {
            return plan.monthlyPrice * subscription.userCount;
        } else {
            // For yearly billing, charge full amount in subscription start month
            if (month == subscription.startMonth && 
                (year == subscription.startYear || 
                 (year > subscription.startYear && (year - subscription.startYear) % 1 == 0))) {
                return plan.yearlyPrice * subscription.userCount;
            }
            return 0.0;
        }
    }
    
    // Generate monthly cost report for the unit year
    vector<MonthlyCost> generateMonthlyCostReport() {
        vector<MonthlyCost> monthlyCosts;
        
        for (int month = 1; month <= 12; month++) {
            double totalMonthCost = 0.0;
            
            for (const auto& subscription : subscriptions) {
                double cost = calculateMonthlyCost(subscription, month, currentYear);
                if (cost > 0) {
                    const Plan& plan = plans[subscription.planType];
                    monthlyCosts.push_back(MonthlyCost(month, currentYear, cost, 
                                                     plan.name, subscription.userCount, 
                                                     subscription.billingCycle));
                }
                totalMonthCost += cost;
            }
        }
        
        return monthlyCosts;
    }
    
    // Generate monthly summary (total cost per month)
    vector<pair<string, double>> generateMonthlySummary() {
        vector<pair<string, double>> summary;
        
        for (int month = 1; month <= 12; month++) {
            double totalMonthCost = 0.0;
            
            for (const auto& subscription : subscriptions) {
                totalMonthCost += calculateMonthlyCost(subscription, month, currentYear);
            }
            
            string monthName = getMonthName(month) + " " + to_string(currentYear);
            summary.push_back({monthName, totalMonthCost});
        }
        
        return summary;
    }
    
    // Calculate total yearly cost
    double calculateYearlyCost() {
        double totalYearlyCost = 0.0;
        
        for (int month = 1; month <= 12; month++) {
            for (const auto& subscription : subscriptions) {
                totalYearlyCost += calculateMonthlyCost(subscription, month, currentYear);
            }
        }
        
        return totalYearlyCost;
    }
    
    // Get cost estimate from current date to end of year
    double getCostEstimateFromNow() {
        double totalCost = 0.0;
        
        for (int month = currentMonth; month <= 12; month++) {
            for (const auto& subscription : subscriptions) {
                totalCost += calculateMonthlyCost(subscription, month, currentYear);
            }
        }
        
        return totalCost;
    }
    
    // Plan comparison
    struct PlanComparison {
        PlanType planType;
        string planName;
        double monthlyCost;
        double yearlyCost;
        double yearlyDiscount;
        int userLimit;
    };
    
    vector<PlanComparison> comparePlans(int userCount) {
        vector<PlanComparison> comparisons;
        
        for (const auto& planEntry : plans) {
            const Plan& plan = planEntry.second;
            
            if (userCount <= plan.userLimit || plan.userLimit == INT_MAX) {
                double monthlyCost = plan.monthlyPrice * userCount * 12;
                double yearlyCost = plan.yearlyPrice * userCount;
                double discount = monthlyCost > 0 ? ((monthlyCost - yearlyCost) / monthlyCost) * 100 : 0;
                
                comparisons.push_back({plan.type, plan.name, monthlyCost, 
                                     yearlyCost, discount, plan.userLimit});
            }
        }
        
        // Sort by yearly cost
        sort(comparisons.begin(), comparisons.end(), 
             [](const PlanComparison& a, const PlanComparison& b) {
                 return a.yearlyCost < b.yearlyCost;
             });
        
        return comparisons;
    }
    
    // Upgrade/downgrade simulation
    void upgradePlan(size_t subscriptionIndex, PlanType newPlanType) {
        if (subscriptionIndex < subscriptions.size()) {
            subscriptions[subscriptionIndex].planType = newPlanType;
        }
    }
    
    void changeUserCount(size_t subscriptionIndex, int newUserCount) {
        if (subscriptionIndex < subscriptions.size()) {
            subscriptions[subscriptionIndex].userCount = newUserCount;
        }
    }
    
    // Reporting functions
    void printMonthlyCostReport() {
        cout << "\n=== Monthly Cost Report for " << currentYear << " ===" << endl;
        cout << setw(15) << "Month" << setw(15) << "Plan" << setw(10) << "Users" 
             << setw(15) << "Billing" << setw(15) << "Cost" << endl;
        cout << string(70, '-') << endl;
        
        auto costs = generateMonthlyCostReport();
        for (const auto& cost : costs) {
            cout << setw(15) << (getMonthName(cost.month) + " " + to_string(cost.year))
                 << setw(15) << cost.planName
                 << setw(10) << cost.userCount
                 << setw(15) << (cost.billingCycle == MONTHLY ? "Monthly" : "Yearly")
                 << setw(14) << "$" << fixed << setprecision(2) << cost.amount << endl;
        }
    }
    
    void printMonthlySummary() {
        cout << "\n=== Monthly Summary for " << currentYear << " ===" << endl;
        cout << setw(20) << "Month" << setw(15) << "Total Cost" << endl;
        cout << string(35, '-') << endl;
        
        auto summary = generateMonthlySummary();
        double totalYear = 0.0;
        
        for (const auto& month : summary) {
            cout << setw(20) << month.first << setw(14) << "$" 
                 << fixed << setprecision(2) << month.second << endl;
            totalYear += month.second;
        }
        
        cout << string(35, '-') << endl;
        cout << setw(20) << "Total Year" << setw(14) << "$" 
             << fixed << setprecision(2) << totalYear << endl;
    }
    
    void printPlanComparison(int userCount) {
        cout << "\n=== Plan Comparison for " << userCount << " users ===" << endl;
        cout << setw(15) << "Plan" << setw(18) << "Monthly (yearly)" 
             << setw(15) << "Yearly" << setw(15) << "Savings" << endl;
        cout << string(65, '-') << endl;
        
        auto comparisons = comparePlans(userCount);
        for (const auto& comp : comparisons) {
            cout << setw(15) << comp.planName
                 << setw(17) << "$" << fixed << setprecision(2) << comp.monthlyCost
                 << setw(14) << "$" << fixed << setprecision(2) << comp.yearlyCost
                 << setw(13) << fixed << setprecision(1) << comp.yearlyDiscount << "%"
                 << endl;
        }
    }
    
    void printCurrentSubscriptions() {
        cout << "\n=== Current Subscriptions ===" << endl;
        cout << setw(5) << "ID" << setw(15) << "Plan" << setw(12) << "Billing" 
             << setw(8) << "Users" << setw(15) << "Start Date" << endl;
        cout << string(55, '-') << endl;
        
        for (size_t i = 0; i < subscriptions.size(); i++) {
            const auto& sub = subscriptions[i];
            const Plan& plan = plans[sub.planType];
            
            cout << setw(5) << i
                 << setw(15) << plan.name
                 << setw(12) << (sub.billingCycle == MONTHLY ? "Monthly" : "Yearly")
                 << setw(8) << sub.userCount
                 << setw(15) << (getMonthName(sub.startMonth) + " " + to_string(sub.startYear))
                 << endl;
        }
    }

private:
    string getMonthName(int month) {
        vector<string> months = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                               "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return months[month];
    }
};

// Test functions
void testBasicCostCalculation() {
    cout << "\n=== Testing Basic Cost Calculation ===" << endl;
    
    CostExplorer explorer;
    
    // Add some subscriptions
    explorer.addSubscription(STANDARD, MONTHLY, 50);  // Standard plan, 50 users
    explorer.addSubscription(PREMIUM, YEARLY, 25);    // Premium plan, 25 users
    
    explorer.printCurrentSubscriptions();
    explorer.printMonthlySummary();
    
    cout << "\nTotal yearly cost: $" << fixed << setprecision(2) 
         << explorer.calculateYearlyCost() << endl;
    cout << "Cost from now to end of year: $" << fixed << setprecision(2)
         << explorer.getCostEstimateFromNow() << endl;
}

void testMultiplePlans() {
    cout << "\n=== Testing Multiple Plans ===" << endl;
    
    CostExplorer explorer;
    
    // Add multiple subscriptions
    explorer.addSubscription(FREE, MONTHLY, 5);       // Free tier
    explorer.addSubscription(STANDARD, MONTHLY, 30);  // Standard
    explorer.addSubscription(PREMIUM, YEARLY, 100);   // Premium yearly
    explorer.addSubscription(ENTERPRISE, MONTHLY, 500); // Enterprise
    
    explorer.printCurrentSubscriptions();
    explorer.printMonthlyCostReport();
}

void testPlanComparison() {
    cout << "\n=== Testing Plan Comparison ===" << endl;
    
    CostExplorer explorer;
    
    // Compare plans for different user counts
    vector<int> userCounts = {10, 50, 150, 1000};
    
    for (int userCount : userCounts) {
        explorer.printPlanComparison(userCount);
    }
}

void testUpgradeScenario() {
    cout << "\n=== Testing Upgrade Scenario ===" << endl;
    
    CostExplorer explorer;
    
    // Start with standard plan
    explorer.addSubscription(STANDARD, MONTHLY, 25);
    
    cout << "Initial setup:" << endl;
    explorer.printCurrentSubscriptions();
    
    double initialCost = explorer.calculateYearlyCost();
    cout << "Initial yearly cost: $" << fixed << setprecision(2) << initialCost << endl;
    
    // Upgrade to premium
    explorer.upgradePlan(0, PREMIUM);
    
    cout << "\nAfter upgrade to Premium:" << endl;
    explorer.printCurrentSubscriptions();
    
    double upgradedCost = explorer.calculateYearlyCost();
    cout << "Upgraded yearly cost: $" << fixed << setprecision(2) << upgradedCost << endl;
    cout << "Additional cost: $" << fixed << setprecision(2) << (upgradedCost - initialCost) << endl;
    
    // Increase user count
    explorer.changeUserCount(0, 50);
    
    cout << "\nAfter increasing users to 50:" << endl;
    explorer.printCurrentSubscriptions();
    
    double finalCost = explorer.calculateYearlyCost();
    cout << "Final yearly cost: $" << fixed << setprecision(2) << finalCost << endl;
}

int main() {
    testBasicCostCalculation();
    testMultiplePlans();
    testPlanComparison();
    testUpgradeScenario();
    
    return 0;
}
