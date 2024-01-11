#include <iostream>
using namespace std;

int main() {
  int tests;
  std::cin >> tests;

  for (int t = 0; t < tests; t += 1) {
    int n, k;
    std::cin >> n >> k;
    k -= 1;
    std::cout << ((k + (n % 2) * k / (n / 2)) % n + 1) << std::endl;
  }

  return 0;
}