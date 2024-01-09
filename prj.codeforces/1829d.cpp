#include <iostream>

bool check(int n, int m) {
  if (n == m) {
    return 1;
  }

  else if (n % 3 != 0) {
    return 0;
  }

  return (check(n / 3, m) || check(2 * n / 3, m));
}

int main() {
  int tests; 
  std::cin >> tests;
  
  for (int i = 1; i <= tests; i += 1) {
    int n, m;
    std::cin >> n >> m;

    std::cout << (check(n, m) ? "YES" : "NO") << '\n';
  }
  
  return 0;
}