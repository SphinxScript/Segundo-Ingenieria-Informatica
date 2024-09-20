#include <iostream>
#include <set>

int main() {
  std::set<int> prueba{1, 3 , 4, 2};
  for (const int& numero : prueba) {
    std::cout << numero << " ";
  }
  std::cout << std::endl;
  return 0;
}