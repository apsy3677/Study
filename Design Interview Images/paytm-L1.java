// Examination: n questions, m students

// 5 students a,b,c,d,e
// 10 questions

// finite duration: 1 hour

// submission recording service: 

// b, d, a, d, b
// d, b, a 

// b 2, 4 
// d 2, 3
// a 1, 2

// rank students: 
// more submissions better rank
// in case of a tie, quicker to solve gets better rank

// 10^6 Students, 

//rank Students on basis of no of questions solved

Class Student{
    public int id;
    public int solved;
    public int time;
    
    Student(int id, int solved, int time){
    
    }
}

class Compartor implements Comparator<Student> {
    
    @Override 
    
    public int compare(Student s1, Student s2){
        if(s1.solved> s2.solved){
            -1;
        }else if(s1.solved < s2.solved){
            1;
        }else{
           if(s1.time < s2.time){
               return -1;
              }
              else{
                  return 1
              } 
        }
    }
}

List<Integer> rankStudents( List< Integer > studentList ){
    //hashmap
    // put in array
    
    HashMap<Integer, Student> map = new HashMap<> ();
    
    for(int i=0;i<studentList.size();i++){
        int id = studentList.get(i);
        if(!map.contains(id)){
            map.put( id, new Student(id,1,i) );
        }else{
            Student s = map.get(id);
            s.solved++;
            s.time = i;
        }
    }
    
    ArrayList<Student> students= new ArrayList<> ();
    
    Iterator it = map.entrySet().iterator();
    
    while(hmIterator.hasNext()){
       Map.Entry ele = (Map.Entry)it.next();
       
       students.add((Student)ele.getvalue());
       
        
    }
    
    Collections.sort(students, comparator);
    return students;
 }


