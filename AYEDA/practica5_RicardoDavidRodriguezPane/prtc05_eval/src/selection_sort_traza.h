#pragma once

#include "sequence.h"

template <class Key>
class SelectionSort {
 public:
  SelectionSort(StaticSeq<Key>& secuencia, unsigned size, unsigned&);
  unsigned GetAsignaciones() const { return asignaciones_; }
 private:
  void Sort();
  int size_;
  StaticSeq<Key>& secuencia_;
  unsigned& asignaciones_ = 0;
};


template <class Key>
SelectionSort<Key>::SelectionSort(StaticSeq<Key>& secuencia, unsigned size, unsigned& asignaciones) : size_(size), secuencia_(secuencia), asignaciones_(asignaciones) {
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
    asignaciones_ += 3;
    ++i;
    std::cout << "traza: " << std::endl;
    std::cout << secuencia_ << std::endl;
  }
}