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
  int size;
  std::cout << "Inserte las dimensiones del tablero (''x''): ";
  std::cin >> size;

  Ant hormiga{size / 2, size / 2, UP_RIGHT};
  Simulator simulador{size, size, hormiga};

  simulador.run();
}