#include<iostream>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

enum Category{
   FICTION, SCI_FI, MYSTERY, FABLE, MYTHOLOGY,C1,C2,C3,c4 };

class Book
{
public:
   int id;
   string name;
   string author;
   string publisher;
   Category category;
   double price;
   int sold;
   int count;
   int publishYear;

   int getUniqueId()
   {
      static int id = 1;
      return id++;
   }

   Book( string name, string author, string publisher, int publishYear, Category category, double price, int count )
   {
      this->id = getUniqueId();
      this->name = name;
      this->author = author;
      this->publisher = publisher;
      this->publishYear = publishYear;
      this->category = category;
      this->price = price;
      this->count = count;

   }
};

class Catalog
{
public:
   Catalog()
   {
   }
   void addBookToCatalog( Book& book)
   {
      books.push_back( book );
      authorMap[ book.author ].first.push_back( &books.back() );
      authorMap[ book.author ].second.push( { book.count, &books.back() } );
      categoryMap[ book.category ].push( { book.count, &books.back() } );
   }
   vector<Book> searchBookByName( string name)
   {
      vector<Book> bookList;

      for(auto &book : books )
      {
         // check name matches prefix of other books
         if(book.name.substr(0,name.size()) == name )
         {
            bookList.push_back( book );
         }
      }
      return bookList;
   }
   vector<Book> searchBookByAuthor( string name)
   {
      vector<Book> bookList;

      for(auto &it : authorMap )
      {
         auto author = it.first;
         if(author.substr(0, name.size()) == name )
         {
            auto booksByAuthor = it.second.first; // second->first is vector<Book *>
            for(auto book : booksByAuthor )
            {
               bookList.push_back( *book );
            }
         }
      }
      return bookList;
   }
   vector<Book> getMostSoldBooksByAuthor( string name, int limit)
   {
      vector<Book> bookList;
      vector<Book*> removedBooks;

      auto &pq = authorMap[ name ].second;

      while(!pq.empty() && limit-- )
      {
         Book* book = pq.top().second;
         removedBooks.push_back( book );
         bookList.push_back( *book );

         pq.pop();
      }
      for( auto& book : removedBooks )
      {
         pq.push( { book->count, book } );
      }
      return bookList;
   }
   vector<Book> getMostSoldBooksByCategory( Category category, int limit )
   {
      vector<Book> bookList;
      vector<Book *> removedBooks;

      auto &pq = categoryMap[ category ];
      // auto &pq = categoryMap[ category ];

      while(!pq.empty() && limit-- )
      {
         Book* book = pq.top().second;
         removedBooks.push_back( book );
         bookList.push_back( *book );

         pq.pop();
      }
      for(auto &book : removedBooks )
      {
         pq.push({book->count, book} );
      }
      return bookList;
   }
private:
   list<Book> books;
   typedef priority_queue<pair<int, Book*>, vector<pair<int, Book*>>, less<pair<int, Book*>>> countQueue;
   unordered_map<string, pair<vector<Book*>, countQueue>> authorMap;
   unordered_map<Category, countQueue> categoryMap;
};

int main()
{
   cout << "Books catalog\n";

   Book book( "HP & The PS", "J K Rowling", "Bloomsbury", 1997, Category::FICTION, 200, 80 );
   Book book1( "HP & The COS", "J K Rowling", "Bloomsbury", 1998, Category::FICTION, 1000, 100 );
   Book book2( "HP & The POA", "J K Rowling", "Bloomsbury", 1999, Category::FICTION, 2000, 500 );
   Book book3( "HP & The HBP", "J K Rowling", "Bloomsbury", 2005, Category::FICTION, 3000, 700 );
   Book book4( "The Immortals of Meluha", "Amish", "Westland", 2010, Category::MYTHOLOGY, 1500, 600 );
   Book book5( "The Secret of the Nagas", "Amish", "Westland", 2011, Category::MYTHOLOGY, 2500, 400 );
   Book book6( "The Oath of the Vayuputras", "Amish", "Westland", 2013, Category::MYTHOLOGY, 3500, 200 );
   Book book7( "Do Androids dream of Electric Sheep", "Philip K Dick", "DoubleDay", 1968, Category::SCI_FI, 30, 20 );

   Catalog catalog;
   catalog.addBookToCatalog( book );
   catalog.addBookToCatalog( book1 );
   catalog.addBookToCatalog( book2 );
   catalog.addBookToCatalog( book3 );
   catalog.addBookToCatalog( book4 );
   catalog.addBookToCatalog( book5 );
   catalog.addBookToCatalog( book6 );
   catalog.addBookToCatalog( book7 );

   vector<Book> list = catalog.getMostSoldBooksByAuthor( "Amish", 2 );
   for( Book book : list )
      cout << book.name << " " << book.count << endl;

   cout << "**************************************************************************************\n";

   list = catalog.getMostSoldBooksByAuthor( "Amish", 2 );
   for( Book book : list )
      cout << book.name << " " << book.count << endl;

   cout << "**************************************************************************************\n";

   list = catalog.getMostSoldBooksByCategory( Category::FICTION, 2 );
   for( Book book : list )
      cout << book.name << " " << book.count << endl;
   cout << "**************************************************************************************\n";

   list = catalog.searchBookByAuthor( "Amish" );
   for( Book book : list )
      cout << book.name << " " << book.count << endl;
   cout << "**************************************************************************************\n";

   list = catalog.searchBookByAuthor( "Amish" );
   for( Book book : list )
      cout << book.name << " " << book.count << endl;
   cout << "**************************************************************************************\n";

   list = catalog.searchBookByName( "Do" );
   for( Book book : list )
      cout << book.name << " " << book.count << endl;

   return 0;
}