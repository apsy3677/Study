#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

enum Split
{
   EQUAL,
   EXACT,
   PERCENTAGE
};
class User
{
   typedef pair<User, double> expense;
public:
   int id;
   string name;
   vector<expense> expenseHistory;
   double totalExpenseSoFar;
   unordered_map<int, double> expenseSheet;

   bool operator == (const User &user)
   {
      return this->id == user.id;
   }

   int getuniqueId()
   {
      static int userId = 0;
      return userId++;
   }

   User(string name)
   {
      id = getuniqueId();
      this->name = name;
      this->totalExpenseSoFar = 0.0;
      expenseHistory.clear();
      expenseSheet.clear();
   }
   void addExpense(const User &user, double amount)
   {
      if( this->id == user.id ) return;
      this->totalExpenseSoFar += amount;

      expenseSheet[ user.id ] += amount;
   }

   double getTotalExpense()
   {
      return this->totalExpenseSoFar;
   }

   void printTotalbalance()
   {
      if( totalExpenseSoFar > 0 )
         cout << this->name << " Owes total of " << totalExpenseSoFar << endl;
      else
         cout << this->name << " Gets Back total of " << totalExpenseSoFar * -1 << endl;

   }
};
class Expense
{
public:
   int id;
   string description;
   Split split;
   User *creditor;
   double amount;
   vector<double> exactDistribution;
   vector<double> percentageDistribution;
   vector<User> defaulters;

   int getUniqueId()
   {
      static int expenseId = 0;
      return expenseId++;
   }

   // revisit what to take exactly
   Expense(User &creditor, Split split, const double amount, vector<User>& defaulters, const string &description = "" )
   {
      id = getUniqueId();
      this->creditor = &creditor;
      this->description = description;
      this->amount = amount;
      this->defaulters = defaulters;
      if(split == Split::EQUAL )
      {
         
      }
      else if(split == Split::EXACT )
      {
         // exactDistribution = distribution;
      }
      else if(split == Split::PERCENTAGE )
      {
         // percentageDistribution = distribution;
      }
   }
};

class Splitwise
{
   bool VerifyUsers( User &user , vector<User> & users)
   {
      bool ret = true;
      if( find(users.begin(), users.end(), user) == users.end() )
         users.push_back(user);
      for(auto u : users )
      {
         if( IdUserMap.find( u.id ) == IdUserMap.end() )
            return false;
      }
      return ret;
   }

public:
   list<User> users;
   unordered_set<int> userIds;
   unordered_map<int, User*> IdUserMap;
   // unordered_map<int, User*> IdUserMap;

   Splitwise( vector<User> &users)
   {
      
   }

   Splitwise()
   {
      
   }

   void addExpense(Expense & expense)
   {
      if(!VerifyUsers(*expense.creditor, expense.defaulters) )
      {
         cout << "users are not valid " << endl;
         return;
      }
      calculateExpense(expense);
   }

   vector<double> divideEqual(double amount, int sz)
   {
      vector<double> parts;
      for(int i=0;i< sz;i++)
      {
         double part = trunc( 100.0 * amount / ( sz - i ) ) / 100.0;
         parts.push_back( part );
         amount -= part;
      }
      return parts;
      // return vector<double>( sz, amount / sz );

   }

