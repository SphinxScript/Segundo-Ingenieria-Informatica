#pragma once
#include "arbol.h"
#include <iostream>

template <class T>
class ABE : public AB<T> {
 public:
  ABE(NodoB<T>* raiz = nullptr) : AB<T>(raiz) {}
  bool insertar(const T& dato) override;
  bool buscar(const T& dato) const override;
  void inorden(std::ostream&) const override;
 private:
  bool insertar_equilibrado_(NodoB<T>* nodo, const T& dato);
  bool buscar_recursivo_(NodoB<T>* nodo, const T& dato) const;
  int tamano_(NodoB<T>* nodo) const;
  void inorden_recursivo_(NodoB<T>* nodo, std::ostream& os) const {
    if (nodo == nullptr) {
      return;
    }
    inorden_recursivo_(nodo->izdo(), os);
    os << nodo->dato() << " ";
    inorden_recursivo_(nodo->dcho(), os);
  }
};

template <class T>
bool ABE<T>::buscar(const T& dato) const {
  return buscar_recursivo_(this->raiz, dato);
}

template <class T>
bool ABE<T>::buscar_recursivo_(NodoB<T>* nodo, const T& dato) const {
  if (nodo == nullptr) {
    return false;
  }
  if (dato == nodo->dato()) {
    return true;
  }
  return buscar_recursivo_(nodo->izdo(), dato) || buscar_recursivo_(nodo->dcho(), dato);
}

template <class T>
bool ABE<T>::insertar(const T& dato) {
  if (buscar(dato)) {
    return false;
  }

  if (this->raiz == nullptr) {
    this->raiz = new NodoB<T>(dato);
    return true;
  }

  insertar_equilibrado_(this->raiz, dato);
  return true;
}

template <class T>
bool ABE<T>::insertar_equilibrado_(NodoB<T>* nodo, const T& dato) {
  int tam_izdo = tamano_(nodo->izdo());
  int tam_dcho = tamano_(nodo->dcho());

  if (tam_izdo <= tam_dcho) {
    if (nodo->izdo() == nullptr) {
      nodo->set_izdo(new NodoB<T>(dato));
      return true;
    }

    return insertar_equilibrado_(nodo->izdo(), dato);
  }

  if (nodo->dcho() == nullptr) {
    nodo->set_dcho(new NodoB<T>(dato));
    return true;
  }

  return insertar_equilibrado_(nodo->dcho(), dato);
}


template <class T>
int ABE<T>::tamano_(NodoB<T>* nodo) const {
  if (nodo == nullptr) {
    return 0;
  }
  return 1 + tamano_(nodo->izdo()) + tamano_(nodo->dcho());
}



template <class T>
void ABE<T>::inorden(std::ostream& os) const {
  inorden_recursivo_(this->raiz, os);
}
