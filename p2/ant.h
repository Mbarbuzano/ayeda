// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 2: Hormiga de Langton Generalizada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/2/2026
// Archivo: ant.h
// Contenido: declaración de la clase abstracta ant

#ifndef ANT_H_
#define ANT_H_

#include "tape.h"

enum class Direccion {
  UP,
  RIGHT,
  DOWN,
  LEFT
};

class Ant {
public:
  Ant(int x, int y, Direccion dir)
    : x_{x}, y_{y}, dir_{dir} {}

  virtual ~Ant() = default;

  virtual void step(Tape& tape) = 0;

  int x() const { return x_; }
  int y() const { return y_; }
  Direccion dir() const { return dir_; }

protected:
  void turnRight();
  void turnLeft();
  void moveForward();

  int x_;
  int y_;
  Direccion dir_;
};

#endif