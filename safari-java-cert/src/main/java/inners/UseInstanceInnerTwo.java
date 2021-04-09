package inners;

import java.io.Serializable;

public class UseInstanceInnerTwo {
  public static Serializable get() {
    class MyLocalClass implements Serializable {}
    MyLocalClass mlc = new MyLocalClass();
    return mlc;
  }
  public static void main(String[] args) {
    InstanceInnerTwo outer = new InstanceInnerTwo();
    InstanceInnerTwo.TheInner inner = outer.new TheInner();
  }
}
