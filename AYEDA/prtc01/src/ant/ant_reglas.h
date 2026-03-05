#pragma once


#include "ant.h"


class AntReglas : public Ant {
 public:
  AntReglas(const std::string& reglas, const std::string& ANSI) : reglas_(reglas), ANSI_color_(ANSI) {}
  bool Move(Tape&) override;
  const std::string GetColorANSI() const override { return ANSI_color_; }
  const std::string GetReglas() const { return reglas_; }
 private:
  std::string reglas_;
  std::string ANSI_color_;
};