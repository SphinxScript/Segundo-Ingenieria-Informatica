#pragma once

#include "sequence.h"
#include <iostream>

template <class Key>
class BubbleSort {
 public:
  BubbleSort(StaticSeq<Key>& secuencia, unsigned size, unsigned& asignaciones);
  unsigned GetAsginaciones() const { return asignaciones_; }
 private:
  void Sort();
  unsigned size_;
  StaticSeq<Key>& secuencia_;
  unsigned& asignaciones_ = 0;
};


template <class Key>
BubbleSort<Key>::BubbleSort(StaticSeq<Key>& secuencia, unsigned size, unsigned& asignaciones) : size_(size), secuencia_(secuencia), asignaciones_(asignaciones) {
  Sort();
}


template <class Key>
void BubbleSort<Key>::Sort() {
  int recorrido = size_;
  while (recorrido > 1) {
    for (int i{0}; i < recorrido - 1; ++i) {
      if (secuencia_[i] > secuencia_[i + 1]) {
        secuencia_.Swap(i, i + 1);
        asignaciones_ += 3;
      }
    }
    --recorrido;
    std::cout << "traza: " << std::endl;
    std::cout << secuencia_ << std::endl;
  }
}