#include "selection_sort.h"
#include "sequence.h"
#include <iostream>

int main() {
  StaticSeq<int> secuencia(10);
  std::cout << secuencia << std::endl;
  SelectionSort<int> ordenacion(secuencia, unsigned(10));
  std::cout << secuencia << std::endl;
}