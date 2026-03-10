// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: tape_reflective.h
// Contenido: declaración de la clase tape_reflective
// en esta versión del tablero las hormigas cambian de dirección
// cuando chocan con el borde del tablero

#ifndef TAPE_REFLECTIVE_H_
#define TAPE_REFLECTIVE_H_

#include "tape.h"

class TapeReflective : public Tape {
 public:
  TapeReflective(int size_x, int size_y, int colors);

  int GetCell(int x, int y) const override;
  void SetCell(int x, int y, int color) override;

  void Print(std::ostream& os) const override;

 private:
  std::vector<std::vector<Cell>> grid_;

  int ReflectX(int& x, int& dir) const;
  int ReflectY(int& y, int& dir) const;
};

#endif