// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: tape.cc
// Contenido: implementación de la clase tape

#include "tape.h"

Tape::Tape(int size_x, int size_y, int colors)
    : size_x_(size_x),
      size_y_(size_y),
      colors_(colors) {}

void Tape::NextColor(int x, int y) {
  int color = GetCell(x, y);
  color = (color + 1) % colors_;
  SetCell(x, y, color);
}

std::ostream& operator<<(std::ostream& os, const Tape& tape) {
  tape.Print(os);
  return os;
}