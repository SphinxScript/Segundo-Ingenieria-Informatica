
#include <iostream>

#include "nif.h"
#include "dispersionfunction.h"
#include "explorationfunction.h"
#include "hashtable.h"
#include "sequence.h"

int main(int argc, char* argv[]) {
  Nif nif1;
  Nif nif2;
  Nif nif3(12345678);

  std::cout << "nif1: " << long(nif1) << std::endl;
  std::cout << "nif2: " << long(nif2) << std::endl;
  std::cout << "nif3: " << long(nif3) << std::endl;

  if (nif1 < nif2) {
    std::cout << "nif1 es menor que nif2" << std::endl;
  } else if (nif1 > nif2) {
    std::cout << "nif1 es mayor que nif2" << std::endl;
  } else {
    std::cout << "nif1 es igual a nif2" << std::endl;
  }

  if (long(nif3) == 12345678) {
    std::cout << "nif3 es igual a 12345678" << std::endl;
  }

  return 0;
}