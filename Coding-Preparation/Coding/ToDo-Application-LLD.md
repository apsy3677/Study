Design a professional Todo application for both organisations and individuals
 
a.User should be able to create/modify/delete tasks
B.Tasks will be present under lists - Kind of folder
c.User should be able to have working dates,due dates, reminders for the tasks.
d.User should be able to mark a task as important/completed 
e.User should be able to share tasks with other employees of the organisation
f.Task may have file attachments

Users- individual, Enterprise 
CRUD Tasks
Status : completed, InProgress, Created, 
Priority : important, Default

Sharing : Only for premuim users (enterprise user in same orginization)

Tasks : working dates, due dates start date and end date 
Reminder for task : Can be set by users by the day/week/month/ particular date 
Notification to be sent by System to user on basis of config 

User -> ValidateUser -> taskView -> CRUD Tasks -> 
Open a Task -> Notificitaion/ Reminder, update task, attach files 
Share Task with other Orginization members

User{
    id: int
    premium : bool
}

EnterPriseUser : User{
    Organization : string
    // Take care of tasks 
}

Enum TaskStatus {completed, InProgress, Created}
Enum Priority  {Default, Important}
Task{
    id : int
    taskStatus : TaskStatus
    priority : Priority
    attachment : url // cloud link
    startTime : long
    endTime : long
    userid : int

    setStatus()
    setPriority()
    setstartTime ()
    setendTime ()
    setUser(userid)
}

List{
    id,
    userId, 
    list<taskId>  listtasks;

    addTaskToList()
    removetaskFromList()
}

ToDoSystem{
    list<Task> tasks;
    list<User> users;

    list<List> lists;
    unordered_map<userId, list<listId>> userListMap; 

    unordered_map<long, list<long>> usertasksMap; // mapping of userId to  userTasks

    <!-- User should be able to create/modify/delete tasks -->
    <!-- CRUD Operations for Creaing List -->

    <!-- CRUD Operations for Tasks -->

    <Setting Reminder>
    // Notofication System 
    <Sharing Tasks Within Organization>
    // ShareTasks
}


observer pattern Sending Notifications

Notification{

}
EmailNOtification : Notification{

}
whatsUpNOtification : Notification{

}

Notifications{

    subscribe(taskId, userId, notificationDetails)
    unsubscribe(taskId, userId, notificationDetails)
}

ShareTasks{

    ShareTask()
}