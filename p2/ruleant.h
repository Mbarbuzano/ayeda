// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 2: Hormiga de Langton Generalizada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/2/2026
// Archivo: ruleant.h
// Contenido: declaración de la clase ruleant 

#ifndef RULEANT_H_
#define RULEANT_H_

#include "ant.h"

class RuleAnt : public Ant {
public:
  RuleAnt(int x, int y, Direccion dir, std::string rule);

  void step(Tape& tape) override;

private:
  std::string rule_;
};

#endif