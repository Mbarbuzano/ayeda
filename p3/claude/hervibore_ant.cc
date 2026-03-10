// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: herbivore_ant.cc
// Contenido: implementación de la clase herbivore_ant
// 

#include "herbivore_ant.h"

HerbivoreAnt::HerbivoreAnt(int x, int y, int direction, int ttl)
  : Ant(x, y, direction, ttl) {}

void HerbivoreAnt::Step(Tape& tape) {
  if (!IsAlive()) {
    return;
  }

  DecreaseTTL();
  if (!IsAlive()) {
    return;
  }

  int color = tape.GetCell(x_, y_);

  if (color == 0) {
    direction_ = (direction_ + 1) % 4;
  } else {
    direction_ = (direction_ + 3) % 4;
  }

  tape.SetCell(x_, y_, (color + 1) % tape.GetColors());

  MoveForward();
}