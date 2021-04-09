package exceptions;

public class BadBadBad {
  public static int dontDoThis() throws Exception {
    try {
      if (Math.random() > 0.5) {
        throw new Exception("Won't see this");
      }
      System.out.println("Still running try block");
      return 100;
    } finally {
      if (Math.random() > 0.5) {
        System.out.println("finally executing return");
        return 200;
      }
    }
  }

  public static void main(String[] args) throws Exception {
    System.out.println("return is " + dontDoThis());
  }
}
