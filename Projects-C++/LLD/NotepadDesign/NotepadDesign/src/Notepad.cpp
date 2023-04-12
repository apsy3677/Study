#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Notepad
{
public:
   vector<string> content;
   stack<vector<string>> undoStack;
   stack<vector<string>> redoStack;
   vector<string> clipBoard;

   vector<string> split(const string& text, const char delim)
   {
      vector<string> res;

      auto pos = text.find( delim );
      auto i = 0;

      while(pos != string::npos )
      {
         res.push_back( text.substr( i, pos - i ) );
         i = ++pos;
         pos = text.find( delim, pos );
      }
      res.push_back( text.substr( i, text.length() ) );

      return res;
   }

   Notepad(string text)
   {
      content = split(text, '\n'); // if given delimeters
   }

   void display()
   {
      for(string &line : content )
      {
         cout << line << endl;
      }
   }
   bool display(int n, int m)
   {
      bool value = false;
      if( checkBoundries( n, m, value ) ) return value;
      for( auto it = content.begin() + n-1 ; it != content.begin() +m ; it++ )
      {
         cout << *it << "\n";
      }
      return true;
   }

   bool insert(int n, string text)
   {
      bool value = false;
      if( checkBoundries( n, n, value ) ) return value;
      undoStack.push( content );

      auto cont = content.begin() + n - 1;
      (*cont) += text;
      return true;
   }
   bool delete_(int n ){
      bool value = false;
      if( checkBoundries( n, n, value ) ) return value;
      undoStack.push( content );
      content.erase( content.begin() + n - 1 );
      return true;
   }

   bool checkBoundries(int n, int m, bool& value)
   {
      if( static_cast< size_t >( n ) > content.size() )
      {
         cout << " Value of n exceeds number of lines in file\n";
         value = false;
         return true;
      }
      if( static_cast< size_t >( m ) > content.size() )
      {
         cout << " Value of m exceeds number of lines in file\n";
         value = false;
         return true;
      }
      if( n > m )
      {
         cout << "value of n is greater than m\n";
         value = false;
         return true;
      }
      return false;
   }

   bool delete_(int n, int m)
   {
      bool value = false;
      if (checkBoundries(n, m, value)) return value;

      undoStack.push( content );
      content.erase( content.begin() + n - 1, content.begin() + m);
      return true;
   }

   bool copy(int n, int m)
   {
      bool value = false;
      if( checkBoundries( n, m, value ) ) return value;

      clipBoard.clear();
      for( auto it = content.begin() + n - 1; it != content.begin() + m; it++ )
      {
         clipBoard.push_back( *it );
      }
      return true;

   }

   bool paste(int n)
   {
      bool value = false;
      if( checkBoundries( n, n, value ) ) return value;

      undoStack.push( content );
      content.insert( content.begin() + n - 1, content.begin(), content.end() );
      return true;
   }

   bool undo()
   {
      if(undoStack.empty() )
      {
         cout << "Nothing to undo \n";
         return false;
      }
      redoStack.push( content );

      content = undoStack.top();
      undoStack.pop();
      return true;
   }

   bool redo()
   {
      if(redoStack.empty() )
      {
         cout << "Nothing to Redo!\n";
         return false;
      }
      undoStack.push( content );

      content = redoStack.top();
      redoStack.pop();
      return true;
   }
};

int main()
{
   cout << " Notepad Design " << endl;

   Notepad notepad( "At the starting of the week\nAt summit talks you'll hear them speak\nIt's only Monday" );
   notepad.display();
   cout << "**************************** 0 ***********************************\n";
   cout << "** Displaying content: only first two lines **\n";
   notepad.display( 1, 2 );
   cout << "**************************** 1 ***********************************\n";
   cout << "** Inserting yeah to the first line **\n";
   notepad.insert( 1, ", Yeah" );
   notepad.display();
   cout << "**************************** 2 ***********************************\n";
   cout << "** Undoing last move **\n";
   notepad.undo();
   notepad.display();
   cout << "***************************** 3 *********************************\n";
   cout << "** Redoing last move **\n";
   notepad.redo();
   notepad.display();
   cout << "****************************** 4 *******************************\n";
   cout << "** Redoing last move **\n";
   notepad.redo();
   cout << "******************************** 5 ****************************\n";
   cout << "** Deleting first line **\n";
   notepad.delete_( 1 );
   notepad.display();
   cout << "******************************* 6 ****************************\n";
   cout << "** Undoing last move **\n";
   notepad.undo();
   notepad.display();
   cout << "******************************* 7 ***************************\n";
   cout << "** Undoing last move **\n";
   notepad.undo();
   notepad.display();
   cout << "**************************** 8 ***********************************\n";
   cout << "** After deletion of lines 1 to 2 **\n";
   notepad.delete_( 1, 2 );
   notepad.display();
   cout << "***************************** 9 ****************************\n";
   cout << "** Undoing last move **\n";
   notepad.undo();
   notepad.display();
   cout << "***************************** 10 ***************************\n";
   cout << "** Copying lines 1 to 2 and pasting them on 3rd line **\n";
   notepad.copy( 1, 2 );
   notepad.paste( 3 );
   notepad.display();
   cout << "***************************** 11 **************************\n";
   cout << "** Undoing last move **\n";
   notepad.undo();
   notepad.display();
   cout << "****************************** 12 ************************\n";
   cout << "** Redoing last move **\n";
   notepad.redo();
   notepad.display();
   return 0;
}