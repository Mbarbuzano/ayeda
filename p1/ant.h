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

enum Direccion {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Ant{
 public:
  Ant(const int& x, const int& y, Direccion dir) : x_{x}, y_{y}, dir_{dir} { }

  void step(Tape& tape);

 private:
  int x_;
  int y_;
  Direccion dir_;
};

std::ostream& operator<<(std::ostream& os, const Ant& ant);

#endif