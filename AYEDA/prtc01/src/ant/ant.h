#pragma once

#include <iostream>
#include "../tape/tape.h"

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
 * @brief Clase que representa a la hormiga en el juego de la hormiga de Langton.
 *        Contiene información sobre su posición, orientación y métodos para moverla.
 */
class Ant {
 public:
  Ant() = default;
  Ant(const int& life_time) : life_time_(life_time) {}
  virtual ~Ant() = default;

  virtual bool Move(Tape&) = 0;
  virtual const std::string GetColorANSI() const = 0;
  virtual const std::string GetReglas() const = 0;
  virtual bool IsCarnivorous() const = 0;
  virtual double GetVoracity() const { return 0.0; }  // por defecto, las hormigas no carnívoras no tienen voracidad

  void SetPlace(int, int, int);
  std::pair<int,int> GetPosition() const { return std::pair<int,int>(x_, y_); }
  Direccion GetOrientacion() const { return direction_; }
  unsigned int GetLifeTime() const { return life_time_; }
  void GainLife(unsigned int amount) { life_time_ += amount; }
  void LoseLife(unsigned int amount) { life_time_ = (life_time_ > amount) ? life_time_ - amount : 0; }
  void Kill() { dead_ = true; }
  bool IsDead() const { return dead_; }
  
  friend std::ostream& operator<<(std::ostream& os, const Ant& ant);
 protected:
  int x_;   // fila
  int y_;   // columna
  bool dead_{false};
  Direccion direction_;
  unsigned int life_time_;
};