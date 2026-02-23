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

Simulator::Simulator(const std::string& filename) {
  std::ifstream file(filename);

  int width, height, num_colors;
  file >> width >> height >> num_colors;

  tape_ = Tape(width, height, num_colors);

  // Leer línea de hormigas
  // Crear RuleAnt y hacer push_back en ants_

  // Leer posiciones de celdas iniciales
}