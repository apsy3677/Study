#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

class Task;
class User;

enum TaskType
{
	STORY, FEATURE, BUG
};
enum TaskStatus
{
	OPEN, IN_PROGRESS, RESOLVED, DELAYED, COMPLETED
};

class Task
{
public:
	int id;
	Task()
	{
		this->id = getUniqueId();
		this->taskStatus = TaskStatus::OPEN;
	}
	void setSubtract( const string& subtract )
	{
		this->subtract = subtract;
	}
	void setTaskStatus( TaskStatus taskStatus )
	{
		this->taskStatus = taskStatus;
	}
	void setTaskType( TaskType taskType )
	{
		this->taskType = taskType;
	}
	void setUser( int userId )
	{
		this->userId = userId;
	}

   void printDetails()
	{
		cout << this->id << "|" << this->taskType << "|" << taskStatus << "::";
	}

private:
	
	string subtract; // description
	int userId;
	TaskType taskType;
	TaskStatus taskStatus;
	int getUniqueId()
	{
		static int id = 1;
		return id++;
	}
};


class Sprint
{
public:
	Sprint( int begin, int end, string name )
	{
		this->id = getUniqueId();
		this->begin = begin;
		this->end = end;
		this->name = name;
	}
	void addTask( Task* task)
	{
		tasks.push_front( task );
		taskIdMap[ task->id ] = tasks.begin();
	}
	void printDetails() const
   {
		cout << "Sprint Name: " << this->name << "\nSprint Begins: " << this->begin << "\nSprint Ends: " << this->end << endl;
	}
	bool operator==( Sprint sprint ) const
   {
		return ( this->begin == sprint.begin ) && ( this->end == sprint.end ) && ( this->name == sprint.name );
	}
	void removeTask( int taskNumber )
	{
	   if( taskIdMap.count(taskNumber) ==0 )
	   {
			cout << " taskNumber does not exist " << taskNumber << endl;
			return;
	   }

		tasks.erase( taskIdMap[ taskNumber ] );
		taskIdMap.erase( taskNumber );
	}
	void printDetails()
	{
		cout << this->name << endl;
		for(auto task : tasks )
		{
			task->printDetails();
		}
		cout << endl;
	}
	int id;
	list<Task*> tasks;
private:
	int begin, end;
	string name;

	unordered_map<int, list<Task*>::iterator> taskIdMap; // makes deletion O(1), searching O(1)

	int getUniqueId()
	{
		static int id = 1;
		return id++;
	}
};

class User
{
private:
	
	list<Task> taskList;
	unordered_map<int, Task*> taskMap;
	list<Sprint> sprintList;
	unordered_map<int, Sprint*> sprintMap;
	string name;
public:
	int id;
   int getUniqueId()
   {
		static int id = 1;
		return id++;
   }

	User(string name)
	{
		this->id = getUniqueId();
		this->name = name;
	}
	Task createTask( TaskType taskType)
   {
		Task task;
		task.setUser( this->id );
		task.setTaskType( taskType );
		taskList.push_back( task );
		taskMap[ task.id ] = &taskList.back();
		return taskList.back();
   }
	Task createTask( string subtract)
   {
		Task task;
		task.setTaskType( TaskType::STORY );
		task.setSubtract( subtract );
		task.setUser( this->id );
		taskList.push_back( task );
		taskMap[ task.id ] = &taskList.back();

		return taskList.back();
   }
	Sprint createSprint( int begin, int end, string name)
   {
		Sprint s( begin, end, name );
		sprintList.push_back( s );
		sprintMap[ s.id ] = &sprintList.back();

		return sprintList.back();
   }
	bool addToSprint( Sprint& sprint, Task&  task)
   {
		int s_id = sprint.id;

		if( sprintMap.count(s_id) == 0)
		{
			cout << " Sprint does not exist for user " << endl;
			return false;
		}
		if( taskMap.count( task.id ) == 0 )
		{
			cout << " task.id  does not exist for user " << endl;
			return false;
		}
		sprintMap[ s_id ]->addTask( taskMap[task.id]);
		return true;
   }
	bool removeFromSprint( Sprint& sprint, Task& task)
   {
		int s_id = sprint.id;

		if( sprintMap.count( s_id ) == 0 )
		{
			cout << " Sprint does not exist for user " << endl;
			return false;
		}
		sprintMap[ s_id ]->removeTask( task.id );
		return true;
   }
	void printAllTasks()
   {
		cout << this->name << " \n";
		for( Task &task : taskList )
		{
			task.printDetails();
		}
		cout << endl;
		for(Sprint &s: sprintList )
		{
			s.printDetails();
		}
		cout << endl;
   }
	bool changeStatus( Task& task, TaskStatus taskStatus)
   {
      if(taskMap.count(task.id) ==0)
      {
			cout << " No such task present " << endl;
			return false;
      }
		taskMap[ task.id ]->setTaskStatus( taskStatus );
		return true;
   }
};

int main()
{
   cout << " Jira System " << endl;

	User user1("U1"), user2("U2");
	Task task1 = user1.createTask( TaskType::FEATURE );
	Task task11 = user1.createTask( TaskType::BUG );
	Task task2 = user2.createTask( TaskType::BUG );
	Task task22 = user2.createTask( "This is a subtract" );

	Sprint sprint1 = user1.createSprint( 22, 33, "Sprint1" );
	Sprint sprint2 = user2.createSprint( 44, 55, "Sprint2" );

	cout << user1.changeStatus( task11, TaskStatus::IN_PROGRESS ) << endl;//1

	cout << user1.addToSprint( sprint1, task1 ) << "\n"; //1
	cout << user1.addToSprint( sprint1, task11 ) << "\n"; //1
	cout << user1.addToSprint( sprint2, task1 ) << "\n"; //0
	// cout << user1.removeFromSprint( sprint1, task11 ) << "\n"; //1
	cout << user2.addToSprint( sprint1, task1 ) << "\n"; //0
	cout << user2.removeFromSprint( sprint1, task2 ) << "\n"; //0
	cout << user2.addToSprint( sprint2, task1 ) << "\n"; //1
	cout << user2.addToSprint( sprint2, task2 ) << "\n"; //1

	cout << "Sprint1 details " << endl;
	sprint1.printDetails();
	cout << endl;
	cout << "Users details " << endl;
	user1.printAllTasks();
	user2.printAllTasks();
   return 0;
}