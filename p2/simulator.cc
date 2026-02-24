// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 2: Hormiga de Langton Generalizada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/2/2026
// Archivo: simulator.cc
// Contenido: implementación de la clase simulator

#include "simulator.h"
#include "ruleant.h"
#include <fstream>
#include <sstream>

Simulator::Simulator(const std::string& filename)
  : tape_(1,1,1) {

  std::ifstream file(filename);

  int width, height, num_colors;
  file >> width >> height >> num_colors;

  tape_ = Tape(width, height, num_colors);

  file.ignore();

  std::string line;
  std::getline(file, line);

  std::stringstream ss(line);
  std::string block;

  while (std::getline(ss, block, ';')) {
    std::stringstream ant_ss(block);

    std::string rule;
    int x, y;
    char dir_char;

    ant_ss >> rule >> x >> y >> dir_char;

    Direccion dir;

    switch (dir_char) {
      case '^': dir = Direccion::UP; break;
      case 'v': dir = Direccion::DOWN; break;
      case '<': dir = Direccion::LEFT; break;
      case '>': dir = Direccion::RIGHT; break;
      default: dir = Direccion::UP;
    }

    ants_.push_back(
      std::make_unique<RuleAnt>(x, y, dir, rule)
    );
  }

  int x, y, color;
  while (file >> x >> y >> color) {
    tape_.setColor(x, y, color);
  }
}

void Simulator::run(int steps) {
  for (int i = 0; i < steps; ++i) {
    for (auto& ant : ants_) {
      ant->step(tape_);
    }
  }

  tape_.print();
}