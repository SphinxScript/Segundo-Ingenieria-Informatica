#pragma once
#include <list>
#include <vector>

template <class Key>
class Sequence {
 public:
  virtual ~Sequence() = default;
  virtual bool Search(const Key& key) const = 0;
  virtual bool Insert(const Key& key) = 0;
  virtual bool IsFull() const = 0;
};



template <class Key>
class DynamicSeq : public Sequence<Key> {
 public:
  bool Search(const Key& key) const override {
    for (const Key& dato : data_) {
      if (dato == key) return true;
    }
    return false;
  }

  bool Insert(const Key& key) override {
    if (this->Search(key)) return false;
    data_.push_back(key);
    return true;
  }

  bool IsFull() const override {
    return false;
  }

 private:
  std::list<Key> data_;
};



template <class Key>
class StaticSeq : public Sequence<Key> {
 public:
  StaticSeq(unsigned block_size) : block_size_(block_size), data_(block_size), occupied_(block_size, false) {}
  bool Search(const Key& key) const override {
    for (unsigned i{0}; i < block_size_; ++i) {
      if (occupied_[i] && data_[i] == key) return true;
    }
    return false;
  }

  bool Insert(const Key& key) override {
    if (this->Search(key)) return false;
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
  
 private:
  unsigned block_size_;
  std::vector<Key> data_;
  std::vector<bool> occupied_;
};