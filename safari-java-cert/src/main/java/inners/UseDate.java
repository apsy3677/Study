package inners;

public class UseDate {
  public static void main(String[] args) {
    Date d = Date.builder()
        .day(23)
        .month(12)
        .year(2020)
        .build();
    Date d2 = Date.builder()
        .day(23)
        .month(13)
        .year(2020)
        .build();
  }
}
