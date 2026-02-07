#include <iostream>

#include "tape.h"

std::ostream& operator<<(std::ostream& os, const Tape& tape) {
  std::pair<int, int> tape_size = tape.GetSize();
  std::vector<std::vector<bool>> malla = tape.GetMalla();
  std::pair<int, int> ant_position = tape.ant_->GetPosition();

  int antx = ant_position.first;
  int anty = ant_position.second;

  // cabecera columnas
  os << "    ";
  for (int j = 0; j < tape_size.second; ++j) {
    os << j % 10 << " ";
  }
  os << std::endl;
  for (int i = 0; i < tape_size.first; ++i) {
    // indices fila
    os << i % 10 << " | ";
    for (int j = 0; j < tape_size.second; ++j) {
      if (i == antx && j == anty && tape.ant_) {
        os << "\033[34;42m" << *tape.ant_ << "\033[0m ";
      }
      else {
        if (malla[i][j]) {    // si es true (es negro)
          os << "x ";
        }
        else {               // si es false (es blanco)
          os << "□ ";
        }
      }
    }
    os << std::endl;
  }
  return os;
}


void Tape::SetSize(int x, int y) {
  sizeX_ = x;
  sizeY_ = y;
  malla_.resize(x, std::vector<bool>(y, false));
}

void Tape::FlipColor(int x, int y) {
  if (!malla_[x][y]) {
    malla_[x][y] = true;
  }
  else {
    malla_[x][y] = false;
  }
}