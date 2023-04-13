#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <string>

// Generic Message class that can be specialized for different message types
template<typename T>
class Message
{
public:
   Message( const T& data ) : m_data( data )
   {
   }
   T getData() const
   {
      return m_data;
   }
private:
   T m_data;
};

// Subscriber interface that can be implemented for different message types
template<typename T>
class Subscriber
{
public:
   virtual ~Subscriber()
   {
   }
   virtual void receive( const Message<T>& msg ) = 0;
};

// Publisher that can send messages of different types
class Publisher
{
public:
   template<typename T>
   void send( const T& data )
   {
      std::lock_guard<std::mutex> lock( m_mutex );
      m_queue.push( std::make_shared<Message<T>>( data ) );
      m_cond.notify_one();
   }

   void subscribe( std::shared_ptr<Subscriber<std::string>> subscriber )
   {
      std::lock_guard<std::mutex> lock( m_mutex );
      m_subscribers.push_back( subscriber );
   }

   void unsubscribe( std::shared_ptr<Subscriber<std::string>> subscriber )
   {
      std::lock_guard<std::mutex> lock( m_mutex );
      m_subscribers.erase( std::remove( m_subscribers.begin(), m_subscribers.end(), subscriber ), m_subscribers.end() );
   }

private:
   std::queue<std::shared_ptr<void>> m_queue;
   std::vector<std::shared_ptr<Subscriber<std::string>>> m_subscribers;
   std::mutex m_mutex;
   std::condition_variable m_cond;

   void notifySubscribers( std::shared_ptr<void> msg )
   {
      std::lock_guard<std::mutex> lock( m_mutex );
      for( auto& sub : m_subscribers )
      {
         sub->receive( *std::static_pointer_cast< Message<std::string> >( msg ) );
      }
   }

   void start()
   {
      while( true )
      {
         std::unique_lock<std::mutex> lock( m_mutex );
         m_cond.wait( lock, [ this ]
         {
            return !m_queue.empty();
         } );
         auto msg = m_queue.front();
         m_queue.pop();
         lock.unlock();
         notifySubscribers( msg );
      }
   }

   std::thread m_thread { [ this ]
{
start();
} };
};

// Subscriber implementation for messages of type int
class IntSubscriber : public Subscriber<int>
{
public:
   void receive( const Message<int>& msg ) override
   {
      std::cout << "Received int message: " << msg.getData() << std::endl;
   }
};

// Subscriber implementation for messages of type std::string
class StringSubscriber : public Subscriber<std::string>
{
public:
   void receive( const Message<std::string>& msg ) override
   {
      std::cout << "Received string message: " << msg.getData() << std::endl;
   }
};

int main()
{
   Publisher pub;
   std::shared_ptr<Subscriber<int>> intSub = std::make_shared<IntSubscriber>();
   std::shared_ptr<Subscriber<std::string>> stringSub = std::make_shared<StringSubscriber>();

   pub.subscribe( stringSub );
   // pub.subscribe( intSub );

   pub.send( "Hello, world!" );
   pub.send( 42 );

   // pub.unsubscribe( stringSub );
   pub.send( "This message should only be received by the int subscriber" );

   return 0;
}
