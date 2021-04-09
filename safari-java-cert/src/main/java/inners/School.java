package inners;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.function.Predicate;

//interface Predicate<E> {
//  boolean test(E e);
//}

@FunctionalInterface
interface Doubtful {
  void show();
//  void nope();
}

class SmartStudent implements Predicate<Student> {
  private int threshold;

  public SmartStudent(int threshold) {
    this.threshold = threshold;
  }

  @Override
  public boolean test(Student student) {
    return student.getGrade() > threshold;
  }
}

public class School {
//  public static List<Student> getSmart(List<Student> ls, int threshold) {
//    List<Student> rv = new ArrayList<>();
//    for (Student s : ls) { // ls.iterator() hasNext() next()
//      if (s.getGrade() > threshold) {
//        rv.add(s);
//      }
//    }
//    return rv;
//  }
//
//  public static List<Student> getEnthusiastic(List<Student> ls, int threshold) {
//    List<Student> rv = new ArrayList<>();
//    for (Student s : ls) {
//      if (s.getCourses().size() > threshold) {
//        rv.add(s);
//      }
//    }
//    return rv;
//  }

  public static List<Student> getByPredicate(List<Student> ls, Predicate<Student> ps) {
    List<Student> rv = new ArrayList<>();
    for (Student s : ls) {
      // behavior that takes Student as argument returns boolean
      if (ps.test(s)) {
        rv.add(s);
      }
    }
    return rv;
  }

  public static void showAll(List<Student> ls) {
    for (Student s : ls) {
      System.out.println("> " + s);
    }
    System.out.println("---------------");
  }

  public static void main(String[] args) {
    List<Student> roster = List.of(
        new Student("Fred", 70, "Math", "Physics"),
        new Student("Jim", 55, "Art"),
        new Student("Shiela", 95, "Math", "Physics", "Quantum mechanics", "Astrophysics")
    );
//    showAll(getSmart(roster, 65));
//    showAll(getEnthusiastic(roster, 2));

    showAll(getByPredicate(roster, new SmartStudent(65)));
    /*final */int threshold = 4;
    int [] thresholdValues = {4};
    Predicate<Student> unenthusiastic = new Predicate<Student>() {
      @Override
      public boolean test(Student student) {
        // "this" refers to the instance of Predicate
//        return student.getCourses().size() < threshold; // closure -- takes a copy
        return student.getCourses().size() < thresholdValues[0]; // closure -- takes a copy
      }
    };
//    threshold++; // must be final OR "effectively final"
    thresholdValues[0]++;
    showAll(getByPredicate(roster, unenthusiastic));
//    return unenthusiastic;

    // RHS MUST BE:
    // an object, that implements the Predicate<String> interface
    // WE ONLY WANT TO:
    // implement the single abstract method called test.
    // AND test is THE ONLY abstract method in Predicate
//    Predicate<Student> enthusiastic = /* new Predicate<Student>() { */
//      /*@Override
//      public boolean test*/(Student student) -> {
//        return student.getCourses().size() > 3;
//      }
//    /*}*/;
    // Lambda expressions v1
    // lambda can MUST provide EXACTLY ONE method
    // cannot provide constructors
    // briefer :)
    // NO NEW this context
    // MUST IMPLEMENT an *interface* (not subclasses, nor of abstracts..)
    // and that interface MUST define EXACTLY ONE abstract method
    Predicate<Student> enthusiastic = (Student student) -> {
      // this -> not valid (main is static)
      // in general, "this" refers to the same this as the enclosing context
        return student.getCourses().size() > threshold;
      } ;

    Class<?> cl = enthusiastic.getClass();
    System.out.println("class is " + cl.getName());
    Method[] methods = cl.getMethods();
    for (Method m : methods) {
      System.out.println("> " + m);
    }

    Doubtful d = () -> {
      System.out.println("Doubtful");
    };
    d.show();

    showAll(getByPredicate(roster, (Student s) -> {
      return s.getCourses().size() == 2;
    }));
    // if arguments type is unambiguous, we can leave ALL of them out
//    Predicate<Student> e2 = (student) -> {
    // SINGLE untyped argument does not need parens
    Predicate<Student> e2 = student -> {
      return student.getCourses().size() > threshold;
    } ;

//    Comparator<Student> cs = (Student s1, Student s2) -> {
    Comparator<Student> cs = (@Deprecated var s1, var s2) -> {
//    Comparator<Student> cs = (s1, s2) -> {
      return Integer.compare(s2.getCourses().size(), s1.getCourses().size());
    };
    // IF (and only if) method body consists of ONLY "return <expression>
    // Then, can replace ENTIRE method body (curlys inward)
    // with <expression>
    Comparator<Student> cs2 = (s1, s2) ->
        Integer.compare(s2.getCourses().size(), s1.getCourses().size()) ;

    roster = new ArrayList<>(roster);
    System.out.println(roster);
    roster.sort((s1, s2) -> Integer.compare(s2.getCourses().size(), s1.getCourses().size()));
    System.out.println(roster);
  }
}
