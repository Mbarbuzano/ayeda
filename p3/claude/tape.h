// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: tape.h
// Contenido: declaración de la clase tape
// esta será la estructura que maneja el tablero por el que se mueven las hormigas

#ifndef TAPE_H_
#define TAPE_H_

#include <vector>
#include <iostream>

// Representa una celda de la cinta
struct Cell {
  int color;

  Cell(int c = 0) : color(c) {}
};

// Clase base abstracta para las cintas
class Tape {
 public:
  Tape(int size_x, int size_y, int colors);
  virtual ~Tape() = default;

  int GetSizeX() const { return size_x_; }
  int GetSizeY() const { return size_y_; }
  int GetColors() const { return colors_; }

  // Acceso a celdas
  virtual int GetCell(int x, int y) const = 0;
  virtual void SetCell(int x, int y, int color) = 0;

  // Cambia el color de la celda de forma cíclica
  virtual void NextColor(int x, int y);

  // Mostrar la cinta
  virtual void Print(std::ostream& os) const = 0;

 protected:
  int size_x_;
  int size_y_;
  int colors_;
};

std::ostream& operator<<(std::ostream& os, const Tape& tape);

#endif