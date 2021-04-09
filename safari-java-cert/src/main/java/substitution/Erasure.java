package substitution;


import java.time.LocalDate;
import java.util.*;

public class Erasure {
  public static void breakAList(List l) {
    l.add(LocalDate.now());
  }
  public static void showMany(List<String> ls) {
//    ls.add(LocalDate.now());
    System.out.println("showing a list");
  }
//  public static void showMany(List<LocalDate> ld) {
//    System.out.println("showing a list of dates");
//  }
  public static void showMany(Collection<String> cs) {
    System.out.println("showing a collection");
  }

  public static void main(String[] args) {
    List<String> names = Collections.checkedList(new ArrayList<>(Arrays.asList()), String.class);
    showMany(names);
    Set<String> nameSet = new HashSet<>();
    showMany(nameSet);
//    showMany(names);

    breakAList(names);

//    String s = names.get(0);

    if (names instanceof List/*<String>*/) {
      System.out.println("It's a list");
    }
  }
}
