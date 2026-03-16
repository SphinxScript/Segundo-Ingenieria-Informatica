#include "nif.h"
#include <random>

Nif::Nif() {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(10000000, 99999999);
  nif_ = dist(rng);
}