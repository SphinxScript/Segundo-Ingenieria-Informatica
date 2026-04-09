#include "nif.h"
#include <random>

/**
 * @brief Constructor de la clase Nif.
 * Genera un número de NIF aleatorio entre 10000000 y 99999999.
 */
Nif::Nif() {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(10000000, 99999999);
  nif_ = dist(rng);
}