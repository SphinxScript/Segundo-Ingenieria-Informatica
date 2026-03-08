#include "ant_herb.h"

void AntHerb::ManageLife(const Colores& colores) {
  switch (colores) {
    case Colores::c1 :
      life_time_ += 2;
      break;
    case Colores::c2 :
      life_time_ +=3;
      break;
    case Colores::c3 :
      life_time_ +=4;
      break;
    case Colores::c4 :
      life_time_ +=5;
      break;
    default :
      life_time_++;
      break;
  }
}