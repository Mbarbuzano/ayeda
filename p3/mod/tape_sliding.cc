// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: tape_sliding.cc

#include "tape_sliding.h"

TapeSliding::TapeSliding(int size_x, int size_y, int colors)
    : Tape(size_x, size_y, colors), grid_(0, size_y - 1) {
  for (int y = 0; y < size_y; ++y)
    grid_[y] = SlidingVector<Cell>(0, size_x - 1);
}

void TapeSliding::ExpandX(int x) {
  while (x < grid_[grid_.IndexMin()].IndexMin())
    for (int y = grid_.IndexMin(); y <= grid_.IndexMax(); ++y)
      grid_[y].PushFront(Cell(0));
  while (x > grid_[grid_.IndexMin()].IndexMax())
    for (int y = grid_.IndexMin(); y <= grid_.IndexMax(); ++y)
      grid_[y].PushBack(Cell(0));
}

void TapeSliding::ExpandY(int y) {
  int x_min = grid_[grid_.IndexMin()].IndexMin();
  int x_max = grid_[grid_.IndexMin()].IndexMax();
  while (y < grid_.IndexMin())
    grid_.PushFront(SlidingVector<Cell>(x_min, x_max));
  while (y > grid_.IndexMax())
    grid_.PushBack(SlidingVector<Cell>(x_min, x_max));
}

int TapeSliding::GetCell(int x, int y) const {
  if (y < grid_.IndexMin() || y > grid_.IndexMax()) return 0;
  const SlidingVector<Cell>& row = grid_[y];
  if (x < row.IndexMin() || x > row.IndexMax()) return 0;
  return row[x].color;
}

void TapeSliding::SetCell(int x, int y, int color) {
  ExpandY(y);
  ExpandX(x);
  grid_[y][x].color = color;
}

void TapeSliding::Print(std::ostream& os, const AntOverlay& overlay) const {
  for (int y = grid_.IndexMin(); y <= grid_.IndexMax(); ++y) {
    const SlidingVector<Cell>& row = grid_[y];
    for (int x = row.IndexMin(); x <= row.IndexMax(); ++x) {
      int c = row[x].color;
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
