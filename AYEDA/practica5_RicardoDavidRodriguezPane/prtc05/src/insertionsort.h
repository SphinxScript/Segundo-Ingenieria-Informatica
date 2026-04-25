#pragma once

#include "sequence.h"
#include <vector>

template <class Key>
class InsertionSort {
 public:
  InsertionSort(StaticSeq<Key>& secuencia, unsigned size);
 private:
  void Sort();
  unsigned size_;
  StaticSeq<Key>& secuencia_;
};

template <class Key>
InsertionSort<Key>::InsertionSort(StaticSeq<Key>& secuencia, unsigned size) : secuencia_(secuencia), size_(size) {
  Sort();
}


template <class Key>
void InsertionSort<Key>::Sort() {
  for (int i{1}; i < size_; ++i) {
    Key key = secuencia_[i];
    int j = i - 1;
    while (j >= 0 && secuencia_[j] > key) {
      secuencia_[j + 1] = secuencia_[j];
      --j;
    }
    secuencia_[j + 1] = key;
  }
}