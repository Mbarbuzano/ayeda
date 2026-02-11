// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: la hormiga de Langton
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/2/2026
// Archivo: main.cc
// Contenido: archivo principal de compilación

#include "simulator.h"

int main() {
  int sizex, sizey;
  std::cout << "Inserte las dimensiones del tablero (''x''): ";
  std::cin >> sizex;
  sizey = sizex;

  Ant hormiga{sizex / 2, sizey / 2, UP};
  Simulator simulador{sizex, sizey, hormiga};

  simulador.run();
}