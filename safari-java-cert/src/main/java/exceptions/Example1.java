package exceptions;

import java.io.FileInputStream;

interface ExFunction<T extends Throwable> {
  void doStuff() throws T;
}
public class Example1 {
  public static <T extends Throwable> void testIt(ExFunction<T> op) {
    try {
      op.doStuff();
//    } catch (T t) { // not allowed
    } catch (Throwable t) {

    }
  }

  public static void main(String[] args) {
    try (FileInputStream fis = new FileInputStream("data.txt")) {
      if (Math.random() > 0.5) {
        throw new Exception();
      }
    } catch (Exception e)     {
      System.out.println("It broke...");
    }
  }
}
