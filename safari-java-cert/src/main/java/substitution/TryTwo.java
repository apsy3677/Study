package substitution;
class Base2 {
  Object doBaseStuff() {
    return "doBaseStuff";
  }
  long getValue() { return 1; }
}
class Sub2 extends Base2 {
  CharSequence doBaseStuff() {
    return "doSubStuff";
  }
  /*int*/long getValue() { return 1; }
}
public class TryTwo {
  public static void main(String[] args) {
    Base2 b2 = null;
    Object cs = b2.doBaseStuff();

    long l = b2.getValue();
  }
}
