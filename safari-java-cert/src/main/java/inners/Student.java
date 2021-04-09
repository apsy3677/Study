package inners;

import java.util.List;

public class Student {
  private String name;
  private int grade;
  private List<String> courses;

  public Student(String name, int grade, String ... courses) {
    this.name = name;
    this.grade = grade;
    this.courses = List.of(courses);
  }

  public String getName() {
    return name;
  }

  public int getGrade() {
    return grade;
  }

  public List<String> getCourses() {
    return courses;
  }

  @Override
  public String toString() {
    return "Student{" +
        "name='" + name + '\'' +
        ", grade=" + grade +
        ", courses=" + courses +
        '}';
  }
}
