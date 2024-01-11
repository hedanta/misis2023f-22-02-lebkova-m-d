#include <algorithm>
#include <iostream>

const int N = 2e5 + 7;

std::vector<int> v[N];

int main() {
  int tests;
  std::cin >> tests;

  for (int t = 0; t < tests; t += 1) {
    int n, k;
    std::cin >> n >> k;

    for (int i = 0; i <= n; i += 1) {
      v[i].clear();
    }

    long long a[n];
    long long w[k];

    for (int i = 0; i < n; i += 1) {
      std::cin >> a[i];
    }

    for (int i = 0; i < k; i += 1) {
      std::cin >> w[i];
    }

    std::sort(w, w + k);
    std::sort(a, a + n);

    for (int i = 0; i < k / 2; i += 1) {
      std::swap(w[i], w[k - i - 1]);
    }

    int pos = 0;
    for (int i = 0; i < n - k; i += 1) {
      while (w[pos] == v[pos].size() + 1) {
        pos += 1;
      }

      v[pos].push_back(a[i]);
    }

    long long ans = 0;
    int q_friend = 1;

    for (int i = 0; i < k; i++) {
      ans += a[n - i - 1];

      if (v[i].size()) {
        ans += v[i][0];
      }

      else {
        ans += a[n - q_friend];
        q_friend += 1;
      }
    }

    std::cout << ans << std::endl;
  }

  return 0;
}