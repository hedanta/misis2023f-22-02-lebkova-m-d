#include <cctype>
#include <iostream> 
#include <string>

int main() {
  int str_size = 0;
  std::cin >> str_size;

  std::string s;
  std::cin >> s;
  s = "_" + s + "_";

  int max_length = 0;
  int words_count = 0;
  bool brackets = 0;
  int cnt = 0;

  for (int i = 0; i < str_size + 2; i++) {
    if (s[i] == '(' || s[i] == ')' || s[i] == '_') {
      if (!brackets) {
        max_length = std::max(max_length, cnt);
      }

      else if (cnt > 0) {
        words_count += 1;
      }

      cnt = 0;
    }

    if (std::isalpha(s[i])) {
      cnt += 1;
    }

    if (s[i] == '(' || s[i] == ')') {
      brackets = !brackets;
    }
  }

  std::cout << max_length << " " << words_count << std::endl;
  return 0;
}