package substitution;

interface IBase2 {
  private void helperStuff() { // Java 9 onwards...
    System.out.println("Helper stuff");
  }
  static void doStuff() { // automatically public, can be expressly private
    System.out.println("static void doStuff in IBase2");
  }
  static void x() {
    System.out.println("IBase2.x()");
  }
}
interface IBase1 {
  default void x() {
    System.out.println("IBase1.x()");
  }
}
class CBase implements IBase1, IBase2 {
//
//  @Override
//  public void x() {
//    IBase1.super.x();
//    IBase2.super.x();
//  }
}

public class DefaultMethods {
  public static void main(String[] args) {
    CBase cb = new CBase();
    cb.x();
    IBase2.x();
    IBase2 ib2 = cb;
    IBase2.doStuff();
  }
}
