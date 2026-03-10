// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: carnivore_ant.cc
// Contenido: implementación de la clase carnivore_ant

#include "carnivore_ant.h"

CarnivoreAnt::CarnivoreAnt(int x, int y, int direction, int ttl)
  : Ant(x, y, direction, ttl), ants_(nullptr) {}

void CarnivoreAnt::SetAnts(std::vector<Ant*>* ants) {
  ants_ = ants;
}

void CarnivoreAnt::Step(Tape& tape) {
  if (!IsAlive()) {
    return;
  }

  DecreaseTTL();
  if (!IsAlive()) {
    return;
  }

  if (ants_ != nullptr) {
    for (Ant* other : *ants_) {
      if (other == this) {
        continue;
      }

      if (other->IsAlive() &&
          other->GetX() == x_ &&
          other->GetY() == y_) {
        other->Kill();
      }
    }
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