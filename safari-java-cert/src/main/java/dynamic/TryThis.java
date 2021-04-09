package dynamic;
class Y {
  static String sayHi() { return "Y-Hello"; }
  String sayHi2() { return "Y-Hello2"; }
}

class Z extends Y {
  static String sayHi() { return "Z-Hello"; }
  @Override // This annotation adds an additional error to the compiler
  String sayHi2() { return "Z-Hello2"; }
}

public class TryThis {
  public void doIt() {
    Y y = new Z();
    System.out.println(y.sayHi() + ", " + y.sayHi2());
  }
  public static void main(String[] args) {
    Y y = new Z();
//    System.out.println(y.sayHi() + ", " + y.sayHi2());
    System.out.println(Y.sayHi() + ", " + y.sayHi2());
    new TryThis().doIt();
  }
}
