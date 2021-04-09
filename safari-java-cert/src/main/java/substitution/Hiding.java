package substitution;
class P {
  String x = "Parent";
  String getX() {
    return "Parent method";
  }
}

class S extends P {
  String x = "Child";
  String getX() {
    return "Child method";
  }
  public String getParentX() {
    return super.x;
  }

}
public class Hiding {
  public static void main(String[] args) {
    P p = new S();
    System.out.println(p.x);

    System.out.println(p.getX());
    System.out.println(((S)p).x );
    System.out.println(((S) p).getParentX());
  }
}
