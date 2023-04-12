#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

using namespace std;

enum Item {Food, Beverage};

enum Food{Sandwich, Poha, Vada, Burger};
enum Beverage{Tea, Coffee, Water};

typedef pair<int, int> item;

class Store
{
public:
   string id;
   map<item, int> itemSupply;
   // unordered_map<int, int> beverageSupply;
   map<item, int> unitSold;
   // unordered_map<int, int> beverageUnitSold;
   map<item, int> itemRates;
   // unordered_map<int, int> beverageRates;

   string getUniqueId()
   {
      static int id = 0;
      return "store" + to_string( id++ );
   }

   Store(vector<pair<int,int>> &food, vector < pair<int, int>>& beverage)
   {
      this->id = getUniqueId();
      for( auto f : food )
         itemSupply[ {Item::Food,f.first} ] = f.second;
      for( auto f : food )
         itemSupply[ {Item::Beverage, f.first} ] = f.second;
   }

   void purchaseItem(Item type, int val, int qty)
   {
      item it = { type, val };
      if( itemSupply[it] <qty )
      {
         cout << "Not Enough Stock\n";
         return;
      }
      cout << "purchasing... \n";
      itemSupply[ it ] -= qty;
      unitSold[ it ] += qty;
      cout << "purchasing... complete \n";
   }

   void setItemRates( map<item, int> &itemRates)
   {
      this->itemRates = itemRates;
   }
};

class City
{
public:
   string id;
   map<item, int> itemRates;
   list<Store> stores;
   unordered_map<string, list<Store>::iterator> storeIdMap;

   string getUniqueId()
   {
      static int id = 0;
      return "city" + to_string( id++ );
   }

   City(vector<item> &foodRates, vector<item> &beverageRates)
   {
      this->id = getUniqueId();
      for(auto &f : foodRates )
      {
         item it = { Item::Food, f.first };
         itemRates[ it ] = f.second;
      }
      for( auto& f : beverageRates )
      {
         item it = { Item::Beverage, f.first };
         itemRates[ it ] = f.second;
      }
   }
   void addStore(Store &store)
   {
      store.setItemRates( this->itemRates );

      stores.push_front( store );
      storeIdMap[ store.id ] = stores.begin();
   }

   void purchaseItem(string storeId, Item type, int itemval, int qty)
   {
      if(storeIdMap.find(storeId) == storeIdMap.end() )
      {
         cout << " Store not found in city " << this->id << endl;
         return;
      }
      auto& it = storeIdMap[ storeId ];
      it->purchaseItem( type, itemval, qty );
   }
};

class State
{
public:
   string id;
   list<City> cities;
   unordered_map<string, list<City>::iterator> cityIdMap;

   string getUniqueId()
   {
      static int id = 0;
      return "state" + to_string( id++ );
   }

   State()
   {
      this->id = getUniqueId();
   }

   void addCity(City & city)
   {
      cities.push_front( city );
      cityIdMap[ city.id ] = cities.begin();
   }

   void purchaseItem(string cityId, string storeId, Item type, int val, int qty)
   {
      if( cityIdMap.find( cityId ) == cityIdMap.end() )
      {
         cout << " City Not found in State " << this->id << endl;
         return;
      }
      auto& it = cityIdMap[ cityId ];
      it->purchaseItem( storeId, type, val, qty );
   }
};

class System
{
public:
   list<State> states;
   unordered_map<string, list<State>::iterator> stateIdMap;

   System(){}

   void addState(State &state)
   {
      states.push_front( state );
      stateIdMap[ state.id ] = states.begin();
   }

   void purchaseItem(string stateId, string cityId, string storeId, Item type, int val, int qty )
   {
      if(stateIdMap.find(stateId) == stateIdMap.end() )
      {
         cout << " State not present " << stateId << endl;
         return;
      }
      auto& it = stateIdMap[ stateId ];
      it->purchaseItem( cityId, storeId, type, val, qty );
   }
};

int main()
{
   cout << "Sales Management System" << endl;
   vector<pair<int, int>> foodSupply;
   vector<pair<int, int>> beverageSupply;

   for( int i = 0; i < Food::Burger; ++i )
   {
      foodSupply.push_back( { i, i + 1 } );
      beverageSupply.push_back( { i, i + 1 } );
   }

   foodSupply.push_back( { 3, 4 } );

   Store store( foodSupply, beverageSupply );
   City city( foodSupply, beverageSupply ); // this is rate as well
   city.addStore( store );

   State state;
   state.addCity( city );

   System system;
   system.addState( state );

   string state1 = "state0";
   string city1 = "city0";
   string store1 = "store0";

   system.purchaseItem( state1, city1, store1, Item::Food, Food::Burger, 2 );

   // get food units sold for store0
   // these checks should be validated first as we are accessing them directly in map
   auto& itState = system.stateIdMap[ state1 ];

   auto& itCity = itState->cityIdMap[ city1 ];

   auto& itStore = itCity->storeIdMap[ store1 ];

   for( auto& it : itStore->unitSold )
   {
      cout << it.first.first << " " << it.first.second << " " << it.second << " ";
   } cout << endl;

   system.purchaseItem( state1, city1, store1, Item::Food, Food::Burger, 3 );

   return 0;
}