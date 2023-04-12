#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

enum User
{
	ROOT, ADMIN, USER
};
enum SchedulingAlgorithm
{
	FCFS, SJF, FPS, EDF
};

class Job
{
public:
	Job( string name, int duration, int priority, int deadline, User user )
	{
		this->id = getUniqueId();
		this->name = name;
		this->duration = duration;
		this->priority = priority;
		this->deadline = deadline;
		this->user = user;
	}

	int id;
	string name;
	int duration;
	int priority;
	int deadline;
	User user;
	int getUniqueId()
	{
		static int id = 1;
		return id++;
	}
};
// comparisons are done with respect to priority queue greater<> gives minHeap and less<> gives maxheap
// Therefore Comparisons are of this way
struct fcfsComparator
{
	bool operator()( const Job& lhs, const Job& rhs ) const
	{
		return lhs.id > rhs.id;
	}
};
struct sjfComparator
{
	bool operator()( const Job& lhs, const Job& rhs ) const
	{
		return lhs.duration > rhs.duration
			|| ( lhs.duration == rhs.duration &&
				lhs.priority > rhs.priority );
	}
};
struct fpsComparator
{
	bool operator()( const Job& lhs, const Job& rhs ) const
	{
		return lhs.priority > rhs.priority
			|| ( lhs.priority == rhs.priority &&
				lhs.user > rhs.user )
			|| ( lhs.priority == rhs.priority &&
				lhs.user == rhs.user &&
				lhs.duration < rhs.duration );
	}
};
struct edfComparator
{
	bool operator()( const Job& lhs, const Job& rhs ) const
	{
		return lhs.deadline > rhs.deadline
			|| ( lhs.deadline == rhs.deadline &&
				lhs.priority > rhs.priority )
			|| ( lhs.deadline == rhs.deadline &&
				lhs.priority == rhs.priority &&
				lhs.duration > rhs.duration );
	}
};
class Scheduler
{
	vector<Job> jobs;
	priority_queue<Job, vector<Job>, fcfsComparator> fcfsQueue;
	priority_queue<Job, vector<Job>, sjfComparator> sjfQueue;
	priority_queue<Job, vector<Job>, fpsComparator> fpsQueue;
	priority_queue<Job, vector<Job>, edfComparator> edfQueue;
public:
	Scheduler()
	{
	}
	void addJob( Job &job)
	{
		jobs.push_back( job );
		// push to all the PQs for each Algorithm
		fcfsQueue.push( job );
		sjfQueue.push( job );
		fpsQueue.push( job );
		edfQueue.push( job );
	}

	void processThreads( vector<int>& threadCapacity )
	{
		int minElement = *min_element( threadCapacity.begin(), threadCapacity.end() );
		// min time taken by threads to complete one job
		for( size_t i = 0; i < threadCapacity.size(); ++i )
		{
			// reduce this time from each and every thread as it is the minimum
			threadCapacity[ i ] -= minElement;
		}
	}

