#pragma once

#include "../ant/ant.h"
#include <vector>
#include <iostream>

class Ant;  // declaración adelantada

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
  Tape() {};
  void SetColores(int num_colores) { num_colores_ = num_colores; }

  std::vector<std::vector<Colores>> GetMalla() const { return malla_; }
  std::pair<int, int> GetSize() const { return std::pair(sizeX_, sizeY_); }
  int GetNumColores() const { return num_colores_; }

  void FlipColor(int, int, int color = -1);
  void SetSize(int, int);
  
  friend std::ostream& operator<<(std::ostream& os, const Tape& tape);
  
 private:
  int sizeX_;
  int sizeY_;
  int num_colores_;
  //const Ant* ant_;    // tenemos un puntero a la hormiga para poder acceder a su posición y orientación, y así saber qué color pintar en cada paso
  std::vector<std::vector<Colores>> malla_;
};