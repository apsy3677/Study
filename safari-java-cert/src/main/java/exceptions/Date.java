package exceptions;

public class Date {
  private int day;
  private int month;
  private int year;

  public Date(int day, int month, int year) {
    if (day < 1 || day > 31 || month < 1 || month > 12) {
      throw new IllegalArgumentException();
    }
    this.day = day;
    this.month = month;
    this.year = year;
  }
}
