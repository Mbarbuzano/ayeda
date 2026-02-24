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

#include <vector>
#include <iostream>

class Tape {
public:
  Tape(int width, int height, int num_colors);

  int getColor(int x, int y) const;
  void setColor(int x, int y, int color);

  void print() const;

private:
  int width_;
  int height_;
  int num_colors_;
  std::vector<std::vector<int>> grid_;
};

#endif