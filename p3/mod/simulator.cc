// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: simulator.cc
// Contenido: implementación de Simulator

#include "simulator.h"
#include "carnivore_ant.h"
#include "herbivore_ant.h"
#include <iostream>
#include <fstream>
#include <map>

Simulator::Simulator(std::unique_ptr<Tape> tape)
  : tape_(std::move(tape)), step_count_(0) {}

Simulator::~Simulator() {
  for (Ant* ant : ants_) delete ant;
}

void Simulator::AddAnt(Ant* ant) {
  ants_.push_back(ant);
}

void Simulator::SetCell(int x, int y, int color) {
  tape_->SetCell(x, y, color);
}

bool Simulator::HasLivingAnts() const {
  for (Ant* ant : ants_) {
    if (ant->IsAlive()) return true;
  }
  return false;
}

void Simulator::Step() {
  // Dar a cada carnívora acceso a la lista completa de hormigas
  for (Ant* ant : ants_) {
    if (auto carnivore = dynamic_cast<CarnivoreAnt*>(ant)) {
      carnivore->SetAnts(&ants_);
    }
  }

  for (Ant* ant : ants_) {
    if (ant->IsAlive()) {
      ant->Step(*tape_);
    }
  }

  step_count_++;
  ReproduceAnts();
  RemoveDeadAnts();
}

// Bucle interactivo: un paso por cada Enter, para cuando no hay hormigas vivas
void Simulator::Run() {
  Print();
  std::string line;
  while (HasLivingAnts()) {
    std::cout << "Pulsa Enter para avanzar (q + Enter para salir)...";
    std::getline(std::cin, line);
    if (line == "q" || line == "Q") break;

    Step();
    Print();
  }

  if (!HasLivingAnts()) {
    std::cout << "Simulación terminada: no quedan hormigas vivas.\n";
  }

  // Preguntar si guardar
  std::cout << "¿Guardar estado en fichero? (s/n): ";
  std::getline(std::cin, line);
  if (line == "s" || line == "S") {
    std::cout << "Nombre del fichero: ";
    std::string filename;
    std::getline(std::cin, filename);
    Save(filename);
    std::cout << "Estado guardado en " << filename << "\n";
  }
}

void Simulator::Print(std::ostream& os) const {
  os << "--- Paso " << step_count_ << " ---\n";

  // Colores ANSI para el texto de cada hormiga (negrita + color de texto)
  static const char* ant_colors[] = {
    "\033[1;97m",  // blanco brillante
    "\033[1;93m",  // amarillo brillante
    "\033[1;96m",  // cyan brillante
    "\033[1;95m",  // magenta brillante
    "\033[1;92m",  // verde brillante
    "\033[1;91m",  // rojo brillante
  };
  static const int num_colors = 6;

  // Dirección -> símbolo de orientación
  auto dir_symbol = [](int dir) -> char {
    switch (dir) {
      case 0: return '^';
      case 1: return '>';
      case 2: return 'v';
      case 3: return '<';
      default: return '?';
    }
  };

  // Construir el overlay: posición -> (símbolo, color ANSI)
  AntOverlay overlay;
  int idx = 0;
  for (Ant* ant : ants_) {
    if (!ant->IsAlive()) continue;
    auto key = std::make_pair(ant->GetX(), ant->GetY());
    overlay[key] = { dir_symbol(ant->GetDirection()),
                     ant_colors[idx % num_colors] };
    idx++;
  }

  tape_->Print(os, overlay);
  PrintAntInfo(os);
  os << "\n";
}

void Simulator::PrintAntInfo(std::ostream& os) const {
  for (Ant* ant : ants_) {
    if (ant->IsAlive()) {
      os << ant->GetType()
         << "  pos=(" << ant->GetX() << "," << ant->GetY() << ")"
         << "  TTL=" << ant->GetTTL() << "\n";
    }
  }
}

void Simulator::Save(const std::string& filename) const {
  std::ofstream out(filename);
  tape_->Print(out);
}

void Simulator::ReproduceAnts() {
  // Agrupa las hormigas vivas por celda
  // clave: (x, y) → lista de hormigas en esa celda
  std::map<std::pair<int,int>, std::vector<Ant*>> by_cell;
  for (Ant* ant : ants_) {
    if (ant->IsAlive()) {
      by_cell[{ant->GetX(), ant->GetY()}].push_back(ant);
    }
  }

  std::vector<Ant*> newborns;

  for (auto& [pos, group] : by_cell) {
    if (group.size() < 2) continue;

    // Separar por tipo (H- o C-)
    // Dos hormigas del mismo tipo en la misma celda → reproducción
    // Si hay más de dos del mismo tipo, solo se genera una nueva
    std::vector<Ant*> herbs, carns;
    for (Ant* ant : group) {
      if (ant->GetType().substr(0, 2) == "H-") herbs.push_back(ant);
      else                                      carns.push_back(ant);
    }

    auto reproduce = [&](std::vector<Ant*>& pair_group) {
      if (pair_group.size() < 2) return;

      Ant* a = pair_group[0];
      Ant* b = pair_group[1];

      // TTL de la nueva: media de las dos progenitoras
      int new_ttl = (a->GetTTL() + b->GetTTL()) / 2;

      // Dirección: opuesta a la media de las dos
      // Suma las direcciones y coge la contraria para que se aleje
      int avg_dir = (a->GetDirection() + b->GetDirection()) / 2;
      int new_dir = (avg_dir + 2) % 4;

      // Hereda la regla de Gale de la primera progenitora
      std::string rule = a->GetType().substr(2);  // quita "H-" o "C-"

      int x = a->GetX();
      int y = a->GetY();

      if (a->GetType().substr(0, 2) == "H-") {
        newborns.push_back(new HerbivoreAnt(x, y, new_dir, new_ttl, rule));
      } else {
        // Carnívora hereda también la voracidad del primer progenitor
        int voracity = dynamic_cast<CarnivoreAnt*>(a)->GetVoracity();
        newborns.push_back(new CarnivoreAnt(x, y, new_dir, new_ttl, rule, voracity));
      }
    };

    reproduce(herbs);
    reproduce(carns);
  }

  // Añadir los recién nacidos a la lista
  for (Ant* ant : newborns) {
    ants_.push_back(ant);
    std::cout << "\n  *** Nace " << ant->GetType()
              << " en (" << ant->GetX() << "," << ant->GetY() << ")"
              << " TTL=" << ant->GetTTL() << " ***\n";
  }
}

void Simulator::RemoveDeadAnts() {
  std::vector<Ant*> alive;
  for (Ant* ant : ants_) {
    if (ant->IsAlive()) {
      alive.push_back(ant);
    } else {
      delete ant;
    }
  }
  ants_ = alive;
}