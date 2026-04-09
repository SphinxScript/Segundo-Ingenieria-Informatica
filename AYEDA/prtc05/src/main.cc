#include "selection_sort.h"
#include "sequence.h"
#include "bubble_sort.h"

#include <iostream>

int main() {
  StaticSeq<int> secuencia(10);
  std::cout << secuencia << std::endl;
  BubbleSort<int> ordenacion(secuencia, unsigned(10));
  std::cout << secuencia << std::endl;
}