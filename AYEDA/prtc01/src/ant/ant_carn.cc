#include "ant_carn.h"

void AntCarn::ManageLife(const Colores& colores) {
  --life_time_;
}


bool AntCarn::Move(Tape& tape) {
  Colores color_actual = tape.GetColor(x_, y_);
  int idx = static_cast<int>(color_actual);
  char regla = GetReglas()[idx];

  Direccion direccion_anterior = direction_;

  // Girar
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
  else {  // izquierda
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

  ManageLife(color_actual);
  tape.FlipColor(x_, y_);

  // Avance diagonal = componente de la dirección anterior
  //                 + componente de la nueva dirección
  switch (direccion_anterior) {
    case Direccion::up:
      --x_;
      break;
    case Direccion::down:
      ++x_;
      break;
    case Direccion::left:
      --y_;
      break;
    case Direccion::right:
      ++y_;
      break;
  }

  switch (direction_) {
    case Direccion::up:
      --x_;
      break;
    case Direccion::down:
      ++x_;
      break;
    case Direccion::left:
      --y_;
      break;
    case Direccion::right:
      ++y_;
      break;
  }

  tape.ResolvePosition(x_, y_, direction_);
  return true;
}