#include <iostream>
#include <set>
#include <vector>

int main() {
  int n = 0;
  int list_size = 0;
  std::cin >> n >> list_size;
  
  std::vector<int> array(n, 0);
  for (int i = 0; i < n; i += 1) {
    std::cin >> array[i];
  }

  std::set<int> count;
  std::vector<int> ans(n, 0);

  for (int i = n - 1; i >= 0; i -= 1) {
    count.insert(array[i]);
    ans[i] = count.size();
  }

  for (int i = 0; i < list_size; i += 1) {
    int list_number = 0;
    std::cin >> list_number;
    std::cout << ans[list_number - 1] << std::endl;
  }
}
