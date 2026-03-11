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
// Contenido: implementación de CarnivoreAnt

#include "carnivore_ant.h"

CarnivoreAnt::CarnivoreAnt(int x, int y, int direction, int ttl,
                           const std::string& gale_rule, int voracity)
  : Ant(x, y, direction, ttl),
    gale_rule_(gale_rule),
    voracity_(voracity),
    ants_(nullptr) {}

std::string CarnivoreAnt::GetType() const {
  return "C-" + gale_rule_;
}

void CarnivoreAnt::SetAnts(std::vector<Ant*>* ants) {
  ants_ = ants;
}

void CarnivoreAnt::EatAnts() {
  if (ants_ == nullptr) return;

  for (Ant* other : *ants_) {
    if (other == this) continue;
    if (!other->IsAlive()) continue;

    if (other->GetX() == x_ && other->GetY() == y_) {
      // Roba Voracity% del TTL de la víctima (mínimo 1)
      int stolen = (other->GetTTL() * voracity_) / 100;
      if (stolen < 1) stolen = 1;

      other->ReduceTTL(stolen);  // puede matar a la víctima si llega a 0
      IncreaseTTL(stolen);       // la carnívora gana ese TTL
    }
  }
}

void CarnivoreAnt::Step(Tape& tape) {
  if (!IsAlive()) return;

  // 1. Decrementar TTL
  DecreaseTTL();
  if (!IsAlive()) return;

  // 2. Comer hormigas que coincidan en la celda actual
  EatAnts();
  if (!IsAlive()) return;

  int color = tape.GetCell(x_, y_);

  // 3. Girar según la regla de Gale para este color
  if (color < static_cast<int>(gale_rule_.size())) {
    if (gale_rule_[color] == 'D') {
      direction_ = (direction_ + 1) % 4;
    } else {
      direction_ = (direction_ + 3) % 4;
    }
  }

  // 4. Avanzar el color de la celda
  tape.SetCell(x_, y_, (color + 1) % tape.GetColors());

  // 5. Moverse en diagonal
  MoveDiagonal();
}
