#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>  

#include "simulator.h"


/**
 * @brief Constructor de la clase Simulator. Se encarga de leer el fichero de entrada, inicializar la rejilla y la hormiga, y establecer el estado inicial de la simulación.
 * @param fichero_entrada Nombre del fichero de entrada que contiene la configuración inicial de la simulación.
 * @param control Referencia a un booleano que se establece a true si la inicialización es exitosa, o a false si ocurre algún error durante la lectura del fichero o la configuración
 * @param tipo_cinta Tipo de cinta para la simulación
 */
Simulator::Simulator(const std::string& fichero_entrada, bool& control, int tipo_cinta) {
  switch(tipo_cinta) {
    case 1:
      rejilla_ = new TapePeriodic();
      break;
    case 2:
      rejilla_ = new TapeReflective();
      break;
    case 3:
      rejilla_ = new TapeSliding();
      break;
    default:
      rejilla_ = new TapePeriodic();
      break;
  }
  std::ifstream flujo_entrada{fichero_entrada};
  if (!flujo_entrada.is_open()) {
    std::cerr << "No se ha podido abrir el fichero de entrada.\n";
    control = false;
    return;
  }
  // capturamos el tamaño de la rejilla
  int sizeX, sizeY;
  flujo_entrada >> sizeX >> sizeY;
  int num_colores;
  flujo_entrada >> num_colores;
  std::string hormigas_linea;
  std::getline(flujo_entrada, hormigas_linea);  // ahora estaria vacia porque quedó el retorno de carro
  std::getline(flujo_entrada, hormigas_linea);  // almacenamos la linea de las hormigas
  std::stringstream flujo_hormigas{hormigas_linea};

  // vector de colores ANSI para asignar a cada hormiga
  std::vector<std::string> coloresANSI = {
    "\033[31m", // rojo
    "\033[32m", // verde
    "\033[33m", // amarillo
    "\033[34m", // azul
    "\033[35m"  // magenta
  };
  int idx_color{0};
  int contador_hormigas{0};
  std::string hormiga_ind;
  while (std::getline(flujo_hormigas, hormiga_ind, ';')) {
    if (hormiga_ind.empty()) continue;
    std::stringstream flujo_individual{hormiga_ind};
    std::string reglas;
    int pos_x, pos_y, orientacion, lifetime;
    double voracity;
    if (!(flujo_individual >> reglas)) {
      std::cerr << "Error: formato incorrecto en la línea de las hormigas (reglas).\n";
      control = false;
      ClearAnts();
      return;
    }
    char tipo = reglas[0];
    if (tipo != 'H' && tipo != 'C') {
      std::cerr << "Error: tipo de hormiga desconocido (" << tipo << ").\n";
      control = false;
      ClearAnts();
      return;
    }
    reglas.erase(0, 2);
    if (tipo == 'C') {
      if (!(flujo_individual >> pos_x >> pos_y >> orientacion >> lifetime >> voracity)) {
        std::cerr << "Error: formato incorrecto en la línea de las hormigas (hormiga carnívora).\n";
        control = false;
        ClearAnts();
        return;
      }
      
    }
    else {
      if (!(flujo_individual >> pos_x >> pos_y >> orientacion >> lifetime)) {
        std::cerr << "Error: formato incorrecto en la línea de las hormigas (hormiga herbívora).\n";
        control = false;
        ClearAnts();
        return;
      }
    }
    if (pos_x < 0 || pos_x >= sizeX || pos_y < 0 || pos_y >= sizeY) {
      std::cerr << "Error: posición de la hormiga fuera de los límites de la rejilla.\n";
      std::cerr << "Posición de la hormiga: (" << pos_x << ", " << pos_y << ")\n";
      control = false;
      ClearAnts();
      return;
    }
    if (idx_color >= static_cast<int>(coloresANSI.size())) idx_color = 0;
    if (tipo == 'H') {
      Ant* hormiga = new AntHerb(reglas, coloresANSI[idx_color], lifetime);
      hormiga->SetPlace(pos_x, pos_y, orientacion);
      hormigas_.push_back(hormiga);
    }
    else if (tipo == 'C') {
      Ant* hormiga = new AntCarn(reglas, coloresANSI[idx_color], lifetime, voracity);
      hormiga->SetPlace(pos_x, pos_y, orientacion);
      hormigas_.push_back(hormiga);
    }
     else {
      std::cerr << "Error: tipo de hormiga desconocido (" << tipo << ").\n";
      control = false;
      ClearAnts();
      return;
    }
    ++idx_color;
    ++contador_hormigas;
  }

  rejilla_->SetSize(sizeX, sizeY);
  rejilla_->SetColores(num_colores);
  std::string linea;
  while (std::getline(flujo_entrada, linea)) {
    // cada linea es una posición de la rejilla que pasa de blanco (0) por defecto a negro(1)
    if (linea.empty()) continue;
    int x, y, color;
    std::stringstream flujo_linea{linea};
    flujo_linea >> x >> y >> color;    
    rejilla_->FlipColor(x, y, color);
  }
  control = true;
}

