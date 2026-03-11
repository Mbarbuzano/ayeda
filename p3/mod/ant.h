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
// Contenido: declaración de la clase base Ant

#ifndef ANT_H_
#define ANT_H_

#include <string>
#include "tape.h"

class Ant {
 public:
  Ant(int x, int y, int direction, int ttl);
  virtual ~Ant() = default;

  // Método puro: cada tipo de hormiga implementa su movimiento
  virtual void Step(Tape& tape) = 0;

  // Devuelve el nombre del tipo para mostrar en pantalla, e.g. "H-DDII"
  virtual std::string GetType() const = 0;

  bool IsAlive() const;
  void Kill();

  int GetX() const;
  int GetY() const;
  int GetTTL() const;
  int GetDirection() const;

  // Reduce el TTL en 'amount'. Si llega a 0 o menos la hormiga muere.
  void ReduceTTL(int amount);

 protected:
  int x_;
  int y_;
  int direction_;  // 0=arriba 1=derecha 2=abajo 3=izquierda
  int ttl_;
  bool alive_;

  void MoveForward();       // movimiento ortogonal (herbívoras)
  void MoveDiagonal();      // movimiento diagonal (carnívoras)
  void DecreaseTTL();
  void IncreaseTTL(int amount);
};

#endif
