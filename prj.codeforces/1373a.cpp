#include <iostream>

int main() {
  int tests;
  std::cin >> tests;

  for (int t = 0; t < tests; t += 1) {
    long long a, b, c;
    std::cin >> a >> b >> c;

    std::cout << (a < c ? 1 : -1) << " ";
    std::cout << (c < (a * b) ? b : -1) << '\n';
  }

  return 0;
}