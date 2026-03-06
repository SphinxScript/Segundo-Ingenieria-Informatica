#pragma once

#include <vector>
#include <iostream>
#include "../ant/ant.h"

class Ant;  // declaración adelantada
enum class Direccion;  // declaración adelantada

enum class Colores {
  c0,   // blanco por defecto
  c1,   // azul oscuro
  c2,   // verde oscuro
  c3,   // rojo oscuro
  c4,   // amarillo oscuro
};

/**
 * @brief Clase que representa la rejilla (tape) en el juego de la hormiga de Langton.
 * Contiene información sobre el tamaño de la rejilla, el estado de cada celda y un
 * puntero a la hormiga para acceder a su posición y orientación.
 */

class Tape {
 public:
  Tape() = default;
  virtual ~Tape() = default;

  void SetColores(int num_colores) { num_colores_ = num_colores; }
  int GetNumColores() const { return num_colores_; }
  std::pair<int, int> GetSize() const { return std::pair(sizeX_, sizeY_); }
  //const std::vector<std::vector<Colores>>& GetMalla() const { return malla_; }
  
  virtual Colores GetColor(int x, int y) const = 0;
  virtual void FlipColor(int, int, int color = -1) = 0;
  virtual void SetSize(int, int) = 0;

  void ResolvePosition(int& x, int& y, Direccion& direccion) { ResolveMove(x, y, direccion); }

  friend std::ostream& operator<<(std::ostream& os, const Tape& tape) {
    tape.Print(os);
    return os;
  }
  virtual int Minx() const = 0;
  virtual int Maxx() const = 0;
  virtual int Miny() const = 0;
  virtual int Maxy() const = 0;
  
 protected:
  virtual void ResolveMove(int& x, int& y, Direccion&) = 0;
  virtual void Print(std::ostream& os) const = 0;

  int sizeX_;
  int sizeY_;
  int num_colores_;
  //std::vector<std::vector<Colores>> malla_;
};