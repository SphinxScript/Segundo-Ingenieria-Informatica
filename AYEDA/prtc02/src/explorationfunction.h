#pragma once
#include "dispersionfunction.h"

template <class Key>
class ExplorationFunction {
 public:
  virtual ~ExplorationFunction() = default;
  virtual unsigned operator() (const Key& clave, unsigned intento) const = 0;
};


template <class Key>
class LinearExploration : public ExplorationFunction<Key> {
 public:
  unsigned operator() (const Key&, unsigned intento) const override {
    return intento;
  }
};

template <class Key>
class SquareExploration : public ExplorationFunction<Key> {
 public:
  unsigned operator() (const Key&, unsigned intento) const override {
    return intento * intento;
  }
};


template <class Key>
class DoubleDispersionExpl : public ExplorationFunction<Key> {
 public:
  DoubleDispersionExpl(const DispersionFunction<Key>& function) : f_(function) {}

  unsigned operator() (const Key& clave, unsigned intento) const override {
    unsigned paso = f_(clave);
    if (paso == 0) paso = 1;    // evitar ciclo infinito
    return paso * intento;
  }
 private:
  const DispersionFunction<Key>& f_;
};

template <class Key>
class RehashingExploration : public ExplorationFunction<Key> {
 public:
  RehashingExploration(unsigned tablesize) : tablesize_(tablesize) {}
  
  unsigned operator() (const Key& clave, unsigned intento) const override {
    srand(static_cast<unsigned>(long(clave)));
    unsigned value = 0;
    for (unsigned i{0}; i < intento; ++i) {
      value = rand();
    }
    return value % tablesize_;
  }
 private:
  unsigned tablesize_;
};