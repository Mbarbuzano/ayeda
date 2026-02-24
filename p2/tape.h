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

#include "ant.h"

class Tape {
public:

  Tape(int w, int h, int n_colors)
    : width_(w), height_(h), num_colors_(n_colors), grid_(h, std::vector<int>(w, 0)) {}

  void print(const std::vector<Ant*>& ants) const;
  int width() const { return  width_; }
  int height() const { return height_; }



  int getColor(int x, int y) const {
    return grid_[y][x];
  }

  void setColor(int x, int y, int color) {
    grid_[y][x] = color % num_colors_; // ciclico
  }

  void print() const;

private:
  int width_;
  int height_;
  int num_colors_;
  std::vector<std::vector<int>> grid_;
};

#endif