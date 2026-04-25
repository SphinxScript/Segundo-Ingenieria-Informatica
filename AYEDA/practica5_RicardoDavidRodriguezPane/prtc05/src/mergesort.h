#pragma once


#include "sequence.h"
#include <vector>


template <class Key>
class MergeSort {
 public:
  MergeSort(StaticSeq<Key>& secuencia, unsigned size);
 private:
  void Sort(std::vector<Key>&, unsigned, unsigned);
  void Merge(std::vector<Key>& vector_ordenar, unsigned left, unsigned mid, unsigned right);
  unsigned size_;
  StaticSeq<Key>& secuencia_;
};


template <class Key>
MergeSort<Key>::MergeSort(StaticSeq<Key>& secuencia, unsigned size) :  size_(size), secuencia_(secuencia) {
  if (size_ == 0) return;
  std::vector<Key> vector_ordenar(size_);
  for (unsigned i = 0; i < size_; ++i) {
    vector_ordenar[i] = secuencia_[i];
  }
  Sort(vector_ordenar, 0, size_ - 1);
  for (unsigned i{0}; i < size_; ++i) {
    secuencia_[i] = vector_ordenar[i];
  }
}


template <class Key>
void MergeSort<Key>::Sort(std::vector<Key>& vector_ordenar, unsigned left, unsigned right) {
  if (left >= right) return;
  
  unsigned mid = left + (right - left) / 2;
  Sort(vector_ordenar, left, mid);
  Sort(vector_ordenar, mid + 1, right);
  Merge(vector_ordenar, left, mid, right);
}

template <class Key>
void MergeSort<Key>::Merge(std::vector<Key>& vector_ordenar, unsigned left, unsigned mid, unsigned right) {
  // indices que usaremos aqui para recorrer ambas partes
  unsigned idx1 = left;
  unsigned idx2 = mid + 1;
  // vector auxiliar
  std::vector<Key> auxiliar;

  while (idx1 <= mid && idx2 <= right) {
    if (vector_ordenar[idx1] <= vector_ordenar[idx2]) {
      auxiliar.push_back(vector_ordenar[idx1]);
      ++idx1;
    }
    else {
      auxiliar.push_back(vector_ordenar[idx2]);
      ++idx2;
    }
  }
  while (idx1 <= mid) {
    auxiliar.push_back(vector_ordenar[idx1]);
    ++idx1;
  }
  while (idx2 <= right) {
    auxiliar.push_back(vector_ordenar[idx2]);
    ++idx2;
  }
  unsigned k{0};
  for (unsigned i{left}; i <= right; ++i) {
    vector_ordenar[i] = auxiliar[k];
    ++k;
  }
}