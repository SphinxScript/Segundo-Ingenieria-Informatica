#pragma once

#include <iostream>

enum class Direccion {
  left,
  right,
  up,
  down
};

class Ant {
 public:
  // Ant();
  Ant() {};
  void Move();
  void SetPlace(int, int, int);
  std::pair<int,int> GetPosition() const { return std::pair<int,int>(x_, y_); }
  friend std::ostream& operator<<(std::ostream& os, const Ant& ant);
 private:
  // posicion de la hormiga
  int x_;
  int y_;
  // dirección de la hormiga, usamos la enumeración para representar las direcciones
  Direccion direction_;
};