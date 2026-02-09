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
  if (!negra) { // blanca -> izquierda
    switch (dir_) {
      case UP:    dir_ = LEFT;  break;
      case LEFT:  dir_ = DOWN;  break;
      case DOWN:  dir_ = RIGHT; break;
      case RIGHT: dir_ = UP;    break;
    }
  } else { // negra -> derecha
    switch (dir_) {
      case UP:    dir_ = RIGHT; break;
      case RIGHT: dir_ = DOWN;  break;
      case DOWN:  dir_ = LEFT;  break;
      case LEFT:  dir_ = UP;    break;
    }
  }

  // Cambiar color
  grid[y_][x_] = !grid[y_][x_];

  // Avanzar
  switch (dir_) {
    case UP:    --y_; break;
    case DOWN:  ++y_; break;
    case LEFT:  --x_; break;
    case RIGHT: ++x_; break;
  }
}
