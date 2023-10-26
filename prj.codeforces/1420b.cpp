#include <iostream> 
#include <vector>

int main() {
  int tests;
  std::cin >> tests;

  for (int t = 0; t < tests; t += 1) {
    long long arr_size;
    std::cin >> arr_size;
    std::vector<int> arr(arr_size, 0);
    long long ans = 0;

    for (int i = 0; i < arr_size; i++) {
      std::cin >> arr[i];
    }

    for (int k = 32; k >= 1; k -= 1) {
      long long cnt = 0;

      for (int i = 0; i < arr_size; i += 1) {
        if (arr[i] >= (1 << k) && arr[i] < (1 << (k + 1))) {
          cnt += 1;
        }
      }

      ans += cnt * (cnt - 1) / 2;
    }
    std::cout << ans << std::endl;
  }
}