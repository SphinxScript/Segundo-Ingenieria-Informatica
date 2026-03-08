#pragma once

#include "ant.h"
#include "ant_reglas.h"

class AntCarn : public AntReglas {
 public:
  AntCarn() = default;
  AntCarn(const std::string& reglas, const std::string& ANSI, unsigned int lifetime, double voracity) : AntReglas(reglas, ANSI, lifetime), voracity_(voracity) {}
  double GetVoracity() const { return voracity_; }
  protected:
  void ManageLife(const Colores&) override;
 private:
  double voracity_;   // porcentaje de vida que quita
  bool IsCarnivorous() const override { return true; }
};