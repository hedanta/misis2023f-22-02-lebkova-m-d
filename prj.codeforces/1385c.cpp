#include <iostream> 
#include <vector>

int main() {
  int tests;
  std::cin >> tests;

  for (int t = 0; t < tests; t += 1) {
    int arr_size = 0;
    std::cin >> arr_size;
    std::vector<int> arr(arr_size);

    for (int i = 0; i < arr_size; i += 1) {
      std::cin >> arr[i];
    }

    int index = arr_size - 1;

    for (int i = arr_size - 1; i > 0; i -= 1) {
      if (arr[i - 1] >= arr[i]) {
        index -= 1;
      }

      else {
        break;
      }
    }

    int ans = index;
    for (int i = index; i > 0; i -= 1) {
      if (arr[i - 1] <= arr[i]) {
        ans -= 1;
      }

      else {
        break;
      }
    }

    std::cout << ans << std::endl;
  }

  return 0;
}