#pragma once
#include "arbol.h"


template <class T>
class ABB : public AB<T> {
 public:
  ABB(NodoB<T>* raiz = nullptr) : AB<T>(raiz) {}
  bool insertar(const T& dato) override {
    if (this->raiz == nullptr) {
      this->raiz = new NodoB<T>(dato);
      return true;
    }

    NodoB<T>* nodo_actual = this->raiz;
    NodoB<T>* nodo_padre = nullptr;

    while (nodo_actual != nullptr) {
      nodo_padre = nodo_actual;

      if (dato == nodo_actual->dato()) {
        return false;
      }

      if (dato < nodo_actual->dato()) {
        nodo_actual = nodo_actual->izdo();
      }
      else {
        nodo_actual = nodo_actual->dcho();
      }
    }
    if (dato < nodo_padre->dato()) {
      nodo_padre->set_izdo(new NodoB<T>(dato));
    }
    else {
      nodo_padre->set_dcho(new NodoB<T>(dato));
    }
    return true;
  }
  bool buscar(const T& dato) const override {
    return buscar_iterativo_(this->raiz, dato);
  }
  void inorden(std::ostream& os) const override {
    inorden_recursivo_(this->raiz, os);
    os << std::endl;
  }
 private:
  bool buscar_iterativo_(NodoB<T>* nodo, const T& dato) const {
    NodoB<T>* nodo_actual = nodo;
    while (nodo_actual != nullptr) {
      if (dato == nodo_actual->dato()) {
        return true;
      }
      else if (dato < nodo_actual->dato()) {
        nodo_actual = nodo_actual->izdo();
      }
      else {
        nodo_actual = nodo_actual->dcho();
      }
    }
    return false;
  }
  void inorden_recursivo_(NodoB<T>* nodo, std::ostream& os) const {
    if (nodo != nullptr) {
      inorden_recursivo_(nodo->izdo(), os);
      os << nodo->dato() << " ";
      inorden_recursivo_(nodo->dcho(), os);
    }
  }
};