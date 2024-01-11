#include <iostream>
#include <string>

long long sum(std::string s) {
  long long res = 0;

  for (int i = 0; i < s.size(); i += 1) {
    res += s[i] - '0';
  }

  return res;
}

int main() {
  std::string str;
  std::cin >> str;
  
  int cnt = 0;
  
  while(str.size() > 1) {
    long long x = sum(str);
    str = std::to_string(x);
    cnt++;
  }
  
  std::cout << cnt;

  return 0;
}