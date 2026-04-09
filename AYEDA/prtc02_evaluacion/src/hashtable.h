#pragma once

#include "sequence.h"
#include "dispersionfunction.h"
#include "explorationfunction.h"


#define MAX_TRY 10

/**
 * @brief Clase HashTable que implementa una tabla hash con direccionamiento abierto.
 */
template <class Key, class Container=StaticSeq<Key>>
class HashTable {
 public:
  HashTable(unsigned, DispersionFunction<Key>&, ExplorationFunction<Key>&, unsigned);
  ~HashTable();

  bool Insert(const Key&);
  bool Search(const Key&) const;

 private:
  unsigned tablesize_;
  std::vector<Sequence<Key>*> table_;
  DispersionFunction<Key>& fd_;
  ExplorationFunction<Key>& fe_;
  unsigned blocksize_;
};

/**
 * @brief Constructor de la clase HashTable.
 * @param tablesize Tamaño de la tabla hash.
 * @param fd Función de dispersión.
 * @param fe Función de exploración.
 * @param blocksize Tamaño del bloque (solo con direccionamiento cerrado).
 */
template<class Key, class Container> HashTable<Key, Container>::HashTable(unsigned tablesize, DispersionFunction<Key>& fd, ExplorationFunction<Key>& fe, unsigned blocksize)
  : tablesize_(tablesize),
    table_(tablesize),
    fd_(fd),
    fe_(fe),
    blocksize_(blocksize)
{
  for (unsigned i{0}; i < tablesize_; ++i) {
    table_[i] = new Container(blocksize_);
  }
}

/**
 * @brief Destructor de la clase HashTable.
 */
template<class Key, class Container> HashTable<Key, Container>::~HashTable() {
  for (unsigned i{0}; i < tablesize_; ++i) {
    delete table_[i];
  }
}

/**
 * @brief Método Search de la clase HashTable.
 * @param clave Clave a buscar.
 * @return true si la clave se encuentra en la tabla hash, false en caso contrario.
 */
template<class Key, class Container> bool HashTable<Key, Container>::Search(const Key& clave) const {
  unsigned posicion_inicial = fd_(clave);
  if (table_[posicion_inicial]->Search(clave)) return true;
  if (!table_[posicion_inicial]->IsFull()) return false;
  for (unsigned i{1}; i < tablesize_; ++i) {
    unsigned posicion = (posicion_inicial + fe_(clave, i)) % tablesize_;
    if (table_[posicion]->Search(clave)) return true;
    if (!table_[posicion]->IsFull()) return false;
  }
  return false;
}

/**
 * @brief Método Insert de la clase HashTable.
 * @param clave Clave a insertar.
 * @return true si la clave se ha insertado correctamente, false en caso contrario.
 */
template<class Key, class Container> bool HashTable<Key, Container>::Insert(const Key& clave) {
  unsigned posicion_inicial = fd_(clave);
  if (table_[posicion_inicial]->Search(clave)) return false;
  if (table_[posicion_inicial]->Insert(clave)) return true;
  for (unsigned i{1}; i < tablesize_; ++i) {
    unsigned posicion = (posicion_inicial + fe_(clave, i)) % tablesize_;
    if (table_[posicion]->Search(clave)) return false;
    if (table_[posicion]->Insert(clave)) return true;
  }
  return false;
}



/**
 * 
 * 
 * ---CLASE ESPECIALIZACIÓN PARCIAL DINAMICA---
 * 
 * 
 */


/**
 * @brief Clase HashTable especializada para el caso de direccionamiento abierto con secuencia dinámica.
 */
template <class Key>
class HashTable<Key, DynamicSeq<Key>> {
 public:
  HashTable(unsigned, DispersionFunction<Key>&);
  ~HashTable();
  bool Insert(const Key&);
  bool Search(const Key&) const;
 private:
  unsigned tablesize_;
  std::vector<Sequence<Key>*> table_;
  DispersionFunction<Key>& fd_;
};

/**
 * @brief Constructor de la clase HashTable especializada para el caso de direccionamiento abierto con secuencia dinámica.
 * @param tablesize Tamaño de la tabla hash.
 * @param fd Función de dispersión.
 */
template<class Key> HashTable<Key, DynamicSeq<Key>>::HashTable(unsigned tablesize, DispersionFunction<Key>& fd)
  : tablesize_(tablesize),
    table_(tablesize),
    fd_(fd)
{
  for (int i{0}; i < int(tablesize); ++i) {
    table_[i] = new DynamicSeq<Key>();
  }
}

/**
 * @brief Destructor de la clase HashTable especializada para el caso de direccionamiento abierto con secuencia dinámica.
 */
template <class Key> HashTable<Key, DynamicSeq<Key>>::~HashTable() {
  for (int i{0}; i < int(tablesize_); ++i) {
    delete table_[i];
  }
}

/**
 * @brief Método Search de la clase HashTable especializada para el caso de direccionamiento abierto con secuencia dinámica.
 * @param clave Clave a buscar.
 * @return true si la clave se encuentra en la tabla hash, false en caso contrario.
 */
template <class Key> bool HashTable<Key, DynamicSeq<Key>>::Search(const Key& clave) const {
  unsigned posicion = fd_(clave);
  return table_[posicion]->Search(clave);
}

/**
 * @brief Método Insert de la clase HashTable especializada para el caso de direccionamiento abierto con secuencia dinámica.
 * @param clave Clave a insertar.
 * @return true si la clave se ha insertado correctamente, false en caso contrario.
 */
template <class Key> bool HashTable<Key, DynamicSeq<Key>>::Insert(const Key& clave) {
  unsigned posicion = fd_(clave);
  if (table_[posicion]->Search(clave)) return false;
  return table_[posicion]->Insert(clave);
}