// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: la hormiga de Langton
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/2/2026
// Archivo: ant.h
// Contenido: declaración de la clase ant, que describe cómo se comporta
//            la hormiga sobre las celdas

#ifndef ANT_H_
#define ANT_H_

#include "tape.h"

enum Direccion { // Comportamiento modificado para que siga los pasos en diagonal
  UP_RIGHT,
  DOWN_RIGHT,
  DOWN_LEFT,
  UP_LEFT
};


class Ant{
 public:
  Ant(const int& x, const int& y, Direccion dir) : x_{x}, y_{y}, dir_{dir} { }

  const Direccion dir() const { return dir_; }
  void step(Tape& tape);

  const int x() const { return x_; }
  const int y() const { return y_; }

 private:
  int x_;
  int y_;
  Direccion dir_;
};

std::ostream& operator<<(std::ostream& os, const Ant& ant);

#endif