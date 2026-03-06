#pragma once
#include "tape.h"
#include "../ant/ant.h"

class TapeReflective : public Tape {
 public:
  TapeReflective() = default;
  ~TapeReflective() override = default;
  Colores GetColor(int x, int y) const override;
  void FlipColor(int x, int y, int color = -1) override;
  void SetSize(int x, int y) override;

 protected:
  void ResolveMove(int& x, int& y, Direccion& direccion) override;
  void Print(std::ostream& os) const override;

 private:
  virtual int Minx() const override { return 0; }
  virtual int Maxx() const override { return sizeX_ - 1; }
  virtual int Miny() const override { return 0; }
  virtual int Maxy() const override { return sizeY_ - 1; }
  std::vector<std::vector<Colores>> malla_;
};