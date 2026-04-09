#pragma once
#include "nif.h"
#include <string>

class Persona {
 public:
  Persona() = default;
  Persona(const Nif& nif, const std::string& nombre = "-", unsigned edad=0) : nif_{nif}, nombre_{nombre}, edad_{edad} {};
  Nif GetNif() const { return nif_; }
  std::string GetNombre() const { return nombre_; }
  unsigned GetEdad() const { return edad_; }

  operator long() const { return long(nif_); }
  operator Nif() const { return nif_; }

  bool operator<(const Persona& otro)  const { return (long(nif_) < long(otro)); }
  bool operator>(const Persona& otro)  const { return (long(nif_) > long(otro)); }
  bool operator>=(const Persona& otro) const { return (long(nif_) >= long(otro)); }
  bool operator<=(const Persona& otro) const { return (long(nif_) <= long(otro)); }
  bool operator==(const Persona& otro) const { return (long(nif_) == long(otro)); }
  bool operator!=(const Persona& otro) const { return (long(nif_) != long(otro)); }
 private:
  Nif nif_;
  std::string nombre_;
  unsigned edad_;
};