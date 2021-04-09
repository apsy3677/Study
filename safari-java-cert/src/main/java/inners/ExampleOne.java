package inners;

public class ExampleOne {
  private int x = 100;
  static class TryThis {
    private int y = 200;
    public void showOuter(ExampleOne ex) {
      System.out.println(ex.x);
    }
  }

  public void showInner(TryThis tt) {
    System.out.println(tt.y);
  }

  public static void main(String[] args) {
//    ExampleOne e = new ExampleOne();
    inners.ExampleOne.TryThis t = new ExampleOne.TryThis();
  }
}