/**
 * @brief Destructor de la clase Simulator. Se encarga de liberar la memoria asignada a las hormigas.
 */
Simulator::~Simulator() {
  ClearAnts();
  if (rejilla_ != nullptr) delete rejilla_;
}


/**
 * @brief Ejecuta la simulación de Langton según la opción seleccionada.
 * @param opcion Opción de simulación (1 para paso a paso, otro valor para ejecución continua).
 * @return void
 */
void Simulator::Simulate(const int& opcion) {
  std::cout << "Presione enter para avanzar, cualquier otra tecla + enter para finalizar";  
  std::string input;
  bool paso_valido{true};
  int contador{0};
  while(paso_valido) {
    if (opcion == 1) {
      getline(std::cin, input);
      if (!input.empty()) break;
      else {
        paso_valido = Step(contador);
      }
    }
    else {
      paso_valido = Step(contador);
    }
  }
  std::cout << "finalizando simulación..." << std::endl;
}

/**
 * @brief Ejecuta un paso de la simulación, moviendo la hormiga y actualizando la rejilla.
 * @param contador Referencia a un contador que se incrementa en cada paso para llevar el seguimiento del número de pasos realizados.
 * @return true si el paso es válido (dentro de los límites de la rejilla), false si la hormiga se sale de la rejilla.
 */
