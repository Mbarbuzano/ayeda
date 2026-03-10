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
// Contenido: implementación de la clase tape_reflective

#include "tape_reflective.h"

TapeReflective::TapeReflective(int size_x, int size_y, int colors)
    : Tape(size_x, size_y, colors), grid_(size_y, std::vector<Cell>(size_x)) {}

int TapeReflective::ReflectX(int& x, int& dir) const {
  if (x < 0) {
    x = 0;
    dir = 1; // rebote hacia derecha
  } else if (x >= size_x_) {
    x = size_x_ - 1;
    dir = 0; // rebote hacia izquierda
  }
  return x;
}

int TapeReflective::ReflectY(int& y, int& dir) const {
  if (y < 0) {
    y = 0;
    dir = 3; // rebote hacia abajo
  } else if (y >= size_y_) {
    y = size_y_ - 1;
    dir = 2; // rebote hacia arriba
  }
  return y;
}

int TapeReflective::GetCell(int x, int y) const {
  // para lectura no modificamos dir
  if (x < 0) x = 0;
  if (x >= size_x_) x = size_x_ - 1;
  if (y < 0) y = 0;
  if (y >= size_y_) y = size_y_ - 1;
  return grid_[y][x].color;
}

void TapeReflective::SetCell(int x, int y, int color) {
  // ajustamos para que no salga del rango
  if (x < 0) x = 0;
  if (x >= size_x_) x = size_x_ - 1;
  if (y < 0) y = 0;
  if (y >= size_y_) y = size_y_ - 1;
  grid_[y][x].color = color;
}

void TapeReflective::Print(std::ostream& os) const {
  const char* colors_ansi[] = {
    "\033[37m", // 0 blanco
    "\033[31m", // 1 rojo
    "\033[32m", // 2 verde
    "\033[34m", // 3 azul
    "\033[33m", // 4 amarillo
    "\033[35m", // 5 magenta
    "\033[36m", // 6 cyan
    "\033[90m"  // 7 gris oscuro
  };

  for (int y = 0; y < size_y_; ++y) {
    for (int x = 0; x < size_x_; ++x) {
      int c = grid_[y][x].color;
      char display = (c == 0) ? ' ' : 'X';
      const char* color_code = (c < 8) ? colors_ansi[c] : "\033[37m";
      os << color_code << display << "\033[0m";
    }
    os << '\n';
  }
}