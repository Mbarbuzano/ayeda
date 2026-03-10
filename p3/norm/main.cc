// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: main.cc
// Contenido: archivo principal de compilación

#include <fstream>
#include <memory>
#include <string>

#include "simulator.h"
#include "tape_periodic.h"
#include "tape_reflective.h"
#include "tape_sliding.h"
#include "herbivore_ant.h"
#include "carnivore_ant.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    return 1;
  }

  std::ifstream input(argv[1]);

  int width, height, colors;
  input >> width >> height >> colors;

  std::string tape_type;
  input >> tape_type;

  int steps;
  input >> steps;

  std::unique_ptr<Tape> tape;

  if (tape_type == "periodic") {
    tape = std::make_unique<TapePeriodic>(width, height, colors);
  } else if (tape_type == "reflective") {
    tape = std::make_unique<TapeReflective>(width, height, colors);
  } else {
    tape = std::make_unique<TapeSliding>(width, height, colors);
  }

  Simulator sim(std::move(tape));

  std::string type;
  while (input >> type) {
    int x, y, dir, ttl;
    input >> x >> y >> dir >> ttl;

    if (type == "herbivore") {
      sim.AddAnt(new HerbivoreAnt(x, y, dir, ttl));
    } else if (type == "carnivore") {
      sim.AddAnt(new CarnivoreAnt(x, y, dir, ttl));
    }
  }

  sim.Run(steps);

  return 0;
}