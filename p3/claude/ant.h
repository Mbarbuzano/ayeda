// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: ant.h
// Contenido: declaración de la clase ant
// ant es la clase base de la jerarquía

#ifndef ANT_H_
#define ANT_H_

#include "tape.h"

class Ant {
 public:
  Ant(int x, int y, int direction, int ttl);

  virtual ~Ant() = default;

  virtual void Step(Tape& tape) = 0;

  bool IsAlive() const;
  void Kill();

  int GetX() const;
  int GetY() const;

 protected:
  int x_;
  int y_;
  int direction_;
  int ttl_;
  bool alive_;

  void MoveForward();
  void DecreaseTTL();
};

#endif