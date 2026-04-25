#pragma once

template <class T>
class NodoB {
 public:
  explicit NodoB(const T& dato) : dato_(dato), izdo_(nullptr), dcho_(nullptr) {}
  virtual ~NodoB() = default;

  const T& dato() const { return dato_; }
  NodoB<T>* izdo() const { return izdo_; }
  NodoB<T>* dcho() const { return dcho_; }

  void set_izdo(NodoB<T>* nodo) { izdo_ = nodo; }
  void set_dcho(NodoB<T>* nodo) { dcho_ = nodo; }
 private:
  T dato_;
  NodoB<T>* izdo_;
  NodoB<T>* dcho_;
};