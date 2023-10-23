#include <iostream>
#include <vector>

const int N = 1e5 + 1;
std::vector<int> cats(N);
std::vector<int> tree[N];
int ans = 0;

void dfs(int x, int y, int cnt, int m) {
  if (cats[y]) {
    cnt += 1;
  } else {
    cnt = 0;
  }

  if (cnt > m) {
    return;
  }

  if (tree[y].size() == 1 && y != 1) {
    ans += 1;
  }

  for (int to : tree[y]) {
    if (to != x) {
      dfs(y, to, cnt, m);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;

  for(int i = 1; i <= n; i += 1) {
    int tmp = false;
    std::cin >> tmp;
    cats[i] = tmp;
  }

  for (int i = 1; i < n; i += 1) {
    int x = 0;
    int y = 0;
    std::cin >> x >> y;

    tree[x].push_back(y);
    tree[y].push_back(x);
  }

  int x = 0;
  int y = 1;
  int cnt = 0;

  dfs(x, y, cnt, m);

  std::cout << ans;

  return 0;
}
