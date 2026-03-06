#pragma once
#include <vector>
#include <exception>
#include <iostream>


/**
 * @brief enum que representa los lados (mínimo o máximo) que se han excedido en la clase SlidingVector.
 */
enum class Svside { Minimo, Maximo };

/**
 * @brief Excepción personalizada para el manejo de índices fuera de rango en la clase SlidingVector.
 * Contiene información sobre el lado (mínimo o máximo) que se ha excedido y el índice que ha causado la excepción.
 */
class Svexception : public std::exception {
 public:
  Svexception(Svside side, int index) : side_(side), index_(index) {}
  const char* what() const noexcept override { return "SlidingVector index out of range; index: " + index_; }
  Svside side() const noexcept { return side_; }
  int index() const noexcept { return index_; }
 private:
  Svside side_;
  int index_;
};


/**
 * @brief Clase plantilla que implementa un vector deslizante (sliding vector) que permite expandirse dinámicamente en ambas direcciones (hacia adelante y hacia atrás) al acceder a índices fuera de su rango actual.
 * La clase mantiene un rango de índices válidos y lanza una excepción personalizada (Svexception) cuando se intenta acceder a un índice fuera de ese rango, indicando si se ha excedido el límite mínimo o máximo.
 * @tparam T Tipo de los elementos almacenados en el vector deslizante.
 */
template <class T>
class SlidingVector {
 public:
  SlidingVector() : min_{0}, max_{-1} {}
  SlidingVector(int min_i, int max_i, const T& fill);
  ~SlidingVector() = default;

  int min_index() const { return min_; }
  int max_index() const { return max_; }

  void EmplaceFront(const T& valor);
  void PushBack(const T& valor);
  void Resize(const int& x, const T& valor);

  const T& operator[](int indice) const;
  T& operator[](int indice);
 private:
  // min y max pueden tomar valores negativos, luego el vector interno trabajara con 
  // indices: 0 -> max_ - min_ y se accedera a los elementos con indice - min_
  // para transformarlo a indice del vector stl
  int min_;
  int max_;
  std::vector<T> datos_;
};


template <class T> SlidingVector<T>::SlidingVector(int min_i, int max_i, const T& valor) : min_(min_i), max_(max_i), datos_(max_i - min_i + 1, valor) {}

template <class T> void SlidingVector<T>::Resize(const int& x, const T& valor) {
  datos_.resize(x, valor);
}

template <class T> void SlidingVector<T>::EmplaceFront(const T& valor) {
  if (datos_.empty()) {
    datos_.push_back(valor);
    min_ = 0;
    max_ = 0;
  }
  else {
    datos_.insert(datos_.begin(), valor);
    --min_;
  }
}

template <class T> void SlidingVector<T>::PushBack(const T& valor) {
  if (datos_.empty()) {
    datos_.push_back(valor);
    min_ = 0;
    max_ = 0;
  }
  else {
    datos_.push_back(valor);
    ++max_;
  }
}

template <class T> const T& SlidingVector<T>::operator[](int indice) const {
  // std::cout << "debug: acceso const" << std::endl;
  // std::cout << "debug: accediendo a indice " << indice << " (rango actual: " << min_ << " a " << max_ << ")\n";
  if (indice < min_) throw Svexception(Svside::Minimo, indice);
  if (indice > max_) throw Svexception(Svside::Maximo, indice);
  return datos_[indice - min_];
}

template <class T> T& SlidingVector<T>::operator[](int indice) {
  // std::cout << "debug: acceso no const" << std::endl;
  // std::cout << "debug: accediendo a indice " << indice << " (rango actual: " << min_ << " a " << max_ << ")\n";
  if (indice < min_) throw Svexception(Svside::Minimo, indice);
  if (indice > max_) throw Svexception(Svside::Maximo, indice);
  return datos_[indice - min_];
}