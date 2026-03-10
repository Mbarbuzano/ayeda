// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: simulator.h
// Contenido: declaración de la clase simulator
// simulator es el director de orquesta de todo el código
// y se encarga de seleccionar las clases pertinentes y construir y manejar
// el tablero con las hormigas

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <memory>
#include "ant.h"
#include "tape.h"

class Simulator {
 public:
  Simulator(std::unique_ptr<Tape> tape);

  void AddAnt(Ant* ant);
  void Step();
  void Run(int steps);

  void Print() const;

 private:
  std::unique_ptr<Tape> tape_;
  std::vector<Ant*> ants_;

  void RemoveDeadAnts();
};

#endif