package inners;

public final class Date {
  private int day;
  private int month;
  private int year;
  private Date() {}

  // "like any other top level class" except, scoped name, privileged access
  // called a "nested" class
  public static final class Builder {
    Date self = new Date();
    private Builder(){}
    public Builder day(int d) {
      self.day = d;
      return this;
    }
    public Builder month(int m) {
      self.month = m;
      return this;
    }
    public Builder year(int y) {
      self.year = y;
      return this;
    }
    public Date build() {
      validate(self.day, self.month, self.year);
      return self;
    }
  }
  public static Builder builder() {
    return new Builder();
  }

  public static void validate(int day, int month, int year) {
    if (day < 1 || day > 31 || month < 1 || month > 12) throw new IllegalArgumentException();
  }
}