	vector<vector<Job>> getSchedulingSequence( SchedulingAlgorithm algorithm, int threads)
	{
		vector<vector<Job>> schedule;
		schedule.resize( threads );

		vector<int> threadCapacity( threads, 0 );
		vector<int> totalTimeTaken( threads, 0 );

		switch( algorithm )
		{
		case SchedulingAlgorithm::FCFS:
			while( fcfsQueue.empty() == false )
			{
				// check if thread is idle
				for( int i = 0; i < threads; ++i )
				{
					// if thread is idle we can assign a process to the thread 
					if( threadCapacity[ i ] == 0 )
					{
						if( fcfsQueue.empty() == false )
						{
							Job job = fcfsQueue.top();
							schedule[ i ].push_back( job );
							threadCapacity[ i ] += job.duration;
							fcfsQueue.pop();
						}
					}
				}
				// process the jobs using the treads 
				processThreads( threadCapacity );
			}
				break;
		case SchedulingAlgorithm::SJF:
			while( sjfQueue.empty() == false )
			{
				for( int i = 0; i < threads; ++i )
				{
					if( threadCapacity[ i ] == 0 )
					{
						if( sjfQueue.empty() == false )
						{
							Job job = sjfQueue.top();
							schedule[ i ].push_back( job );
							threadCapacity[ i ] += job.duration;
							sjfQueue.pop();
						}
					}
				}
				processThreads( threadCapacity );
			}
			break;
		case SchedulingAlgorithm::FPS:
			while( fpsQueue.empty() == false )
			{
				for( int i = 0; i < threads; ++i )
				{
					if( threadCapacity[ i ] == 0 )
					{
						if( fpsQueue.empty() == false )
						{
							Job job = fpsQueue.top();
							schedule[ i ].push_back( job );
							threadCapacity[ i ] += job.duration;
							fpsQueue.pop();
						}
					}
				}
				processThreads( threadCapacity );
			}
			break;
		case SchedulingAlgorithm::EDF:
			while( edfQueue.empty() == false )
			{
				for( int i = 0; i < threads; ++i )
				{
					if( threadCapacity[ i ] == 0 )
					{
						if( edfQueue.empty() == false )
						{
							Job job = edfQueue.top();
							totalTimeTaken[ i ] += job.duration;
							if( totalTimeTaken[ i ] <= job.deadline )
								schedule[ i ].push_back( job );
							else
								totalTimeTaken[ i ] -= job.duration;

							threadCapacity[ i ] += job.duration;
							edfQueue.pop();
						}
					}
				}
				processThreads( threadCapacity );
			}
			break;
		default:
			break;
		}

		return schedule;
	}
};

int main()
{
	cout << " Job Scheduler\n";
	Job j1( "J1", 10, 0, 10, User::ROOT );
	Job j2( "J2", 20, 0, 40, User::ADMIN );
	Job j3( "J3", 15, 2, 40, User::ROOT );
	Job j4( "J4", 30, 1, 40, User::USER );
	Job j5( "J5", 10, 2, 30, User::USER );

	Scheduler scheduler;
	scheduler.addJob( j1 );
	scheduler.addJob( j2 );
	scheduler.addJob( j3 );
	scheduler.addJob( j4 );
	scheduler.addJob( j5 );

	cout << "************************************ FCFS ***********************************" << endl;

	vector<vector<Job>> res = scheduler.getSchedulingSequence( SchedulingAlgorithm::FCFS, 2 );

	for( size_t i = 0; i < res.size(); ++i )
	{
		vector<Job> temp = res[ i ];
		for( Job job : temp )
			cout << job.name.c_str() << " ";
		cout << endl;
	}

	res = scheduler.getSchedulingSequence( SchedulingAlgorithm::FCFS, 2 );

	for( size_t i = 0; i < res.size(); ++i )
	{
		vector<Job> temp = res[ i ];
		for( Job job : temp )
			cout << job.name.c_str() << " ";
		cout << endl;
	}

	cout << "************************************ SJF ************************************" << endl;

	res = scheduler.getSchedulingSequence( SchedulingAlgorithm::SJF, 2 );

	for( size_t i = 0; i < res.size(); ++i )
	{
		vector<Job> temp = res[ i ];
		for( Job job : temp )
			cout << job.name.c_str() << " ";
		cout << endl;
	}

	cout << "************************************ FPS ************************************" << endl;

	res = scheduler.getSchedulingSequence( SchedulingAlgorithm::FPS, 2 );

	for( size_t i = 0; i < res.size(); ++i )
	{
		vector<Job> temp = res[ i ];
		for( Job job : temp )
			cout << job.name.c_str() << " ";
		cout << endl;
	}

	cout << "************************************ EDF ************************************" << endl;

	res = scheduler.getSchedulingSequence( SchedulingAlgorithm::EDF, 2 );

	for( size_t i = 0; i < res.size(); ++i )
	{
		vector<Job> temp = res[ i ];
		for( Job job : temp )
			cout << job.name.c_str() << " ";
		cout << endl;
	}

	return 0;
}