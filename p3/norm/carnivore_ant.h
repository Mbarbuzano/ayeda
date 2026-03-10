// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: carnivore_ant.h
// Contenido: declaración de la clase carnivore_ant
// esta hormiga se come al resto cuando se juntan en la misma celda

#ifndef CARNIVORE_ANT_H_
#define CARNIVORE_ANT_H_

#include "ant.h"

class CarnivoreAnt : public Ant {
 public:
  CarnivoreAnt(int x, int y, int direction, int ttl);

  void Step(Tape& tape) override;

  void SetAnts(std::vector<Ant*>* ants);

 private:
  std::vector<Ant*>* ants_;
};

#endif