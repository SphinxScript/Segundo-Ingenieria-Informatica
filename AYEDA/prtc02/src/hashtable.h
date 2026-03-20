#pragma once

#include "sequence.h"
#include "dispersionfunction.h"
#include "explorationfunction.h"


#define MAX_TRY 10

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

template<class Key, class Container> HashTable<Key, Container>::~HashTable() {
  for (unsigned i{0}; i < tablesize_; ++i) {
    delete table_[i];
  }
}

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
 * ---CLASE ESPECIALIZACIÓN PARCIAL---
 * 
 * 
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

template<class Key> HashTable<Key, DynamicSeq<Key>>::HashTable(unsigned tablesize, DispersionFunction<Key>& fd)
  : tablesize_(tablesize),
    table_(tablesize),
    fd_(fd)
{
  for (int i{0}; i < tablesize; ++i) {
    table_[i] = new DynamicSeq<Key>();
  }
}

template <class Key> HashTable<Key, DynamicSeq<Key>>::~HashTable() {
  for (int i{0}; i < tablesize_; ++i) {
    delete table_[i];
  }
}

template <class Key> bool HashTable<Key, DynamicSeq<Key>>::Search(const Key& clave) const {
  unsigned posicion = fd_(clave);
  return table_[posicion]->Search(clave);
}

template <class Key> bool HashTable<Key, DynamicSeq<Key>>::Insert(const Key& clave) {
  unsigned posicion = fd_(clave);
  if (table_[posicion]->Search(clave)) return false;
  return table_[posicion]->Insert(clave);
}