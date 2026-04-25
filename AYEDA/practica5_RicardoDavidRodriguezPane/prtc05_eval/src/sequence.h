#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <random>

/**
 * @brief Clase abstracta Sequence que representa una secuencia de claves.
 * Esta clase se utiliza para implementar las secuencias de claves en la tabla hash.
 * Se pueden implementar diferentes tipos de secuencias, como secuencias estáticas o dinámicas.
 */
template <class Key>
class Sequence {
 public:
  virtual ~Sequence() = default;
  virtual bool Search(const Key& key) const = 0;
  virtual bool Insert(const Key& key) = 0;
  virtual bool IsFull() const = 0;
  virtual Key operator[] (const unsigned) const = 0;
  virtual Key& operator[] (const unsigned) = 0;
  virtual void print(std::ostream& os) const = 0;
};

template <class Key>
std::ostream& operator<<(std::ostream& os, const Sequence<Key>& sequence) {
  sequence.print(os);
  return os;
}

/**
 * @brief Clase DynamicSeq que representa una secuencia dinámica de claves.
 * Esta clase se utiliza para implementar la secuencia de claves en la tabla hash cuando se utiliza direccionamiento abierto con secuencia dinámica.
 * La secuencia dinámica se implementa utilizando una lista enlazada.
 */
// template <class Key>
// class DynamicSeq : public Sequence<Key> {
//  public:
//   bool Search(const Key& key) const override {
//     for (const Key& dato : data_) {
//       if (dato == key) return true;
//     }
//     return false;
//   }

//   bool Insert(const Key& key) override {
//     if (this->Search(key)) return false;
//     data_.push_back(key);
//     return true;
//   }

//   bool IsFull() const override {
//     return false;
//   }

//  private:
//   std::list<Key> data_;
// };


/**
 * @brief Clase StaticSeq que representa una secuencia estática de claves.
 * Esta clase se utiliza para implementar la secuencia de claves en la tabla hash cuando se utiliza direccionamiento abierto con secuencia estática.
 * La secuencia estática se implementa utilizando un vector de tamaño fijo.
 */
template <class Key>
class StaticSeq : public Sequence<Key> {
 public:
  StaticSeq(unsigned block_size) : block_size_(block_size), data_(block_size), occupied_(block_size, false) {};
  bool Search(const Key& key) const override {
    for (unsigned i{0}; i < block_size_; ++i) {
      if (occupied_[i] && data_[i] == key) return true;
    }
    return false;
  }

  bool Insert(const Key& key) override {
    //if (this->Search(key)) return false;
    for (unsigned i{0}; i < block_size_; ++i) {
      if (!occupied_[i]) {
        data_[i] = key;
        occupied_[i] = true;
        return true;
      }
    }
    return false;
  }

  bool IsFull() const override {
    for (bool occupied : occupied_) {
      if (!occupied) return false;
    }
    return true;
  }

  virtual Key operator[] (const unsigned idx) const override {
    return data_[idx];
  }
  virtual Key& operator[] (const unsigned idx) override {
    return data_[idx];
  }

  void print(std::ostream& os) const override {
    for (const Key& dato : data_) {
      os << dato << " ";
    }
    os << std::endl;
  }

  void Swap(unsigned antes, unsigned despues);

  
 private:
  unsigned block_size_;
  std::vector<Key> data_;
  std::vector<bool> occupied_;
};

template <class Key>
void StaticSeq<Key>::Swap(unsigned antes, unsigned despues) {
  std::swap(data_[antes], data_[despues]);
}