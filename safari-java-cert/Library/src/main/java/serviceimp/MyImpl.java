package serviceimp;

import myservice.MySPI;

public class MyImpl implements MySPI {
  @Override
  public String getMessage() {
    return "message from service";
  }
}
