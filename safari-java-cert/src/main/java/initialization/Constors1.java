package initialization;
class X {
  int x;
  /*private */X() {} // default disappears on adding ANY explicit constructor
  private X(int x) {
    this.x = x;
  }
  void doSomething() {
    XInner target = new XInner();
    target.doOtherStuff(); // can access enclosed private too (not nesting)
  }
  class XInner {
    private void doOtherStuff() {}
    void doStuff() {
      new X(); // can access enclosing private
    }
  }
}
class Y extends X {
  Y(int x) {
    // super();
  }
}
public class Constors1 {
  public static void main(String[] args) {
    X x = new Y(3); // line 1
    System.out.println(x.x);
  }
}
