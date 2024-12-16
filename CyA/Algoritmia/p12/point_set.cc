/**
 * @file point_set.cc
 * @author Ricardo David Rodríguez Pane (alu0101643137@ull.edu.es)
 * @date 14/12/2024
 * @brief Contiene la implementación de los metodos de la clase point_set
 * @version 1.0
 * 
 * @details
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Computabilidad y Algoritmia
 * Curso: 2º
 * Práctica 12: Algoritmos Divide y Vencerás (Divide & Conquer). Cálculo de la envoltura convexa
 * 
 * @note
 * - 01/11/2024: Creación (primera versión) del código
 */

#include <iomanip>
#include "point_set.h"

/**
 * @brief: función publica que llama a la función privada quickHull y limpia el vector de puntos de la envolvente convexa
 * @param[in] void
 * @return void
 */
void cya::point_set::quickHullPublic(void) {
  hull_.clear();

  cya::point min_x_point;
  cya::point max_x_point;

  x_bounds(min_x_point, max_x_point);

  quickHull(cya::line(min_x_point, max_x_point), side::LEFT);
  quickHull(cya::line(min_x_point, max_x_point), side::RIGHT);

  // Remove duplicates
  std::sort(hull_.begin(), hull_.end());
  hull_.erase(std::unique(hull_.begin(), hull_.end()), hull_.end());
}

/**
 * @brief: función privada que calcula la envolvente convexa de un conjunto de puntos
 * @param[in] l: linea que contiene los puntos a calcular
 * @param[in] side: lado de la linea
 * @return void
 */
void cya::point_set::quickHull(const cya::line& l, int side) {
  cya::point farthest;

  if (farthest_point(l, side, farthest)) {
    quickHull(cya::line(l.first, farthest), -find_side(cya::line(l.first, farthest), l.second));

    quickHull(cya::line(farthest, l.second), -find_side(cya::line(farthest, l.second), l.first));
  }
  else {
    hull_.push_back(l.first);
    hull_.push_back(l.second);

    // aquí agrego las aristas al vector de aristas para el archivo .dot de graphviz
    lines_.push_back(l);
  }
}

/**
 * @brief: función que calcula el punto más lejano de una linea
 * @param[in] l: linea que contiene los puntos a calcular
 * @param[in] side: lado de la linea
 * @param[out] farthest: punto más lejano
 * @return bool: devuelve true si se ha encontrado un punto más lejano
 */
bool cya::point_set::farthest_point(const cya::line& l, int side, cya::point& farthest) const {
  farthest = cya::point_vector::at(0);

  double max_dist = 0;
  bool found = false;

  for (const cya::point& p : *this) {
    const double dist = distance(l, p);

    if (find_side(l, p) == side && dist > max_dist) {
      farthest = p;
      max_dist = dist;
      found = true;
    }
  }

  return found;
}

/**
 * @brief: función determina si un punto está a la izquierda o a la derecha de una linea
 * @param[in] l: linea
 * @param[in] p: punto
 * @return double: valor que determina si el punto está a la izquierda o a la derecha de la linea, siendo negativo o positivo o 0
 */
double cya::point_set::point_2_line(const cya::line& l, const cya::point& p) const {
  const cya::point& p1 = l.first;
  const cya::point& p2 = l.second;

  return (p.second - p1.second) * (p2.first - p1.first) - (p2.second - p1.second) * (p.first - p1.first);
}

/**
 * @brief: función que calcula la distancia de un punto a una linea
 * @param[in] l: linea
 * @param[in] p: punto
 * @return double: distancia del punto a la linea
 */
double cya::point_set::distance(const cya::line& l, const cya::point& p) const {
  return fabs(point_2_line(l, p));
}

/**
 * @brief: función que calcula los limites en x de un conjunto de puntos
 * @param[out] min_x: punto mínimo en x   modifica los valores
 * @param[out] max_x: punto máximo en x   modifica los valores
 * @return void
 */
void cya::point_set::x_bounds(point& min_x, point& max_x) const {
  if (this->empty()) {    // Si el conjunto de puntos está vacío se establecen ambos valores como el origen
    min_x = {0, 0};
    max_x = {0, 0};
  }
  else {
    min_x = this->at(0);  // se establecen los valores iniciales como el punto del indice 0 del vector
    max_x = this->at(0);
    for (const cya::point& p : *this) {     // recorremos todo el vector del objeto invocante
      if (p.first < min_x.first) {          // si el valor del bucle es menor que el minimo actual se actualiza minimo actual
        min_x = p;
      }
      if (p.first > max_x.first) {          // si el valor del bucle es mayor que el maximo actual se actualiza maximo actual
        max_x = p;
      }
    }
  }
}

/**
 * @brief: función que determina si un punto está a la izquierda, a la derecha o en el centro de una linea
 * @param[in] l: linea
 * @param[in] p: punto
 * @return int: devuelve un valor que determina si el punto está a la izquierda, a la derecha o en el centro de la linea
 */
int cya::point_set::find_side(const line& l, const point& p) const {
  const double valor = point_2_line(l, p);
  if (valor < 0) {
    return side::LEFT;
  }
  else if (valor > 0) {
    return side::RIGHT;
  }
  else {
    return side::CENTER;
  }
}

/**
 * @brief: función que imprime los puntos de la envolvente convexa
 * @param[in] os: flujo de salida
 * @return void
 */
void cya::point_set::write_hull(std::ostream& os) const {
  os << "Puntos de la envolvente convexa:" << std::endl;
  for (const cya::point& p : hull_) {
    os << "(" << std::fixed << std::setprecision(3) << p.first << ", " << p.second << ")" << std::endl;
  }
}

/**
 * @brief: función que imprime los puntos y las aristas de la envolvente convexa en formato .dot
 * @param[in] os: flujo de salida
 * @return void
 */
void cya::point_set::write_dot(std::ostream& os) const {
  os << "graph {" << std::endl << std::endl;
  std::vector<cya::point> puntos = *this;
  int contador{0};
  for (const cya::point& punto : puntos) {
    os << " " << contador << " [pos = \" "<< punto.first << ", " << punto.second << "!\"]" << std::endl;
    ++contador;
  }
  os << std::endl;
  for (int i{0}; i < static_cast<int>(lines_.size()); ++i) {      // recorremos todo el vector de lineas, que contiene las aristas correctas de la envoltura convexa
    cya::point point = lines_[static_cast<size_t>(i)].first;      // creamos el primer punto point de la arista
    // creamos el segundo punto point2 de la arista, todo esto para comparar con el vector que hemos usado para almacenar los puntos e imprimirlos justo en el bucle anterior
    cya::point point2 = lines_[static_cast<size_t>(i)].second;    
    for (int j{0}; j < static_cast<int>(puntos.size()); ++j) {    // ahora recorremos el vector de puntos
      // si el pnto de la arista es igual al punto que estamos en el vector, reusamos la variable contador, y la ponemos con valor j (indice del bucle actual de puntos)
      if (point == puntos[static_cast<size_t>(j)]) {              
        contador = j;
        // volvemos a recorrer el vector de puntos y comparar ahora el punto2 de la arista con los puntos totales del vector
        for (int k{0}; k < static_cast<int>(puntos.size()); ++k) {
          // si son iguales, usamos los indices contador y k (indice actual) para imprimir la arista en el formato esperado (ya que se han impreso siguiendo este mismo indice en el bucle inicial)
          if (point2 == puntos[static_cast<size_t>(k)]) {
            os << " " << contador << " -- " << k << std::endl;
          }
        }
      }
    }
  }
  os << "}" << std::endl;
}