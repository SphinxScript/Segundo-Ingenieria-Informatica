#pragma once


#include "ant.h"


class AntReglas : public Ant {
 public:
  AntReglas(const std::string& reglas, const std::string& ANSI, unsigned int lifetime) : Ant(lifetime), reglas_(reglas), ANSI_color_(ANSI) {}
  bool Move(Tape&) override;
  const std::string GetColorANSI() const override { return ANSI_color_; }
  const std::string GetReglas() const { return reglas_; }
 protected:
  virtual void ManageLife(const Colores&) = 0;
 private:
  std::string reglas_;
  std::string ANSI_color_;
};