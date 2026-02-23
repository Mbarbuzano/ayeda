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

#include "ruleant.h"

class Simulator {
 public:
   Simulator(int size_x, int size_y, Ant ant)
      : tablero_(size_x, size_y), hormiga_(ant), pasos_(0), running_(true) {}

  void run();
  bool out_of_bounds() const;
  void render() const;

 private:
  Tape tablero_;
  Ant hormiga_;
  int pasos_;
  bool running_;
};

#endif