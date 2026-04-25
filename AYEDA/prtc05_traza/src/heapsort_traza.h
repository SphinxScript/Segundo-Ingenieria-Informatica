#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "sequence.h"

template <class Key>
class HeapSort {
 public:
  HeapSort(StaticSeq<Key>& secuencia, unsigned size);
 private:
  void Sort();
  void Shiftdown(std::vector<Key>&, unsigned, unsigned);
  void Buildheap(std::vector<Key>&);
  unsigned size_;
  StaticSeq<Key>& secuencia_;
};

template <class Key>
HeapSort<Key>::HeapSort(StaticSeq<Key>& secuencia, unsigned size) : size_(size), secuencia_(secuencia)  {
  Sort();
}

template <class Key>
void HeapSort<Key>::Sort() {
  if (size_ < 2) return;
  // copiamos la secuencia a vector
  std::vector<Key> monticulo(size_);
  for (unsigned i{0}; i < size_; ++i) {
    monticulo[i] = secuencia_[i];
  }

  Buildheap(monticulo);
  std::cout << "traza: " << std::endl;
  std::cout << secuencia_ << std::endl;
  for (int end = size_ - 1; end > 0; --end) {
    std::swap(monticulo[0], monticulo[end]);
    Shiftdown(monticulo, 0, end);
    std::cout << "traza: " << std::endl;
    for (auto& elem : monticulo) {
      std::cout << elem << " ";
    }
    std::cout << std::endl << std::endl;
  }

  for (unsigned i{0}; i < size_; ++i) {
    secuencia_[i] = monticulo[i];
  }
}

template <class Key>
void HeapSort<Key>::Buildheap(std::vector<Key>& vector) {
  for (int i = int(vector.size()) / 2 - 1; i >= 0; --i) {
    Shiftdown(vector, i, size_);
  }
}

template <class Key>
void HeapSort<Key>::Shiftdown(std::vector<Key>& vector_ordenar, unsigned idx_nodo_padre, unsigned recorrido) {
  while (true) {
    unsigned idx_hijo_izq = 2 * idx_nodo_padre + 1;
    unsigned idx_hijo_drch = 2 * idx_nodo_padre + 2;
    unsigned indice_max_elm = idx_nodo_padre;
    if (idx_hijo_izq < recorrido && vector_ordenar[idx_hijo_izq] > vector_ordenar[indice_max_elm]) {
      indice_max_elm = idx_hijo_izq;
    }
    if (idx_hijo_drch < recorrido && vector_ordenar[idx_hijo_drch] > vector_ordenar[indice_max_elm]) {
      indice_max_elm = idx_hijo_drch;
    }
    if (indice_max_elm == idx_nodo_padre) {
      break;
    }
    std::swap(vector_ordenar[idx_nodo_padre], vector_ordenar[indice_max_elm]);
    idx_nodo_padre = indice_max_elm;
  }
}