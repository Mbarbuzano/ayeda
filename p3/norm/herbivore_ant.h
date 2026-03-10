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
// Contenido: declaración de HerbivoreAnt
// Se mueve ortogonalmente. El giro en cada celda depende de la cadena
// de Gale (D/I por color). Al pasar por una celda gana TTL igual al
// valor numérico del color de esa celda.

#ifndef HERBIVORE_ANT_H_
#define HERBIVORE_ANT_H_

#include <string>
#include "ant.h"

class HerbivoreAnt : public Ant {
 public:
  // gale_rule: cadena de 'D'/'I', una letra por color (ej: "DDII")
  HerbivoreAnt(int x, int y, int direction, int ttl,
               const std::string& gale_rule);

  void Step(Tape& tape) override;
  std::string GetType() const override;

 private:
  std::string gale_rule_;  // regla de Gale, ej: "DDII"
};

#endif
