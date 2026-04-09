#pragma once

#include "sequence.h"

template <class Key>
class SelectionSort {
 public:
  SelectionSort(StaticSeq<Key>& secuencia, unsigned size);
 private:
  void Sort();
  unsigned size_;
  StaticSeq<Key>& secuencia_;
};


template <class Key>
SelectionSort<Key>::SelectionSort(StaticSeq<Key>& secuencia, unsigned size) : secuencia_(secuencia), size_(size) {
  Sort();
}


template <class Key>
void SelectionSort<Key>::Sort() {
  int i = 0;
  while (i < size_ - 1) {
    int indx_menor = i;
    for (int j{i + 1}; j < size_; ++j) {
      if (secuencia_[j] < secuencia_[indx_menor]) {
        indx_menor = j;
      }
    }
    Key aux = secuencia_[i];
    secuencia_[i] = secuencia_[indx_menor];
    secuencia_[indx_menor] = aux;
    ++i;
  }
}