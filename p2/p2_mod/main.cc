// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 2: Hormiga de Langton Generalizada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 25/2/2026
// Archivo: main.cc
// Contenido: archivo principal de compilacion

#include "simulator.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Uso: ./langton fichero.txt\n";
    return 1;
  }

  Simulator sim(argv[1]);
  sim.run(10000);

  return 0;
}