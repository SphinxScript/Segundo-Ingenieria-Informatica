#include "ant.h"

// Ant::Ant();

void Ant::SetPlace(int x, int y, int orientacion) {
  x_ = x;
  y_ = y;
  direction_ = static_cast<Direccion>(orientacion);
}

std::ostream& operator<<(std::ostream& os, const Ant& ant) {
  switch(ant.direction_) {
    case Direccion::left:   os << "<"; break;
    case Direccion::right:  os << ">"; break;
    case Direccion::up:     os << "^"; break;
    case Direccion::down:   os << "v"; break;
  }
  return os;
}