#include "ant_reglas.h"


/**
 * @brief Implementación del método Move de la clase AntReglas. Se encarga de mover la hormiga según las reglas definidas, cambiar el color de la celda y actualizar la rejilla.
 * @param tape Referencia a la rejilla (tape) donde se encuentra la hormiga.
 * @return true si el movimiento es válido (dentro de los límites de la rejilla), false en caso contrario.
 */
bool AntReglas::Move(Tape& tape) {
  Colores color_actual = tape.GetColor(x_, y_);
  int idx = static_cast<int>(color_actual);
  char regla = reglas_[idx];
  if (regla == 'D') {
    switch (direction_) {
      case Direccion::up:
        direction_ = Direccion::right;
        break;
      case Direccion::right:
        direction_ = Direccion::down;
        break;
      case Direccion::down:
        direction_ = Direccion::left;
        break;
      case Direccion::left:
        direction_ = Direccion::up;
        break;
    }
  }
  else {
    switch (direction_) {
      case Direccion::up:
        direction_ = Direccion::left;
        break;
      case Direccion::right:
        direction_ = Direccion::up;
        break;
      case Direccion::down:
        direction_ = Direccion::right;
        break;
      case Direccion::left:
        direction_ = Direccion::down;
        break;
    }
  }
  // antes de cambiar el color, actualizamos su vida
  ManageLife(color_actual);
  //std::cout << "debug: vida de la hormiga: " << life_time_ << "\n";
  tape.FlipColor(x_, y_);
  // ahora movemos la hormiga a la siguiente celda según su orientación
  switch (direction_) {
    case Direccion::up:
      --x_;
      break;
    case Direccion::right:
      ++y_;
      break;
    case Direccion::down:
      ++x_;
      break;
    case Direccion::left:
      --y_;
      break;
  }
  tape.ResolvePosition(x_, y_, direction_);  // normalizamos las coordenadas en caso de ser necesario (solo válido para TapePeriodic)
  // comprobamos que la hormiga no se salga de la rejilla
  //return (x_ >= 0 && x_ < tape.GetSize().first && y_ >= 0 && y_ < tape.GetSize().second);
  // ya no comprobamos los limites, devuelve true siempre. la cinta se encarga
  return true;
}