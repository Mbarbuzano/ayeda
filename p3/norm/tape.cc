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

#include "tape.h"

Tape::Tape(int size_x, int size_y, int colors)
    : size_x_(size_x), size_y_(size_y), colors_(colors) {}

void Tape::NextColor(int x, int y) {
  SetCell(x, y, (GetCell(x, y) + 1) % colors_);
}

// Tabla centralizada de colores ANSI para celdas
// color 0 = fondo oscuro (celda vacía), resto colores vivos
const char* Tape::CellColor(int c) {
  static const char* table[] = {
    "\033[40m",   // 0 fondo negro
    "\033[41m",   // 1 fondo rojo
    "\033[42m",   // 2 fondo verde
    "\033[44m",   // 3 fondo azul
    "\033[43m",   // 4 fondo amarillo
    "\033[45m",   // 5 fondo magenta
    "\033[46m",   // 6 fondo cyan
    "\033[100m",  // 7 fondo gris oscuro
  };
  if (c >= 0 && c < 8) return table[c];
  return table[0];
}

std::ostream& operator<<(std::ostream& os, const Tape& tape) {
  tape.Print(os);
  return os;
}
