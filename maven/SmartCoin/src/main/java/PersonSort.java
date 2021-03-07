import org.omg.CORBA.INTERNAL;

import java.text.SimpleDateFormat;
import java.util.*;

class DateComparator implements Comparator<Person>{

    public int compare(Person p1, Person p2){
        return p1.dob.compareTo(p2.dob);
    }
}

public class PersonSort {

    // creating HASH for persons
    public static HashMap<Date, Person> map = new HashMap<Date, Person>();
    public static HashMap<String, Integer> pState = new HashMap<>();

    public static void main() throws Exception {

        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        Person p1 = new Person(1, "Rohit",  sdf.parse("1992-02-21"));
        Person p2 = new Person(2, "Virat",  sdf.parse("1990-07-21"));
        Person p3 = new Person(3, "Jaspreet",  sdf.parse("1994-08-21"));

        List<Person> people = new ArrayList();
        people.add(p1);  people.add(p2); people.add(p3);
//million such entries will get added


        for (Person p: people){
            map.put(p.dob, p);
            Integer count = pState.containsKey(p.state) ? pState.get(p.state) : 0 ;
            pState.put(p.state, count +1 );
        }

        sort(people);
        find(people, sdf.parse("1992-02-28") );
    }

    static void sort(List<Person> people){
        Collections.sort(people, new DateComparator());

//        for(Person p: people){
//            System.out.println("p.id DOB " + p.id + " "+ p.dob);
//        }
    }

    static Person find(List<Person> people, Date dob){
        Person p = null;
        if(map.containsKey(dob)){
            p = map.get(dob);
        }
        return p;
    }

    static String maxState(List <Person> people){
        String ans = "";
        int count = 0;
        Iterator it = pState.entrySet().iterator();

        while(it.hasNext()){
            Map.Entry mapElement = (Map.Entry) it.next();
            int val = (Integer) mapElement.getValue();
            if(val > count){
                count = val;
                ans = (String)mapElement.getKey();
            }
        }

        return ans;
    }
}
