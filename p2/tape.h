// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Práctica 1: la hormiga de Langton
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/2/2026
// Archivo: tape.h
// Contenido: declaración de la clase tape, que dicta las celdas
//            sobre las que se mueve la hormiga

#ifndef TAPE_H_
#define TAPE_H_

#include <iostream>
#include <vector>

class Tape {
 public:
  Tape(const int& size_x,const int& size_y) : size_x_{size_x}, size_y_{size_y}, 
                                              tablero_(size_x, std::vector<bool>(size_x, false)) {}

  int size_x() const { return size_x_; }
  int size_y() const { return size_y_; }
  std::vector<std::vector<bool>>& tablero() { return tablero_; }
  const std::vector<std::vector<bool>>& tablero() const { return tablero_; }

 private:
  int size_x_;
  int size_y_;
  std::vector<std::vector<int>> tablero_;
  int num_colors_;
};

std::ostream& operator<<(std::ostream& os, const Tape& cinta);

#endif