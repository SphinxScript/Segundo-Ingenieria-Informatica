#pragma once


/**
 * @brief DispersionFunction representa una función de dispersión genérica para claves de tipo Key.
 */
template<class Key>
class DispersionFunction {
 public:
  virtual ~DispersionFunction() = default;
  virtual unsigned operator() (const Key& key) const = 0;
};


/**
 * @brief DfModule implementa una función de dispersión basada en el módulo de la clave.
 */
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


/**
 * @brief DfSum implementa una función de dispersión que suma los dígitos de la clave.
 */
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


/**
 * @brief DfRandom implementa una función de dispersión que genera un número aleatorio basado en la clave.
 */
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