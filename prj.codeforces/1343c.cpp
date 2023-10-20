#include <iostream>
#include <vector> 

int main() {
  int tests = 0;
  std::cin >> tests;

  for (int t = tests; t > 0; t -= 1) {
  	int length = 0;
	  std::cin >> length;
	  std::vector<int> arr(length);
	
	  for (int i = 0; i < length; i += 1) {
	    std::cin >> arr[i];
	  }
	
	  long long sum = 0;
	
	  for (int i = 0; i < length; i += 1) {
	    int cur = arr[i];
	    int j = i;
	    while (j < length) {
	      if ((arr[i] > 0 && arr[j] > 0) || 
            (arr[i] < 0 && arr[j] < 0)) {
	        cur = std::max(cur, arr[j]);
	        j += 1;
        }
        else {
          break;
        }
	    }
	    
		  sum += cur;
		  i = j - 1;
	  }
	  
	  std::cout << sum << std::endl;
  }
  
  return 0;
}
