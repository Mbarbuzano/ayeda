// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: herbivore_ant.h
// Contenido: declaración de la clase herbivore_ant

#ifndef HERBIVORE_ANT_H_
#define HERBIVORE_ANT_H_

#include "ant.h"

class HerbivoreAnt : public Ant {
 public:
  HerbivoreAnt(int x, int y, int direction, int ttl);

  void Step(Tape& tape) override;
};

#endif