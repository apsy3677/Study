package encapsulation;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Student {
  private String name;
  private int grade;
  private List<String> courses;

  public Student(String name, int grade, List<String> courses) {
    this.name = name;
    this.grade = grade;
    this.courses = new ArrayList<>(courses);
  }

  public String getName() {
    return name;
  }

  public int getGrade() {
    return grade;
  }

  public List<String> getCourses() {
//    return Collections.unmodifiableList(courses);
    return List.copyOf(courses);
  }

  @Override
  public String toString() {
    return "Student{" +
        "name='" + name + '\'' +
        ", grade=" + grade +
        ", courses=" + courses +
        '}';
  }

  public static void main(String[] args) {
    Student s = new Student("Fred", 97, List.of("Math", "Physics", "Chemistry"));

    List<String> courses = s.getCourses();
//    courses.add("Journalism");

    System.out.println(s);

    List<String> names = new ArrayList<>(Arrays.asList("Fred", "Jim"));
    List<String> names1 = Collections.unmodifiableList(names);
    List<String> names2 = List.copyOf(names);
    List<String> names3 = List.copyOf(names2);
    List<String> names4 = List.copyOf(names1);
    System.out.println("names == names2? " + (names == names2));
    System.out.println("names2 == names3? " + (names2 == names3));
    System.out.println("names1 == names4? " + (names1 == names4));
  }
}
