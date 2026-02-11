#include <iostream>

#include "tape.h"

/**
 * @brief Sobrecarga del operador de salida para imprimir la representación de la rejilla (tape).
 * @param os Flujo de salida.
 * @param tape Objeto Tape cuya representación se desea imprimir.
 * @return Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Tape& tape) {
  std::pair<int, int> tape_size = tape.GetSize();
  std::vector<std::vector<bool>> malla = tape.GetMalla();
  //std::pair<int, int> ant_position = tape.ant_->GetPosition();

  //int antx = ant_position.first;
  //int anty = ant_position.second;

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
        os << (malla[i][j] ? "x " : "□ ");
    }
    os << std::endl;
  }
  return os;
}

/**
 * @brief Establece el tamaño de la rejilla (tape) y redimensiona la malla.
 * @param x Número de filas de la rejilla.
 * @param y Número de columnas de la rejilla.
 */
void Tape::SetSize(int x, int y) {
  sizeX_ = x;
  sizeY_ = y;
  malla_.resize(x, std::vector<bool>(y, false));
}

/**
 * @brief Cambia el color de la celda en la posición (x, y) de la rejilla (tape).
 * @param x Coordenada x (fila) de la celda.
 * @param y Coordenada y (columna) de la celda.
 */
void Tape::FlipColor(int x, int y) {
  if (!malla_[x][y]) {
    malla_[x][y] = true;
  }
  else {
    malla_[x][y] = false;
  }
}