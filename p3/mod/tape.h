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

#ifndef TAPE_H_
#define TAPE_H_

#include <vector>
#include <map>
#include <string>
#include <iostream>

struct Cell {
  int color;
  Cell(int c = 0) : color(c) {}
};

// Información visual de una hormiga para pintar sobre el tablero
struct AntMark {
  char symbol;        // < > ^ v
  std::string ansi;   // código de color ANSI para esta hormiga
};

// Mapa de posición -> marca de hormiga
using AntOverlay = std::map<std::pair<int,int>, AntMark>;

class Tape {
 public:
  Tape(int size_x, int size_y, int colors);
  virtual ~Tape() = default;

  int GetSizeX() const { return size_x_; }
  int GetSizeY() const { return size_y_; }
  int GetColors() const { return colors_; }

  virtual int GetCell(int x, int y) const = 0;
  virtual void SetCell(int x, int y, int color) = 0;
  virtual void NextColor(int x, int y);

  // overlay: posiciones y símbolos de las hormigas (vacío = solo celdas)
  virtual void Print(std::ostream& os,
                     const AntOverlay& overlay = {}) const = 0;

 protected:
  int size_x_;
  int size_y_;
  int colors_;

  // Colores ANSI para las celdas según su valor
  static const char* CellColor(int c);
};

std::ostream& operator<<(std::ostream& os, const Tape& tape);

#endif