bool Simulator::Step(int& contador) {
  // se mueven todas las hormigas, si alguna se sale de la rejilla, se finaliza la simulación
  for (int i{0}; i < static_cast<int>(hormigas_.size()); ++i) {
    if (hormigas_[i]->GetLifeTime() == 0 && !hormigas_[i]->IsDead()) {
      ++dead_ants_;
      hormigas_[i]->Kill();
      continue;
    }
    if (!hormigas_[i]->IsDead()) hormigas_[i]->Move(*rejilla_);
  }
  if (hormigas_.size() == dead_ants_) {
    std::cout << "Todas las hormigas han muerto. Finalizando simulación..." << std::endl;
    return false;
  }
  // aquí realizamos la actualización del lifetime.
  std::map<std::pair<int,int>, std::vector<Ant*>> posiciones_hormigas;  // mapa que asocia cada posición con las hormigas en la posicion
  for (int i{0}; i < static_cast<int>(hormigas_.size()); ++i) {
    std::pair<int,int> pos = hormigas_[i]->GetPosition();
    posiciones_hormigas[pos].push_back(hormigas_[i]);
  }
  for (const std::pair<const std::pair<int,int>, std::vector<Ant*>>& entry : posiciones_hormigas) {
    const std::vector<Ant*>& hormigas_en_posicion = entry.second;
    if (hormigas_en_posicion.size() > 1) {
      // hay más de una hormiga en la misma posición, se comen entre ellas
      for (int i{0}; i < static_cast<int>(hormigas_en_posicion.size()); ++i) {
        // roba vida a todas las demas menos a las carnivoras, a si misma, y las muertas
        Ant* hormiga = hormigas_en_posicion[i];
        for (int j{0}; j < static_cast<int>(hormigas_en_posicion.size()); ++j) {
          if (i == j) continue;
          Ant* otra_hormiga = hormigas_en_posicion[j];
          if (hormiga->IsCarnivorous() && !otra_hormiga->IsCarnivorous() && otra_hormiga->GetLifeTime() > 0) {
            unsigned int vida_robada = static_cast<unsigned int>(otra_hormiga->GetLifeTime() * hormiga->GetVoracity());
            hormiga->GainLife(vida_robada);
            otra_hormiga->LoseLife(vida_robada);
          }
        }
      }
    }
  }

  system("clear");
  // imprimimos indices de columnas:
  const int min_x = rejilla_->Minx();
  const int max_x = rejilla_->Maxx();
  const int min_y = rejilla_->Miny();
  const int max_y = rejilla_->Maxy();
  std::cout << "    ";
  for (int i{min_y}; i <= max_y; ++i) {
    std::cout << i % 10 << " ";
  }
  std::cout << std::endl;
  for (int i{min_x}; i <= max_x; ++i) {
    std::cout << i % 10 << " | ";
    for (int j{min_y}; j <= max_y; ++j) {
      for (int k{0}; k < static_cast<int>(hormigas_.size()); ++k) {
        if (hormigas_[k]->GetPosition() == std::pair(i,j) && hormigas_[k]->GetLifeTime() > 0) {
          std::cout << hormigas_[k]->GetColorANSI() << *hormigas_[k] << "\033[0m ";
          break;
        }
        else if (hormigas_[k]->GetPosition() == std::pair(i,j) && hormigas_[k]->GetLifeTime() == 0) {
          // si la hormiga está muerta, la representamos con una X
          std::cout << "\033[31mX\033[0m ";  // X roja para hormiga muerta
          break;
        }
        else if (k == static_cast<int>(hormigas_.size()) - 1) {
          switch(rejilla_->GetColor(i, j)) {
            case Colores::c0:
              std::cout << "□ ";
              break;
            case Colores::c1:
              std::cout << "\033[34m■\033[0m ";  // azul oscuro
              break;
            case Colores::c2:
              std::cout << "\033[32m■\033[0m ";  // verde oscuro
              break;
            case Colores::c3:
              std::cout << "\033[31m■\033[0m ";  // rojo oscuro
              break;
            case Colores::c4:
              std::cout << "\033[33m■\033[0m ";  // amarillo oscuro
              break;
          }
        }
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << "Paso " << contador << std::endl;
  for (int i{0}; i < static_cast<int>(hormigas_.size()); ++i) {
    std::cout << "Hormiga: " << ColorHormiga(*hormigas_[i]) 
              << " Posición: (" << hormigas_[i]->GetPosition().first << ", " << hormigas_[i]->GetPosition().second << ")"
              << " Vida: " << hormigas_[i]->GetLifeTime() << std::endl;
  }
  ++contador;
  return true;
}

/**
 * @brief Sobrecarga del operador de salida para imprimir el estado actual del simulador, incluyendo la rejilla y la posición de las hormigas.
 * @param os Flujo de salida.
 * @param simulator Objeto Simulator que se desea imprimir.
 * @return Referencia al flujo de salida.
 */
std::ostream& operator<<(std::ostream& os, const Simulator& simulator) {
  os << "    ";
  for (int i{0}; i < simulator.rejilla_->GetSize().second; ++i) {
    os << i % 10 << " ";
  }
  os << std::endl;
  for (int i = 0; i < simulator.rejilla_->GetSize().first; ++i) {
    os << i % 10 << " | ";
    for (int j = 0; j < simulator.rejilla_->GetSize().second; ++j) {
      for (int k{0}; k < static_cast<int>(simulator.hormigas_.size()); ++k) {
        if (simulator.hormigas_[k]->GetPosition() == std::pair(i,j)) {
          os << simulator.hormigas_[k]->GetColorANSI() << *simulator.hormigas_[k] << "\033[0m ";
          break;
        }
        else if (k == static_cast<int>(simulator.hormigas_.size()) - 1) {
          switch(simulator.rejilla_->GetColor(i, j)) {
            case Colores::c0:
              os << "□ ";
              break;
            case Colores::c1:
              os << "\033[34m■\033[0m ";  // azul oscuro
              break;
            case Colores::c2:
              os << "\033[32m■\033[0m ";  // verde oscuro
              break;
            case Colores::c3:
              os << "\033[31m■\033[0m ";  // rojo oscuro
              break;
            case Colores::c4:
              os << "\033[33m■\033[0m ";  // amarillo oscuro
              break;
          }
        }
      }
    }
    os << std::endl;  
  }
  for (int i{0}; i < static_cast<int>(simulator.hormigas_.size()); ++i) {
    os << "Hormiga: " << simulator.ColorHormiga(*simulator.hormigas_[i]) 
       << " Posición: (" << simulator.hormigas_[i]->GetPosition().first << ", " << simulator.hormigas_[i]->GetPosition().second << ")"
       << " Vida: " << simulator.hormigas_[i]->GetLifeTime() << std::endl;
  }
  return os;
}

std::string Simulator::ColorHormiga(const Ant& hormiga) const {
  std::string color;
  if (hormiga.GetColorANSI() == "\033[31m") color = "rojo";
  else if (hormiga.GetColorANSI() == "\033[32m") color = "verde";
  else if (hormiga.GetColorANSI() == "\033[33m") color = "amarillo";
  else if (hormiga.GetColorANSI() == "\033[34m") color = "azul";
  else if (hormiga.GetColorANSI() == "\033[35m") color = "magenta";
  return color;
}

/**
 * @brief Libera la memoria asignada a las hormigas y limpia el vector de hormigas.
 */
void Simulator::ClearAnts() {
  for (Ant* a : hormigas_) delete a;
  hormigas_.clear();
}