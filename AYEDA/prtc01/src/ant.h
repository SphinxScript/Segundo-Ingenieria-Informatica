#pragma once

#include <iostream>
#include "tape.h"

enum class Direccion {
  left,
  right,
  up,
  down
};

class Tape;  // declaracion adelantada

class Ant {
 public:
  Ant() = default;
  void Move(bool, Tape&);
  void SetPlace(int, int, int);
  std::pair<int,int> GetPosition() const { return std::pair<int,int>(x_, y_); }
  friend std::ostream& operator<<(std::ostream& os, const Ant& ant);
 private:
  // posicion de la hormiga
  int x_;   // fila
  int y_;   // columna
  // dirección de la hormiga, usamos la enumeración para representar las direcciones
  Direccion direction_;
};