#pragma once


class Nif {

 public:
  Nif();
  Nif(const long& nif) : nif_{nif} {}
  operator long() const { return nif_; }
  bool operator<(const Nif& otro)  const { return (nif_ < long(otro)); }
  bool operator>(const Nif& otro)  const { return (nif_ > long(otro)); }
  bool operator>=(const Nif& otro) const { return (nif_ >= long(otro)); }
  bool operator<=(const Nif& otro) const { return (nif_ <= long(otro)); }
  bool operator==(const Nif& otro) const { return (nif_ == long(otro)); }
  bool operator!=(const Nif& otro) const { return (nif_ != long(otro)); }
 private:
  long nif_;
};