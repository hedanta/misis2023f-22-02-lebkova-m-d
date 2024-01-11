#include <iostream>

int main() {
  int tests;
  std::cin >> tests;

  for (int t = 0; t < tests; t += 1) {
    int n, a, b;
    std::cin >> n >> a >> b;

    for (int i = 0; i < n; i += 1) {
      std::cout << char('a' + i % b);
    }

    std::cout << std::endl;
  }

  return 0;
}