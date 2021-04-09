package substitution;
class Base {
  private void doBaseStuff() {
    System.out.println("doBaseStuff");
  }
}
class Sub extends Base {
//  @Override
  void doBaseStuff() {
    System.out.println("doSubStuff");
  }
  void doOtherStuff() {
    System.out.println("doOtherStuff");
  }
}
public class TryOne {
}
