#include <iostream>

#include "tape.h"

std::ostream& operator<<(std::ostream& os, const Tape& tape) {
  os << "debug: aqui" << std::endl;
  std::pair<int, int> tape_size{tape.GetSize()};
  std::vector<std::vector<bool>> malla = tape.GetMalla();
  std::pair<int,int> ant_position = tape.ant_->GetPosition();
  int antx{ant_position.first};
  int anty{ant_position.second};
  for (int i{0}; i < tape_size.first; ++i) {
    for (int j{0}; j < tape_size.second; ++j) {
      if (i == antx && j == anty) {
        if (!(tape.ant_ == nullptr)) {
          os << *tape.ant_ << " ";
        }
      }
      else {
        if (malla[i][j]) {    // si vale 1 (es true)
          os << "x ";
        }
        else {                // si vale 0 (es false)
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