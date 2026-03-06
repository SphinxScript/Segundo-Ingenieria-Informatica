#pragma once

#include "../sliding_vector.h"
#include "tape.h"

class TapeSliding : public Tape {
 public:
  TapeSliding() = default;
  ~TapeSliding() override = default;

  void SetSize(int x, int y) override;
  void FlipColor(int x, int y, int color = -1) override;
  Colores GetColor(int x, int y) const override;

 protected:
  void ResolveMove(int& x, int& y, Direccion& direccion) override;
  void Print(std::ostream& os) const override;

 private:
  SlidingVector<SlidingVector<Colores>> malla_;

  void InsideMove(int& x, int& y);
  void ExpandRow(const Svexception& exc, int& y);
  void ExpandCol(const Svexception& exc, int& x);

  virtual int Minx() const override { return malla_.min_index(); }
  virtual int Maxx() const override { return malla_.max_index(); }
  virtual int Miny() const override { return malla_[malla_.min_index()].min_index(); }
  virtual int Maxy() const override { return malla_[malla_.min_index()].max_index(); }
  SlidingVector<Colores> MakeEmptyRow() const;
};