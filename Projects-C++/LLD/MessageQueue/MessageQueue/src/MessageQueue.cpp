#include <iostream>
#include <queue>
#include <mutex>
#include <string>

using namespace std;

struct Message
{
   int id;
   string data;
};

class MessageQueue
{
   queue<Message> m_queue;
   mutex m_mutex;
   std::condition_variable m_cond;

public:

   void push( const Message& msg )
   {
      unique_lock<mutex> lock( m_mutex );
      m_queue.push( msg );
      lock.unlock();
      m_cond.notify_one();
   }

   Message pop()
   {
      unique_lock<mutex> lock( m_mutex );
      // while( m_queue.empty() )
      // {
      //    m_cond.wait(lock); // understand it more
      // }
      m_cond.wait( lock, [ this ]
      {
         return !m_queue.empty();
      } );
      Message msg = m_queue.front();
      m_queue.pop();
      return msg;
   }
};

class Publisher
{
   MessageQueue& m_queue;
public:
   Publisher( MessageQueue& queue ) : m_queue( queue )
   {

   }
   void send( const Message& msg )
   {
      m_queue.push( msg );
   }
};
mutex m_print_mutex;
class Subscriber
{
   MessageQueue& m_queue;
   int cnt;

public:
   Subscriber( MessageQueue& queue ) : m_queue( queue ), cnt( 0 )
   {

   }

   void receive()
   {
      while( true )
      {
         Message msg = m_queue.pop();
         unique_lock<mutex> lock( m_print_mutex );
         cout << " received message " << msg.id << " : " << msg.data << " " << ++cnt << endl;
         lock.unlock();
      }
   }
};

int main()
{
   cout << "Message Queue \n";

   MessageQueue queue;

   Publisher publisher( queue );

   Subscriber sub1( queue );
   Subscriber sub2( queue );

   thread sub1_thread( &Subscriber::receive, &sub1 ); // function name + *this as *this is first argument for a member function
   thread sub2_thread( &Subscriber::receive, &sub2 ); // function name + *this as *this is first argument for a member function

   for( int i = 0; i <= 100; i++ )
   {
      Message msg { i, "Message" + to_string( i ) };
      publisher.send( msg );
   }

   sub1_thread.join();
   sub2_thread.join();

   return 0;
}