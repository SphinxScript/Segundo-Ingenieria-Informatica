#pragma once

#include "ant.h"
#include "ant_reglas.h"

class AntHerb : public AntReglas {
 public:
  AntHerb() = default;
  AntHerb(const std::string& reglas, const std::string& ANSI, unsigned int lifetime) : AntReglas(reglas, ANSI, lifetime) {}
 protected:
  void ManageLife(const Colores&) override;
  bool IsCarnivorous() const override { return false; }
};