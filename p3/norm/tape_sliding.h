// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: tape_sliding.h
// Contenido: declaración de la clase tape_sliding
// en esta versión del tablero las hormigas expanden el rango
// del tablero cuando chocan con un borde

#ifndef TAPE_SLIDING_H_
#define TAPE_SLIDING_H_

#include "tape.h"
#include "sliding_vector.h"

class TapeSliding : public Tape {
 public:
  TapeSliding(int size_x, int size_y, int colors);

  int GetCell(int x, int y) const override;
  void SetCell(int x, int y, int color) override;

  void Print(std::ostream& os) const override;

 private:
  SlidingVector<SlidingVector<Cell>> grid_;

  void ExpandLeft();
  void ExpandRight();
  void ExpandTop();
  void ExpandBottom();
};

#endif