// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: tape_periodic.h
// Contenido: declaración de la clase tape_periodic
// en esta versión del tablero las hormigas aparecen por el opuesto
// del tablero cuando se salen de los límites

#ifndef TAPE_PERIODIC_H_
#define TAPE_PERIODIC_H_

#include "tape.h"

class TapePeriodic : public Tape {
 public:
  TapePeriodic(int size_x, int size_y, int colors);

  int GetCell(int x, int y) const override;
  void SetCell(int x, int y, int color) override;

  void Print(std::ostream& os, const AntOverlay& overlay = {}) const override;

 private:
  std::vector<std::vector<Cell>> grid_;

  int WrapX(int x) const;
  int WrapY(int y) const;
};

#endif