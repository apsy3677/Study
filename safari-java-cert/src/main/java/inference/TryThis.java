package inference;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.function.Consumer;

public class TryThis {
  static int x = 10;
  private int y = 10;

  // ... compiler builds caller side array if needed from variable arg list
  public static void doStuff(String ... names) {}

  // In Java, method args DO NOT HAVE initialization,
  // therfore, CANNOT use vra.
//  public static void showIt(var s) {
//    System.out.println(s);
//  }

  public static void main(String[] args) {

//    var x;
//    x = 10;
//    static int x = 10;
//    private int x = 10;

//    var x = 10;
//    throw new RuntimeException();
//    System.out.println("Hello");

    // arrays have additional rules with var

//    String [] names = {"Fred", "Jim", "Sheila"};
//    doStuff(names);
//    doStuff({"Fred", "Jim", "Sheila"}); // Compiler not sure what base type for the array...
    doStuff(new String [] {"Fred", "Jim", "Sheila"}); // Compiler happy :)
//    doStuff("Fred", "Alice", "Bob");

//    var n2 = {"Fred", "Jim"}; // NO, same problem as above
    var n2 = new String[] {"Fred", "Jim"};
    var n3 = new String[3];
//    String [] n2 = {"Fred", "Jim"};

//    String [] n4 = new String[3];
//    String n4[] = new String[3];
//    var [] n4 = new String[3]; // var is ENTIRE type, or don't use it :)

    Consumer<String> cs = (var s) -> { System.out.println(s); };

    var many = Arrays.asList("Fred");
    var arr = new ArrayList<String>();
  }
}
