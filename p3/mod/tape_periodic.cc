// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: tape_periodic.cc

#include "tape_periodic.h"

TapePeriodic::TapePeriodic(int size_x, int size_y, int colors)
    : Tape(size_x, size_y, colors),
      grid_(size_y, std::vector<Cell>(size_x)) {}

int TapePeriodic::WrapX(int x) const {
  int w = x % size_x_;
  return w < 0 ? w + size_x_ : w;
}

int TapePeriodic::WrapY(int y) const {
  int w = y % size_y_;
  return w < 0 ? w + size_y_ : w;
}

int TapePeriodic::GetCell(int x, int y) const {
  return grid_[WrapY(y)][WrapX(x)].color;
}

void TapePeriodic::SetCell(int x, int y, int color) {
  grid_[WrapY(y)][WrapX(x)].color = color;
}

void TapePeriodic::Print(std::ostream& os, const AntOverlay& overlay) const {
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
