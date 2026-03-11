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
// Contenido: implementación de la clase base Ant

#include "ant.h"

Ant::Ant(int x, int y, int direction, int ttl)
  : x_(x), y_(y), direction_(direction), ttl_(ttl), alive_(true) {}

bool Ant::IsAlive() const { return alive_; }
void Ant::Kill() { alive_ = false; }
int Ant::GetX() const { return x_; }
int Ant::GetY() const { return y_; }
int Ant::GetTTL() const { return ttl_; }
int Ant::GetDirection() const { return direction_; }

void Ant::DecreaseTTL() {
  ttl_--;
  if (ttl_ <= 0) alive_ = false;
}

void Ant::IncreaseTTL(int amount) {
  ttl_ += amount;
}

void Ant::ReduceTTL(int amount) {
  ttl_ -= amount;
  if (ttl_ <= 0) alive_ = false;
}

// Movimiento ortogonal: arriba/derecha/abajo/izquierda
void Ant::MoveForward() {
  switch (direction_) {
    case 0: y_--; break;  // arriba
    case 1: x_++; break;  // derecha
    case 2: y_++; break;  // abajo
    case 3: x_--; break;  // izquierda
  }
}

// Movimiento diagonal: las carnívoras se mueven en diagonal
// dirección 0=arriba-derecha, 1=abajo-derecha, 2=abajo-izquierda, 3=arriba-izquierda
void Ant::MoveDiagonal() {
  switch (direction_) {
    case 0: x_++; y_--; break;  // arriba-derecha
    case 1: x_++; y_++; break;  // abajo-derecha
    case 2: x_--; y_++; break;  // abajo-izquierda
    case 3: x_--; y_--; break;  // arriba-izquierda
  }
}
