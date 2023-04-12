#include<iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

class Employee
{
public:
   int id;
   string name;
   int managerId;
   bool isManager;
   Employee* manager;
   list<Employee*> subordinates;

   Employee( Employee& manager, bool isManager )
   {
      this->isManager = isManager;
      this->manager = &manager;
   }

   int getUniqueId()
   {
      static int empId = 1;
      return empId++;
   }

   Employee(string name )
   {
      this->name = name;
      this->id = getUniqueId();
      this->isManager = false;
      this->manager = nullptr;
      this->managerId = 0;
   }
   void addSubordinate(Employee &emp)
   {
      this->subordinates.push_back( &emp );
   }
};

class System
{
public:
   list<Employee> employees;
   unordered_map<int, list<Employee>::iterator> empMap;

   System(){}

   void registerEmployee(Employee &emp)
   {
      employees.push_front( emp );
      empMap[ emp.id ] = employees.begin();
   }

   void registerManager(int empId, int managerId )
   {
      if( !empMap.count( empId ) || !empMap.count( managerId ) )
      {
         cout << "Either Employee or Manager not registered! Please provide correct registered identifiers to continue\n";
         return;
      }
      empMap[ empId ]->manager = &*(empMap[ empId ]->manager);
      empMap[ empId ]->managerId = managerId;
      empMap[ managerId ]->addSubordinate( *empMap[ empId ] );
   }

   void printDetails( int empId )
   {
      if( empMap.find( empId ) == empMap.end() )
      {
         cout << "Employee not registered! Please provide correct Id and retry\n";
         return;
      }

      cout << "Id: " << empId << "\t";
      cout << "Name: " << empMap[ empId ]->name << "\t";
      int magrId = empMap[ empId ]->managerId;
      if( empMap.find( magrId ) == empMap.end() )
      {
         cout << "Employee Does not have Manager!\n";
         return;
      }
      cout << "Manager: " << empMap[ magrId ]->name << endl;
   }

   list<Employee *> getSubordinates( int empId )
   {
      if( empMap.find( empId ) == empMap.end() )
      {
         cout << "Employee not registered! Please provide correct Id and retry\n";
         list<Employee *> dummy;
         return dummy;
      }

      return empMap[ empId ]->subordinates;
   }
   void printDetails( string prefix )
   {
      for( Employee employee : employees )
      {
         if( employee.name.substr( 0, prefix.size() ) == prefix )
         {
            cout << "Id: " << employee.id << "\tName: " << employee.name << "\t";
            cout << "Manager: " << empMap[ employee.managerId ]->name << endl;
         }
      }
   }

   list<Employee*> getSubordinates( string name )
   {
      for( Employee employee : employees )
      {
         if( employee.name == name )
            return employee.subordinates;
      }

      list<Employee*> dummy;
      return dummy;
   }
};

int main()
{
   std::cout << "Employee management System \n";

   Employee employee( "Achilees" );
   Employee employee1( "Hector" );
   Employee employee2( "Paris" );
   Employee employee3( "Helen" );

   System system;
   system.registerEmployee( employee );
   system.registerEmployee( employee1 );
   system.registerEmployee( employee2 );
   system.registerEmployee( employee3 );

   system.registerManager( employee1.id, employee.id );
   system.registerManager( employee2.id, employee.id );
   system.registerManager( employee3.id, employee.id );
   system.printDetails( employee1.id );

   cout << "********************************************************************\n";

   system.printDetails( "He" );

   cout << "********************************************************************\n";

   for( Employee *e : system.getSubordinates( employee.name ) )
   {
      cout << e->name << " " << e->id << endl;
   }

   cout << "********************************************************************\n";

   for( Employee* e : system.getSubordinates( employee.id ) )
   {
      cout << e->name << " " << e->id << endl;
   }

   cout << "********************************************************************\n";

   for( Employee* e : system.getSubordinates( employee1.name ) )
   {
      cout << e->name << " " << e->id << endl;
   }

   return 0;
}