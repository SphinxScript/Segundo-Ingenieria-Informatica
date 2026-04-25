#pragma once

#include "sequence.h"

template <class Key>
class SelectionSort {
 public:
  SelectionSort(StaticSeq<Key>& secuencia, unsigned size);
 private:
  void Sort();
  int size_;
  StaticSeq<Key>& secuencia_;
};


template <class Key>
SelectionSort<Key>::SelectionSort(StaticSeq<Key>& secuencia, unsigned size) : size_(size), secuencia_(secuencia) {
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
    secuencia_.Swap(i, indx_menor);
    ++i;
  }
}