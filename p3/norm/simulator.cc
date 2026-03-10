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
#include <iostream>
#include <fstream>

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
