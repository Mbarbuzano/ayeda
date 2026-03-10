// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: ant.cc
// Contenido: implementación de la clase base ant


#include "ant.h"

Ant::Ant(int x, int y, int direction, int ttl)
  : x_(x), y_(y), direction_(direction), ttl_(ttl), alive_(true) {}

bool Ant::IsAlive() const {
  return alive_;
}

void Ant::Kill() {
  alive_ = false;
}

int Ant::GetX() const {
  return x_;
}

int Ant::GetY() const {
  return y_;
}

void Ant::DecreaseTTL() {
  ttl_--;
  if (ttl_ <= 0) {
    alive_ = false;
  }
}

void Ant::MoveForward() {
  switch (direction_) {
    case 0:
      y_--;
      break;
    case 1:
      x_++;
      break;
    case 2:
      y_++;
      break;
    case 3:
      x_--;
      break;
  }
}