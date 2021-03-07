import java.util.HashMap;

public class Main {
    public static void main(String[] args) {

    }

    public String getStateWithMaximumScore(List<Course> courses ,
                                           List<Student> students,
                                           List<StudentDemographic> studentDemographics, List<StudentCourse> studentCourses){

        HashMap<long,  long> uniqueCOurseReg = new HashMap<long, long>();
        HashMap<long,  String> courseName = new HashMap<>();
        for(Course c: courses){
            courseName.put(c.id, c.name);
        }
        for(StudentCourse s:studentCourses){
            int count = uniqueCOurseReg.containsKey(s.courseId) ? uniqueCOurseReg.get(s.courseId) : 0 ;
            uniqueCOurseReg.put(s.courseId, count +1 );
        }

    }
}
