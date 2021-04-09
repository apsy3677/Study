package inners;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.Serializable;

//class MyActionListener implements ActionListener {
//  @Override
//  public void actionPerformed(ActionEvent e) {
//    System.out.println("Action performed");
//  }
//}

public class EventStuff {
//  public static ActionListener getActionListener() {
//    return new MyActionListener();
//  }

  //  private Serializable serializable = new Serializable() {};
  class MyActionListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
      System.out.println("Action performed");
    }
  }

  public static ActionListener getActionListener() {
    // anonymous inner class
    return new /*class MyActionListener implements*/ ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        System.out.println("Action performed");
      }
    };
  }

  public static void main(String[] args) {
    ActionListener al = getActionListener();
    al.actionPerformed(null);
    System.out.println("name of al's class is " + al.getClass().getName());
  }
}
