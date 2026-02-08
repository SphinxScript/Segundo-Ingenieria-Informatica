#include "ant.h"
#include "tape.h"

/**
 * @brief Establece la posición y orientación de la hormiga.
 * @param x Fila de la posición inicial de la hormiga.
 * @param y Columna de la posición inicial de la hormiga.
 * @param orientacion Orientación inicial de la hormiga, representada como un entero (0: up, 1: right, 2: down, 3: left).
 */
void Ant::SetPlace(int x, int y, int orientacion) {
  x_ = x;
  y_ = y;
  direction_ = static_cast<Direccion>(orientacion);
}

/**
 * @brief Sobrecarga del operador de salida para imprimir la representación de la hormiga.
 * @param os Flujo de salida.
 * @param ant Objeto Ant cuya representación se desea imprimir.
 * @return Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Ant& ant) {
  switch(ant.direction_) {
    case Direccion::left:   os << "<"; break;
    case Direccion::right:  os << ">"; break;
    case Direccion::up:     os << "^"; break;
    case Direccion::down:   os << "v"; break;
  }
  return os;
}

/**
 * @brief Mueve la hormiga según las reglas del juego de la hormiga de Langton.
 * @param color Color de la celda actual (false: blanca, true: negra).
 * @param cinta Referencia a la cinta (rejilla) sobre la que se mueve la hormiga.
 * @return true si el movimiento es válido (dentro de los límites de la rejilla), false si la hormiga se sale de la rejilla.
 */
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