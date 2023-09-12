Determine if the number is valid
Given an input string, determine if it makes a valid number or not. For simplicity, assume that white spaces are not present in the input.

enum STATE { START, INTEGER, DECIMAL, UNKNOWN, AFTER_DECIMAL};

STATE get_next_state(STATE current_state, char ch) {
  switch(current_state) {
    case START:
    case INTEGER: {
      if (ch == '.') {
        return DECIMAL;
      } else if (ch >= '0' && ch <= '9') {
        return INTEGER;
      } else {
        return UNKNOWN;
      }
      break;
    }
    
    case DECIMAL:
      if (ch >= '0' && ch <= '9') {
        return AFTER_DECIMAL;
      } else {
        return UNKNOWN;
      }
      break;

     case AFTER_DECIMAL:
      if (ch >= '0' && ch <= '9') {
        return AFTER_DECIMAL;
      } else {
        return UNKNOWN;
      }
      break;
      
    case UNKNOWN:
      return UNKNOWN;
  }
  return UNKNOWN;
}

bool is_number_valid(const string s) {
  int i = 0;
  if (s[i] == '+' || s[i] == '-') {
    i++;
  }
  STATE current_state = START;
  while (s[i] != '\0') {
    current_state = get_next_state(current_state, s[i]);
    if (current_state == UNKNOWN) {
      return false;
    }
    i++;
  }
  
  if (current_state == DECIMAL)
    return false;
  
  return true;
}

void test(const string s, bool expected) {
  bool is_valid = is_number_valid(s);
  if (is_valid) {
    cout << s << " is valid." << endl;
  } else {
     cout << s << " is not valid." << endl;
  }
}

int main(int argc, char* argv[]) {
  test("4.325", true);
  test("4.325a", false);
  test("x4.325", false);
  test("4.32.5", false);
  test("4325", true);
  test("1.", false);
  test("1.1.", false);
  test("1.1.1", false);
  test("1.1.1.", false);
  test("+1.1.", false);
  test("+1.1", true);
  test("-1.1.", false);
  test("-1.1", true);
  test("-1.1.1", true);
  test("", true);
}