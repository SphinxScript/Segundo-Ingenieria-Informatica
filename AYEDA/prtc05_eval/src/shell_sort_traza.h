#pragma once

#include "sequence.h"
#include <vector>


template <class Key>
class ShellSort {
 public:
  ShellSort(StaticSeq<Key>& secuencia, unsigned size, double alpha, unsigned& asignaciones);
  unsigned GetAsignaciones() const { return asignaciones_; }
 private:
  void Sort();

  int size_;
  double alpha_;
  StaticSeq<Key>& secuencia_;
  unsigned& asignaciones_ = 0;
};


template <class Key>
ShellSort<Key>::ShellSort(StaticSeq<Key>& secuencia, unsigned size, double alpha, unsigned& asignaciones) : size_(size), alpha_(alpha), secuencia_(secuencia), asignaciones_(asignaciones) {
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
        ++asignaciones_;
        j -= salto;
      }
      secuencia_[j] = temp;
      ++asignaciones_;
    }
    std::cout << "traza: " << std::endl;
    std::cout << secuencia_ << std::endl;
  }
}