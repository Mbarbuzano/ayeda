// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: la hormiga de Langton
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/2/2026
// Archivo: simulator.h
// Contenido: declaración de la clase simulator, que actúa como director
//            de orquesta sobre los dos objetos "hormiga_" y "tablero_"

#include "simulator.h"
#include <limits>

void Simulator::run() {
  while (running_) {
    render();

    // Esperar Enter
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    hormiga_.step(tablero_);
    ++pasos_;

    if (out_of_bounds()) {
      running_ = false;
      std::cout << "La hormiga ha salido del tablero.\n";
    }
  }
}

void Simulator::render() const {
  // Limpiar pantalla
  std::cout << "\033[2J\033[H";

  std::cout << "Pasos: " << pasos_ << "\n";

  for (int y = 0; y < tablero_.size_y(); ++y) {
    for (int x = 0; x < tablero_.size_x(); ++x) {
      if (x == hormiga_.x() && y == hormiga_.y()) {
        std::cout << hormiga_;
      } else {
        std::cout << (tablero_.tablero()[y][x] ? "■" : "□");
      }
    }
    std::cout << '\n';
  }
}

bool Simulator::out_of_bounds() const {
  return hormiga_.x() < 0 || hormiga_.x() >= tablero_.size_x() ||
         hormiga_.y() < 0 || hormiga_.y() >= tablero_.size_y();
}