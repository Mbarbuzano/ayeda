// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: la hormiga de Langton
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/2/2026
// Archivo: tape.cc
// Contenido: implementación de la clase tape

#include "tape.h"

Tape::Tape(int width, int height, int num_colors)
  : width_{width}, height_{height}, num_colors_{num_colors},
    grid_(height, std::vector<int>(width, 0)) {}

int Tape::getColor(int x, int y) const {
  return grid_[y][x];
}

void Tape::setColor(int x, int y, int color) {
  grid_[y][x] = color;
}

void Tape::print() const {
  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      std::cout << grid_[y][x];
    }
    std::cout << '\n';
  }
}