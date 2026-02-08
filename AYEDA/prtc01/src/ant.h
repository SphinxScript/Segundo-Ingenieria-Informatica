#pragma once

#include <iostream>
#include "tape.h"

/**
 * @brief enumeración para representar las direcciones de la hormiga.
 */
enum class Direccion {
  left,
  right,
  up,
  down
};

class Tape;  // declaracion adelantada

/**
 * @brief Clase que representa a la hormiga en el juego de la hormiga de Langton. Contiene información sobre su posición, orientación y métodos para moverla.
 */
class Ant {
 public:
  Ant() = default;
  bool Move(bool, Tape&);
  void SetPlace(int, int, int);
  std::pair<int,int> GetPosition() const { return std::pair<int,int>(x_, y_); }
  Direccion GetOrientacion() const { return direction_; }
  friend std::ostream& operator<<(std::ostream& os, const Ant& ant);
 private:
  // posicion de la hormiga
  int x_;   // fila
  int y_;   // columna
  // dirección de la hormiga, usamos la enumeración para representar las direcciones
  Direccion direction_;
};