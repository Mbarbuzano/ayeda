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

Tape::Tape(const std::string& filename) {
  std::ifstream file(filename);
    if (!file) {
      throw std::runtime_error("No se pudo abrir el fichero");
    }

  file >> size_x_ >> size_y_;
  tablero_ = std::vector<std::vector<bool>>(size_y_, std::vector<bool>(size_x_, false));

  int x, y;
  while (file >> x >> y) {
    if (x >= 0 && x < size_x_ && y >= 0 && y < size_y_) {
      tablero_[y][x] = true;
    }
  }
}