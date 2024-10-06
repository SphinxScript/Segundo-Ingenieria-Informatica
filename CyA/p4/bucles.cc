#include "bucles.h"

std::ostream& operator<<(std::ostream& os, const Bucles& otro) {
  os << "[Line " << otro.GetNum() << "]" << otro.GetBucle() << std::endl;
  return os;
}