// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 2: Hormiga de Langton Generalizada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/2/2026
// Archivo: ant.cc
// Contenido: implementación de la clase ant

#include "ant.h"

void Ant::turnRight() {
  switch (dir_) {
    case Direccion::UP:    dir_ = Direccion::RIGHT; break;
    case Direccion::RIGHT: dir_ = Direccion::DOWN;  break;
    case Direccion::DOWN:  dir_ = Direccion::LEFT;  break;
    case Direccion::LEFT:  dir_ = Direccion::UP;    break;
  }
}

void Ant::turnLeft() {
  switch (dir_) {
    case Direccion::UP:    dir_ = Direccion::LEFT;  break;
    case Direccion::LEFT:  dir_ = Direccion::DOWN;  break;
    case Direccion::DOWN:  dir_ = Direccion::RIGHT; break;
    case Direccion::RIGHT: dir_ = Direccion::UP;    break;
  }
}

void Ant::moveForward(int width, int height) {
  switch (dir_) {
    case Direccion::UP:    --y_; break;
    case Direccion::DOWN:  ++y_; break;
    case Direccion::LEFT:  --x_; break;
    case Direccion::RIGHT: ++x_; break;
  }

  if (x_ < 0) x_ = width - 1;
  if (x_ >= width) x_ = 0;

  if (y_ < 0) y_ = height - 1;
  if (y_ >= height) y_ = 0;
}