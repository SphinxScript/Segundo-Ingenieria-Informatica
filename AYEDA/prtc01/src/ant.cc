#include "ant.h"
#include "tape.h"

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

bool Ant::Move(bool color, Tape& cinta) {
  // Si está sobre una celda blanca, cambia el color a negra, gira noventa grados a la izquierda
  // y avanza una celda.
  // Si está sobre una celda negra, cambia el color a blanca, gira noventa grados a la derecha
  // y avanza una celda.
  // primero giramos
  if (!color) {
    switch(direction_) {
      case Direccion::up:
        direction_ = Direccion::left;
        break;
      case Direccion::left:
        direction_ = Direccion::down;
        break;
      case Direccion::down:
        direction_ = Direccion::right;
        break;
      case Direccion::right:
        direction_ = Direccion::up;
        break;
    }
  }
  else {
    switch(direction_) {
      case Direccion::up:
        direction_ = Direccion::right;
        break;
      case Direccion::left:
        direction_ = Direccion::up;
        break;
      case Direccion::down:
        direction_ = Direccion::left;
        break;
      case Direccion::right:
        direction_ = Direccion::down;
        break;
    }
  }

  // cambiamos el color ahora
  cinta.FlipColor(x_, y_);

  // finalmente avanzamos
  switch(direction_) {
    case Direccion::up:
      // std::cout << "debug: moviendo hacia arriba" << std::endl;
      --x_;
      break;
    case Direccion::down:
      // std::cout << "debug: moviendo hacia abajo" << std::endl;
      ++x_;
      break;
    case Direccion::left:
      // std::cout << "debug: moviendo hacia la izquierda" << std::endl;
      --y_;
      break;
    case Direccion::right:
      // std::cout << "debug: moviendo hacia la derecha" << std::endl;
      ++y_;
      break;
  }
  // comprobamos que la nueva posicion es valida, es decir, que no se sale de la rejilla
  bool valido = true;
  std::pair<int,int> size = cinta.GetSize();
  if (x_ < 0 || x_ >= size.first || y_ < 0 || y_ >= size.second) {
    valido = false;
  }
  return valido;
}