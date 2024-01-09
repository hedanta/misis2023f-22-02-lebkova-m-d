#include <algorithm>
#include <iostream>

int main() {
  int tests;
  std::cin >> tests;

  for (int t = 0; t < tests; t += 1) {
    std::string str;
    std::cin >> str;
    int zero = 0;
    int one = 0;

    for (int i = 0; i < str.size(); i += 1) {
      if (str[i] == '0') {
        zero += 1;
      }

      else {
        one += 1;
      }
    }

    if (std::min(zero, one) % 2 != 0) {
      std::cout << "DA\n";
    }
    else {
      std::cout << "NET\n";
    }
  }

  return 0;
}