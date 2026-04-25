#pragma once

#include "nodo.h"
#include <iostream>
#include <queue>

template <class T>
class AB {
 public:
  AB(NodoB<T>* raiz = nullptr) : raiz(raiz) {}
  virtual ~AB() {
    destruir(raiz);
  }
  virtual bool insertar(const T& dato) = 0;
  virtual bool buscar(const T& dato) const = 0;
  virtual void inorden(std::ostream& ) const = 0;
  void mostrar_por_niveles(std::ostream& os) const {
    int nivel = 0;
    std::queue<NodoB<T>*> cola;
    cola.push(this->raiz);
    while (!cola.empty()) {
      int nodos_en_nivel = cola.size();
      os << "Nivel " << nivel << ": ";
      for (int i = 0; i < nodos_en_nivel; ++i) {
        NodoB<T>* nodo_actual = cola.front();
        cola.pop();

        if (nodo_actual == nullptr) {
          os << "[.] ";
        }
        else {
          os << "[" << nodo_actual->dato() << "] ";
          cola.push(nodo_actual->izdo());
          cola.push(nodo_actual->dcho());
        }
      }
      os << std::endl;
      ++nivel;
    }
  }

 protected:
  NodoB<T>* raiz;
 private:
  void destruir(NodoB<T>* nodo) {
    if (nodo == nullptr) {
      return;
    }
    destruir(nodo->izdo());
    destruir(nodo->dcho());
    delete nodo;
  }
};

template <class T>
std::ostream& operator<<(std::ostream& os, const AB<T>& arbol) {
  arbol.mostrar_por_niveles(os);
  return os;
}