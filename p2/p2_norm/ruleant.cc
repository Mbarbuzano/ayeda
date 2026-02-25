// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 2: Hormiga de Langton Generalizada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/2/2026
// Archivo: ruleant.cc
// Contenido: implementación de la clase ruleant 

#include "ruleant.h"

RuleAnt::RuleAnt(int x, int y, Direccion dir, const std::string& rule)
  : Ant(x, y, dir), rule_{rule} {}

void RuleAnt::step(Tape& tape) {
  int color = tape.getColor(x_, y_);

  char giro = rule_[color];

  if (giro == 'D')
    turnRight();
  else
    turnLeft();

  tape.setColor(x_, y_, (color + 1) % rule_.size());

  moveForward(tape.width(), tape.height());
}