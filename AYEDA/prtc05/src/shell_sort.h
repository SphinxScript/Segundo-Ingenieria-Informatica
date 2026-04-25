#pragma once

#include "sequence.h"
#include <vector>


template <class Key>
class ShellSort {
 public:
  ShellSort(StaticSeq<Key>& secuencia, unsigned size, double alpha);
 private:
  void Sort();

  int size_;
  double alpha_;
  StaticSeq<Key>& secuencia_;
};


template <class Key>
ShellSort<Key>::ShellSort(StaticSeq<Key>& secuencia, unsigned size, double alpha) : size_(size), alpha_(alpha), secuencia_(secuencia) {
  Sort();
}

template <class Key>
void ShellSort<Key>::Sort() {
  for (int salto{size_ / 2}; salto > 0; salto *= alpha_) {
    for (int i{salto}; i < size_; ++i) {
      Key temp = secuencia_[i];
      int j = i;
      while (j >= salto && secuencia_[j - salto] > temp) {
        secuencia_[j] = secuencia_[j - salto];
        j -= salto;
      }
      secuencia_[j] = temp;
    }
  }
}