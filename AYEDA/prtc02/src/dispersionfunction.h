#pragma once



template<class Key>
class DispersionFunction {
 public:
  virtual ~DispersionFunction() = default;
  virtual unsigned operator() (const Key& key) const = 0;
};



template <class Key>
class DfModule : public DispersionFunction<Key> {
 public:
  DfModule(unsigned tablesize) : tablesize_(tablesize) {}

  unsigned operator() (const Key& key) const override {
    return long(key) % tablesize_;
  }
 private:
  unsigned tablesize_;
};


template <class Key>
class DfSum : public DispersionFunction<Key> {
 public:
  DfSum(unsigned tablesize) : tablesize_(tablesize) {}

  unsigned operator() (const Key& key) const override {
    long val = long(key);
    unsigned sum = 0;
    while (val > 0) {
      sum += val % 10;
      val /= 10;
    }
    return sum % tablesize_;
  }
 private:
  unsigned tablesize_;
};


template <class Key>
class DfRandom : public DispersionFunction<Key> {
 public:
  DfRandom(unsigned tablesize) : tablesize_(tablesize) {}
  unsigned operator() (const Key& key) const override {
    srand((long)key);
    return rand() % tablesize_;
  }
 private:
  unsigned tablesize_;
};