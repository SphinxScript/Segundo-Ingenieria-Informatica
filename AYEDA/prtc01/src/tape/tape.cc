#include <iostream>

#include "tape.h"

/**
 * @brief Sobrecarga del operador de salida para imprimir la representación de la rejilla (tape).
 * @param os Flujo de salida.
 * @param tape Objeto Tape cuya representación se desea imprimir.
 * @return Referencia al flujo de salida.
 */
// std::ostream& operator<<(std::ostream& os, const Tape& tape) {
//   std::pair<int, int> tape_size = tape.GetSize();
//   //const std::vector<std::vector<Colores>>& malla = tape.GetMalla();
//   //std::pair<int, int> ant_position = tape.ant_->GetPosition();

//   //int antx = ant_position.first;
//   //int anty = ant_position.second;

//   // cabecera columnas
//   os << "    ";
//   for (int j = 0; j < tape_size.second; ++j) {
//     os << j % 10 << " ";
//   }
//   os << std::endl;
//   for (int i = 0; i < tape_size.first; ++i) {
//     // indices fila
//     os << i % 10 << " | ";
//     for (int j = 0; j < tape_size.second; ++j) {
//       switch(tape.GetColor(i, j)) {
//         case Colores::c0:
//           os << "□ ";
//           break;
//         case Colores::c1:
//           os << "\033[34m■\033[0m ";  // azul oscuro
//           break;
//         case Colores::c2:
//           os << "\033[32m■\033[0m ";  // verde oscuro
//           break;
//         case Colores::c3:
//           os << "\033[31m■\033[0m ";  // rojo oscuro
//           break;
//         case Colores::c4:
//           os << "\033[33m■\033[0m ";  // amarillo oscuro
//           break;
//       }
//     }
//     os << std::endl;
//   }
//   return os;
// }

// Colores Tape::GetColor(int x, int y) const {
//   return malla_[x][y];
// }

/**
 * @brief Establece el tamaño de la rejilla (tape) y redimensiona la malla.
 * @param x Número de filas de la rejilla.
 * @param y Número de columnas de la rejilla.
 */
// void Tape::SetSize(int x, int y) {
//   sizeX_ = x;
//   sizeY_ = y;
//   malla_.resize(x, std::vector<Colores>(y, Colores::c0));
// }

/**
 * @brief Cambia el color de la celda en la posición (x, y) de la rejilla (tape).
 * @param x Coordenada x (fila) de la celda.
 * @param y Coordenada y (columna) de la celda.
 * @param color Color a aplicar (1-4). 
 *              si no se pasa el color, es que la hormiga esta haciendo el cambio de color
 *              por lo que se cambia al siguiente color de la secuencia (c0 -> c1 -> c2 -> c3 -> c4 -> c0).
 */
// void Tape::FlipColor(int x, int y, int color) {
//   if (color != -1) {
//     malla_[x][y] = static_cast<Colores>(color);
//     return;
//   }
//   else {
//     int actual = static_cast<int>(malla_[x][y]);
//     int siguiente = (actual + 1) % num_colores_;
//     malla_[x][y] = static_cast<Colores>(siguiente);
//   }
// }