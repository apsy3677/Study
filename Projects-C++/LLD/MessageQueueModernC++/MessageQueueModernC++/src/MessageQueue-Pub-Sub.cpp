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
   condition_variable m_cond;

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
      while( m_queue.empty() )
      {
         m_cond.wait( lock ); // understand it more
      }
      // m_cond.wait( lock,  [(this->m_queue)] {
      //    return !m_queue.empty();
      // });
      Message msg = m_queue.front();
      m_queue.pop();
      return msg;
   }
};

class IPublisher
{
public:
   virtual void send(const Message& msg) = 0;
   virtual ~ IPublisher(){}
};

class ISubscriber
{
public:
   virtual void receive( const Message& msg ) = 0;
   virtual ~ISubscriber(){}
};

class Publisher : public IPublisher
{
   MessageQueue& m_queue;
public:
   Publisher( MessageQueue& queue ) : m_queue( queue ){}
   void send( const Message& msg ) override
   {
      m_queue.push( msg );
   }
};
mutex m_print_mutex;

class Subscriber : public ISubscriber
{
   MessageQueue& m_queue;

public:
   Subscriber( MessageQueue& queue ) : m_queue( queue ){}

   void receive(const Message& msg) override
   {
      unique_lock<mutex> lock( m_print_mutex ); // only for printing purpose
      cout << " received message " << msg.id << " : " << msg.data << endl;
      lock.unlock();
   }
};

int main()
{
   cout << "Message Queue \n";

   MessageQueue queue;

   // Publisher publisher( queue );

   unique_ptr<IPublisher> publisher = make_unique<Publisher>( queue );

   unique_ptr<ISubscriber> sub1 = make_unique<Subscriber>( queue );
   unique_ptr<ISubscriber> sub2 = make_unique<Subscriber>( queue );

   thread sub1_thread( [&]()
   {
      while(true )
      {
         Message msg = queue.pop();
         sub1->receive( msg );
      }
   }); // function name + *this as *this is first argument for a member function
   thread sub2_thread( [&]( )
   {
      while( true )
      {
         Message msg = queue.pop();
         sub2->receive( msg );
      }
   } ); // function name + *this as *this is first argument for a member function

   for( int i = 0; i <= 100; i++ )
   {
      Message msg { i, "Message" + to_string( i ) };
      publisher->send( msg );
   }

   sub1_thread.join();
   sub2_thread.join();

   return 0;
}