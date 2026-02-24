// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 2: Hormiga de Langton Generalizada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/2/2026
// Archivo: simulator.h
// Contenido: declaración de la clase simulator

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <memory>
#include "ruleant.h"

class Simulator {
public:
  Simulator(const std::string& filename);
  void run(int steps);

private:
  Tape tape_;
  std::vector<std::unique_ptr<Ant>> ants_;
};

#endif