   bool calculateExpense(Expense expense)
   {
      User creditor = *expense.creditor;
      vector<User> defaulters = expense.defaulters;
      vector<double> amtPerhead;

      switch(expense.split)
      {
         case Split::EQUAL:
            amtPerhead = divideEqual( expense.amount, (int)defaulters.size() );
            for( size_t i = 0; i < defaulters.size(); ++i )
            {
               auto it = find( users.begin(), users.end(), defaulters[ i ] );
               IdUserMap[ creditor.id ]->addExpense( defaulters[i], ( -1 ) * amtPerhead[i]);
               IdUserMap[ defaulters[i].id]->addExpense(creditor, amtPerhead[i]);
               // userIdMap[ creditor.getId() ]->addToUserExpenseSheet( defaulters[ i ], ( -1 ) * amtPerHead[ i ] );
               // userIdMap[ defaulters[ i ].getId() ]->addToUserExpenseSheet( creditor, amtPerHead[ i ] );
            }
            break;
         case Split::EXACT:
            amtPerhead = expense.exactDistribution;
            if( expense.amount != accumulate( amtPerhead.begin(), amtPerhead.end(), 0 ) )
            {
               cout << " Expense is wrong, provide correct expense " << endl;
               return false;
            }
            if(amtPerhead.size() != defaulters.size() )
            {
               cout << " defaulters are not equal to the expense provides\n";
               return false;
            }

            for( size_t i = 0; i < defaulters.size(); ++i )
            {
               IdUserMap[creditor.id]->addExpense(defaulters[i], (-1) * amtPerhead[i]);
               IdUserMap[defaulters[i].id]->addExpense(creditor, amtPerhead[i]);
               // userIdMap[creditor.getId()]->addToUserExpenseSheet(defaulters[i], (-1) * amtPerHead[i]);
               // userIdMap[defaulters[i].getId()]->addToUserExpenseSheet(creditor, amtPerHead[i]);
            }
            break;
         case Split::PERCENTAGE:
            amtPerhead = expense.percentageDistribution;
            if( 100.0 != accumulate( amtPerhead.begin(), amtPerhead.end(), 0.0 ) )
            {
               cout << " Percentage does not add to 100 % Expense is wrong, provide correct expense " << endl;
               return false;
            }
            if( amtPerhead.size() != defaulters.size() )
            {
               cout << " defaulters are not equal to the expense provides\n";
               return false;
            }

            for( size_t i = 0; i < defaulters.size(); ++i )
   		   {
   			   double amount = (amtPerhead[i] * expense.amount) / 100.0;
   			   amount = floor((amount * 100.0) + 0.5) / 100.0;
      
   			   IdUserMap[creditor.id]->addExpense(defaulters[i], (-1) * amount);
   			   IdUserMap[defaulters[i].id]->addExpense(creditor, amount);
   		   }
            break;
      }
      cout << "Balance After Add Expense " << endl;
      // printBalForAllUsers();
      return true;
   }
   void RegisterUser( User &user )
   {
      if( IdUserMap.find(user.id) == IdUserMap.end() )
      {
         users.push_back( user );
         // userIds.insert( user.id );
         IdUserMap[ user.id ] = &users.back();
      }
   }
   void printBalForAllUsers()
   {
      for(auto &user : users)
      {
         user.printTotalbalance();
      }
   }

   void simplifyExpenses()
   {
      vector<int> amounts;
      for( User& user : users )
      {
         amounts.push_back( ( -1 ) * user.totalExpenseSoFar );
      }

      pair<vector<int>::iterator, vector<int>::iterator> min_max = minmax_element( amounts.begin(), amounts.end() );

      while( *min_max.first !=0 and *min_max.second !=0 )
      {
         int min_index = min_max.first - amounts.begin();
         int max_index = min_max.second - amounts.begin();

         int min_amount = min( -amounts[ min_index ], amounts[ max_index ] );

         amounts[ min_index ] += min_amount;
         amounts[ max_index ] -= min_amount;

         auto it_min = users.begin();
         auto it_max = users.begin();

         advance( it_min, min_index );
         advance( it_max, max_index );

         cout << it_min->name << " pays the amount " << min_amount << " to " << it_max->name << endl;

         min_max = minmax_element( amounts.begin(), amounts.end() );
      }
   }
};
int main()
{
   cout << " SplitWise LLD " << endl;
   User u1( "U1" ), u2( "U2" ), u3( "U3" ), u4( "U4" ), u5( "U5" );
   vector<User> users = { u1,u2,u3,u4,u5 };

   Splitwise sp;

   for(auto &user : users )
   {
      sp.RegisterUser( user );
   }
   Expense expense( users[0], Split::EQUAL, 2000.0, users);
   sp.addExpense( expense );

   sp.printBalForAllUsers();

   sp.simplifyExpenses();
   return 0;
}