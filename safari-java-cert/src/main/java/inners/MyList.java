package inners;

import java.util.Iterator;

public class MyList<E> implements Iterable<E> {
  private E[] data = (E[])(new Object[10]);
  private int count = 0;
  // default constructor...
  public void add(E e) {
    data[count++] = e;
  }

  @Override
  public String toString() {
    StringBuilder rv = new StringBuilder("MyList [ ");
    for (int i = 0; i < count; i++) {
      rv.append(data[i]).append(", ");
    }
    rv.setLength(rv.length() - 2);
    rv.append(" ]");
    return rv.toString();
  }

  public static void main(String[] args) {
    MyList<String> mls = new MyList<>();
    mls.add("Fred");
    mls.add("Jim");
    mls.add("Sheila");
    MyList<Integer> mli = new MyList<>();
    mli.add(1);
    mli.add(2);
    mli.add(3);
    mli.add(4);
    System.out.println(mls);

    for (int i : mli) {
      System.out.println(">> " + i);
    }
    for (String s : mls) {
      System.out.println("> " + s);
    }
    Iterator<String> is = mls.iterator();
    Iterator<String> is2 = mls.iterator();
    System.out.println("> " + is.next());
    System.out.println(">>           " + is2.next());
    System.out.println(">>           " + is2.next());
    System.out.println("> " + is.next());
    System.out.println("> " + is.next());
    System.out.println(">>           " + is2.next());
  }

  private class MyIterator implements Iterator<E> {
    private int progress = 0;
    @Override
    public boolean hasNext() {
      return progress < count;
    }

    @Override
    public E next() {
      return data[progress++];
    }
  }

  @Override
  public Iterator<E> iterator() {
    return new MyIterator();
  }
}
