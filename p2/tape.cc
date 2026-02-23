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

std::ostream& operator<<(std::ostream& os, const Tape& cinta) {
  for (int y{0}; y < cinta.size_y(); ++y) {
    for (int x{0}; x < cinta.size_x(); ++x) {
      os << (cinta.tablero()[x][y] ? "■" : "□");
    }
    os << "\n";
  }
  return os;
}