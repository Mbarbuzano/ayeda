// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: tape_reflective.cc

#include "tape_reflective.h"

TapeReflective::TapeReflective(int size_x, int size_y, int colors)
    : Tape(size_x, size_y, colors),
      grid_(size_y, std::vector<Cell>(size_x)) {}

int TapeReflective::ReflectX(int& x, int& dir) const {
  if (x < 0) { x = 0; dir = 1; }
  else if (x >= size_x_) { x = size_x_ - 1; dir = 3; }
  return x;
}

int TapeReflective::ReflectY(int& y, int& dir) const {
  if (y < 0) { y = 0; dir = 2; }
  else if (y >= size_y_) { y = size_y_ - 1; dir = 0; }
  return y;
}

int TapeReflective::GetCell(int x, int y) const {
  if (x < 0) x = 0;
  if (x >= size_x_) x = size_x_ - 1;
  if (y < 0) y = 0;
  if (y >= size_y_) y = size_y_ - 1;
  return grid_[y][x].color;
}

void TapeReflective::SetCell(int x, int y, int color) {
  if (x < 0) x = 0;
  if (x >= size_x_) x = size_x_ - 1;
  if (y < 0) y = 0;
  if (y >= size_y_) y = size_y_ - 1;
  grid_[y][x].color = color;
}

void TapeReflective::Print(std::ostream& os, const AntOverlay& overlay) const {
  for (int y = 0; y < size_y_; ++y) {
    for (int x = 0; x < size_x_; ++x) {
      int c = grid_[y][x].color;
      auto key = std::make_pair(x, y);
      if (overlay.count(key)) {
        const AntMark& m = overlay.at(key);
        os << CellColor(c) << m.ansi << m.symbol << "\033[0m";
      } else {
        os << CellColor(c) << ' ' << "\033[0m";
      }
    }
    os << '\n';
  }
}
