package exceptions;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Returning {
  public static void main(String[] args) {
//    try (BufferedReader br = Files.newBufferedReader(Paths.get("data.txt"))) {
    try (BufferedReader br = Files.newBufferedReader(Path.of("data.txt"))) {
      System.out.println("in body of try");
      if (Math.random() > 0) return;
      System.out.println("Still in body");
    } catch (FileNotFoundException fnfe) {
      System.out.println("File not found...");
    } catch (IOException ioe) {
      System.out.println("IOException...");
    } finally {
      System.out.println("In finally");
      if (Math.random() > 0) return;
      System.out.println("Still in finally");
    }
  }
}
