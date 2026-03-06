#include "tape_sliding.h"
#include <cassert>


Colores TapeSliding::GetColor(int x, int y) const {
  return malla_[x][y];
}

void TapeSliding::FlipColor(int x, int y, int color) {
  if (color != -1) {
    malla_[x][y] = static_cast<Colores>(color);
  }
  else {
    int actual = static_cast<int>(malla_[x][y]);
    int siguiente = (actual + 1) % num_colores_;
    malla_[x][y] = static_cast<Colores>(siguiente);
  }
}

SlidingVector<Colores> TapeSliding::MakeEmptyRow() const {
  if (sizeX_ == 0) { // en caso de que no haya filas, se crea una fila vacía con el tamaño actual de columnas (sizeY_)
    return SlidingVector<Colores>(0, sizeY_ - 1, Colores::c0);
  }
  // si hay filas, se toma el rango de columnas de la primera fila (que se asume que es representativa del resto) para crear la nueva fila vacía
  int fila_ref = malla_.min_index();
  int min_y = malla_[fila_ref].min_index();
  int max_y = malla_[fila_ref].max_index();
  return SlidingVector<Colores>(min_y, max_y, Colores::c0);
}

/**
 * @brief Establece el tamaño de la rejilla. Solo se hace una vez, al inicio
 * @param x Número de filas.
 * @param y Número de columnas.
 */
void TapeSliding::SetSize(int x, int y) {
  sizeX_ = x;   // filas
  sizeY_ = y;   // columnas
  SlidingVector<Colores> fila(0, sizeY_ - 1, Colores::c0);  // vila vacía, desde 0 a sizeY_-1
  malla_ = SlidingVector<SlidingVector<Colores>>(0, x - 1, fila);
}


void TapeSliding::ResolveMove(int& x, int& y, Direccion& direccion) {
  InsideMove(x, y);
}

void TapeSliding::InsideMove(int& x, int& y) {
  while (true) {
    try { // primero fila
      malla_[x];
    }
    catch (const Svexception& exc) {
      ExpandRow(exc, x);
      continue;
    }
    try { // luego columna
      malla_[x][y];
    }
    catch (const Svexception& exc) {
      ExpandCol(exc, y);
      continue;
    }
    break;
  }
}


void TapeSliding::ExpandRow(const Svexception& exc, int& x) {
  SlidingVector<Colores> nueva_fila = MakeEmptyRow();
  if (exc.side() == Svside::Minimo) {
    malla_.EmplaceFront(nueva_fila);
    ++sizeX_;
  }
  else {
    malla_.PushBack(nueva_fila);
    ++sizeX_;
  }
}

void TapeSliding::ExpandCol(const Svexception& exc, int& y) {
  if (exc.side() == Svside::Minimo) {
    for (int i{malla_.min_index()}; i <= malla_.max_index(); ++i) {
      malla_[i].EmplaceFront(Colores::c0);
    }
    ++sizeY_;
  }
  else {
    // Nos salimos por DERECHA: push_back en cada fila
    for (int i = malla_.min_index(); i <= malla_.max_index(); ++i) {
      malla_[i].PushBack(Colores::c0);
    }
    ++sizeY_;
    // y se queda tal cual (normalmente y == old sizeY_)
  }
}

void TapeSliding::Print(std::ostream& os) const {
  int fila_ref = malla_.min_index();

  int min_x = malla_.min_index();
  int max_x = malla_.max_index();
  int min_y = malla_[fila_ref].min_index();
  int max_y = malla_[fila_ref].max_index();

  // cabecera columnas
  os << "    ";
  for (int j = min_y; j <= max_y + 1; ++j) {
    os << j % 10 << " ";
  }
  os << std::endl;
  for (int i = min_x; i <= max_x + 1; ++i) {
    // indices fila
    os << i % 10 << " | ";
    for (int j = min_y; j <= max_y + 1; ++j) {
      switch(GetColor(i, j)) {
        case Colores::c0:
          os << "□ ";
          break;
        case Colores::c1:
          os << "\033[34m■\033[0m ";  // azul oscuro
          break;
        case Colores::c2:
          os << "\033[32m■\033[0m ";  // verde oscuro
          break;
        case Colores::c3:
          os << "\033[31m■\033[0m ";  // rojo oscuro
          break;
        case Colores::c4:
          os << "\033[33m■\033[0m ";  // amarillo oscuro
          break;
      }
    }
    os << std::endl;
  }
}