package client;

import myservice.MyClass;
import myservice.MySPI;

import java.lang.reflect.Field;
import java.util.ServiceLoader;

public class MyClient {
  public static void main(String[] args) throws Throwable {
    System.out.println(MyClass.message);
    Class<?> cl = MyClass.class;
    Field secret = cl.getDeclaredField("secretMessage");
    secret.setAccessible(true);
    String msg = (String)(secret.get(null));
    System.out.println(msg);

    ServiceLoader<MySPI> loader = ServiceLoader.load(MySPI.class);
    for (MySPI service : loader) {
      System.out.println("Found a service: " + service.getClass().getName());
      System.out.println(" -- message is " + service.getMessage());
    }
  }
}
