#include <iostream>

int main() {
  int tests;
  std::cin >> tests;

  for (int t = 0; t < tests; t += 1) {
    int n;
    cin >> n;
    char c;
    std::cin >> c;
    std::string s;
    std::cin >> s;
    s += s;
    int j = 0, ans = 0, seconds = 0;

    for (int i = 0; i < n; i += 1) {
      while (s[j] != 'g' || i > j) {
        j += 1;
      }

      if (s[i] == c) {
        seconds = j - i;
      }

      if (seconds > ans) {
        ans = seconds;
      }
    }

    std::cout << ans << std::endl;

  }

  return 0;
}