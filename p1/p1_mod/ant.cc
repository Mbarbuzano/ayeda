// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: la hormiga de Langton
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/2/2026
// Archivo: ant.cc
// Contenido: implementación de la clase ant

#include "ant.h"

void Ant::step(Tape& tape) {
  auto& grid = tape.tablero();

  bool negra = grid[y_][x_];

  // Girar
  if (!negra) { // blanca -> izquierda (arriba)
    switch (dir_) {
      case UP_RIGHT:  dir_ = UP_LEFT;    break;
      case UP_LEFT:   dir_ = DOWN_LEFT;  break;
      case DOWN_LEFT: dir_ = DOWN_RIGHT; break;
      case DOWN_RIGHT:dir_ = UP_RIGHT;   break;
    }
  } else { // negra -> derecha (abajo)
    switch (dir_) {
      case UP_RIGHT:  dir_ = DOWN_RIGHT; break;
      case DOWN_RIGHT:dir_ = DOWN_LEFT;  break;
      case DOWN_LEFT: dir_ = UP_LEFT;    break;
      case UP_LEFT:   dir_ = UP_RIGHT;   break;
    }
  }

  // Cambiar color
  grid[y_][x_] = !grid[y_][x_];

  // Avanzar en diagonal
  switch (dir_) {
    case UP_RIGHT:   --y_; ++x_; break;
    case DOWN_RIGHT: ++y_; ++x_; break;
    case DOWN_LEFT:  ++y_; --x_; break;
    case UP_LEFT:    --y_; --x_; break;
  }
}


std::ostream& operator<<(std::ostream& os, const Ant& ant) {
  switch (ant.dir()) {
    case UP_RIGHT:   os << '^'; break;
    case DOWN_RIGHT: os << '>'; break;
    case DOWN_LEFT:  os << 'v'; break;
    case UP_LEFT:    os << '<'; break;
  }
  return os;
}
