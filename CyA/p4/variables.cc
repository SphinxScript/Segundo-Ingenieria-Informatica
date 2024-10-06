#include "variables.h"


std::ostream& operator<<(std::ostream& os, const Variables& otro) {
  os << "[Line " << otro.GetIndice() << "] " << otro.GetVariable() << std::endl;
  return os;
}