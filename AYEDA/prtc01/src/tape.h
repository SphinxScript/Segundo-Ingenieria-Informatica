#pragma once

#include "ant.h"
#include <vector>
#include <iostream>

class Ant;  // declaración adelantada

class Tape {
 public:
  Tape() {};
  void SetAnt(const Ant* ant) { ant_ = ant; }

  std::vector<std::vector<bool>> GetMalla() const { return malla_; }
  std::pair<int, int> GetSize() const { return std::pair(sizeX_, sizeY_); }

  
  void FlipColor(int, int);
  void SetSize(int, int);
  
  friend std::ostream& operator<<(std::ostream& os, const Tape& tape);
  
 private:
  int sizeX_;
  int sizeY_;
  const Ant* ant_;    // tenemos un puntero a la hormiga para poder acceder a su posición y orientación, y así saber qué color pintar en cada paso
  std::vector<std::vector<bool>> malla_;
};