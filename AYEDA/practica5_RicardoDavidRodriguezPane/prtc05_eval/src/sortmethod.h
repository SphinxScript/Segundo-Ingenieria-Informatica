#pragma once

#include "selection_sort_traza.h"
#include "sequence.h"
#include "bubble_sort_traza.h"
#include "mergesort_traza.h"
#include "heapsort_traza.h"
#include "shell_sort_traza.h"

template <class Key>
class SortMethod {
 public:
  SortMethod(StaticSeq<Key>& secuencia, unsigned size) : secuencia_(secuencia), size_(size) {};
  virtual ~SortMethod() = default;
  virtual void Sort() = 0;
  unsigned GetAsignaciones() const { return asignaciones_; }
  void SetAsignacionesZero() { asignaciones_ = 0; }
 protected:
  StaticSeq<Key>& secuencia_;
  unsigned size_;
  unsigned asignaciones_ = 0;
};


template <class Key>
class MethodSelection : public SortMethod<Key> {
 public:
  MethodSelection(StaticSeq<Key>& secuencia, unsigned size) : SortMethod<Key>(secuencia, size) {};
  void Sort() override { SelectionSort<Key> ordenacion(this->secuencia_, this->size_, this->asignaciones_); };
};

template <class Key>
class MethodBubble : public SortMethod<Key> {
 public:
  MethodBubble(StaticSeq<Key>& secuencia, unsigned size) : SortMethod<Key>(secuencia, size) {};
  void Sort() override { BubbleSort<Key> ordenacion(this->secuencia_, this->size_, this->asignaciones_); };
};

template <class Key>
class MethodMerge : public SortMethod<Key> {
 public:
  MethodMerge(StaticSeq<Key>& secuencia, unsigned size) : SortMethod<Key>(secuencia, size) {};
  void Sort() override { MergeSort<Key> ordenacion(this->secuencia_, this->size_, this->asignaciones_); };
};


template <class Key>
class MethodHeap : public SortMethod<Key> {
 public:
  MethodHeap(StaticSeq<Key>& secuencia, unsigned size) : SortMethod<Key>(secuencia, size) {};
  void Sort() override { HeapSort<Key> ordenacion(this->secuencia_, this->size_, this->asignaciones_); };
};


template <class Key>
class MethodShell : public SortMethod<Key> {
 public:  MethodShell(StaticSeq<Key>& secuencia, unsigned size, double alpha) : SortMethod<Key>(secuencia, size), alpha_(alpha) {};
  void Sort() override { ShellSort<Key> ordenacion(this->secuencia_, this->size_, alpha_, this->asignaciones_); };
 private:
  double alpha_;
};