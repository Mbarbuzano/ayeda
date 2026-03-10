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
// Contenido: implementación de HerbivoreAnt

#include "herbivore_ant.h"

HerbivoreAnt::HerbivoreAnt(int x, int y, int direction, int ttl,
                           const std::string& gale_rule)
  : Ant(x, y, direction, ttl), gale_rule_(gale_rule) {}

std::string HerbivoreAnt::GetType() const {
  return "H-" + gale_rule_;
}

void HerbivoreAnt::Step(Tape& tape) {
  if (!IsAlive()) return;

  // 1. Decrementar TTL (muere si llega a 0)
  DecreaseTTL();
  if (!IsAlive()) return;

  int color = tape.GetCell(x_, y_);

  // 2. Incrementar TTL con el valor del color de la celda actual
  //    (la herbívora "se alimenta" del color)
  if (color > 0) {
    IncreaseTTL(color);
  }

  // 3. Girar según la regla de Gale para este color
  //    D = derecha (+1 mod 4), I = izquierda (+3 mod 4)
  if (color < static_cast<int>(gale_rule_.size())) {
    if (gale_rule_[color] == 'D') {
      direction_ = (direction_ + 1) % 4;
    } else {
      direction_ = (direction_ + 3) % 4;
    }
  }

  // 4. Avanzar el color de la celda de forma cíclica
  tape.SetCell(x_, y_, (color + 1) % tape.GetColors());

  // 5. Moverse ortogonalmente
  MoveForward();
}
