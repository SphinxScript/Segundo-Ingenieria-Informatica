#pragma once

#include <vector>
#include <iostream>

class Tape {
 public:
  Tape() {};
  std::vector<std::vector<bool>> GetMalla() const;
  void FlipColor(int, int);
  void SetSize(int, int);
  friend std::ostream& operator<<(std::ostream& os, const Tape& tape);
 private:
  int sizeX_;
  int sizeY_;
  std::vector<std::vector<bool>> malla_;
};