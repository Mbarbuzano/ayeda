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
// Contenido: programa principal
//
// Formato del fichero de entrada:
//   Línea 1: ancho alto num_colores
//   Línea 2: tipo_frontera  (periodic | reflective | sliding)
//   Línea 3: TIPO x y orientacion [voracity] ; TIPO x y orientacion [voracity] ; ...
//            TIPO: H-<regla> para herbívora, C-<regla> para carnívora
//            orientacion: < > ^ v
//            voracity: entero 0-100, solo para carnívoras (por defecto 100)
//   Línea 4+: x y color   (celdas no blancas, opcionales)
//
// Ejemplo:
//   7 10 4
//   periodic
//   H-DDII 3 3 > ; C-IDID 5 7 v 50
//   3 4 1
//   3 5 2

#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <iostream>

#include "simulator.h"
#include "tape_periodic.h"
#include "tape_reflective.h"
#include "tape_sliding.h"
#include "herbivore_ant.h"
#include "carnivore_ant.h"

// Convierte el carácter de orientación del guión a entero interno
// ^ = 0 (arriba), > = 1 (derecha), v = 2 (abajo), < = 3 (izquierda)
int ParseDirection(char c) {
  switch (c) {
    case '^': return 0;
    case '>': return 1;
    case 'v': return 2;
    case '<': return 3;
    default:  return 0;
  }
}

// Parsea la línea de hormigas, que tiene el formato:
//   H-DDII 3 3 > ; C-IDID 5 7 v 50 ; ...
// y añade cada hormiga al simulador
void ParseAnts(const std::string& line, Simulator& sim, int default_ttl) {
  std::istringstream ss(line);
  std::string token;
  std::string current;

  // Dividimos por ';'
  while (std::getline(ss, current, ';')) {
    std::istringstream ant_ss(current);
    std::string type;
    int x, y;
    char orientation;

    if (!(ant_ss >> type >> x >> y >> orientation)) continue;

    int dir = ParseDirection(orientation);

    if (type.size() > 2 && type.substr(0, 2) == "H-") {
      std::string rule = type.substr(2);  // quita el "H-"
      // TTL opcional en el fichero, si no se pone usamos default_ttl
      int ttl = default_ttl;
      ant_ss >> ttl;
      sim.AddAnt(new HerbivoreAnt(x, y, dir, ttl, rule));

    } else if (type.size() > 2 && type.substr(0, 2) == "C-") {
      std::string rule = type.substr(2);  // quita el "C-"
      int ttl = default_ttl;
      int voracity = 100;  // por defecto voracidad máxima
      ant_ss >> ttl >> voracity;
      sim.AddAnt(new CarnivoreAnt(x, y, dir, ttl, rule, voracity));
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Uso: " << argv[0] << " <fichero_entrada>\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input) {
    std::cerr << "Error: no se puede abrir " << argv[1] << "\n";
    return 1;
  }

  // Línea 1: dimensiones y colores
  int width, height, colors;
  input >> width >> height >> colors;
  input.ignore();  // consume el '\n' restante

  // Línea 2: tipo de frontera
  std::string tape_type;
  std::getline(input, tape_type);

  std::unique_ptr<Tape> tape;
  if (tape_type == "periodic") {
    tape = std::make_unique<TapePeriodic>(width, height, colors);
  } else if (tape_type == "reflective") {
    tape = std::make_unique<TapeReflective>(width, height, colors);
  } else {
    tape = std::make_unique<TapeSliding>(width, height, colors);
  }

  Simulator sim(std::move(tape));

  // Línea 3: hormigas separadas por ';'
  std::string ant_line;
  std::getline(input, ant_line);
  // TTL por defecto si no se especifica en el fichero
  const int kDefaultTTL = 100;
  ParseAnts(ant_line, sim, kDefaultTTL);

  // Líneas 4+: celdas no blancas (x y color)
  int cx, cy, cc;
  while (input >> cx >> cy >> cc) {
    sim.SetCell(cx, cy, cc);
  }

  sim.Run();

  return 0;
}
