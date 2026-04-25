#pragma once

#include "sequence.h"

template <class Key>
class BubbleSort {
 public:
  BubbleSort(StaticSeq<Key>& secuencia, unsigned size);
 private:
  void Sort();
  unsigned size_;
  StaticSeq<Key>& secuencia_;
};


template <class Key>
BubbleSort<Key>::BubbleSort(StaticSeq<Key>& secuencia, unsigned size) : size_(size), secuencia_(secuencia) {
  Sort();
}


template <class Key>
void BubbleSort<Key>::Sort() {
  int recorrido = size_;
  while (recorrido > 1) {
    for (int i{0}; i < recorrido - 1; ++i) {
      if (secuencia_[i] > secuencia_[i + 1]) {
        secuencia_.Swap(i, i + 1);
      }
    }
    --recorrido;
  }
}