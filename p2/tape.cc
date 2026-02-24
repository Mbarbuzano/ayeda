// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: la hormiga de Langton
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/2/2026
// Archivo: tape.cc
// Contenido: implementación de la clase tape

#include "tape.h"


// Secuencias ANSI para colores (background)
const std::string COLORS[4] = {
  "\033[47m", // blanco
  "\033[41m", // rojo
  "\033[42m", // verde
  "\033[44m"  // azul
};
const std::string RESET = "\033[0m";

void Tape::print(const std::vector<Ant*>& ants) const {
    for (int y = 0; y < height_; ++y) {
        std::cout << y << "|"; // número de fila
        for (int x = 0; x < width_; ++x) {
            bool printed = false;
            for (auto ant : ants) {
                if (ant->x() == x && ant->y() == y) {
                    // Mostrar la hormiga con dirección
                    switch (ant->dir()) {
                        case Direccion::UP:    std::cout << "^"; break;
                        case Direccion::DOWN:  std::cout << "v"; break;
                        case Direccion::LEFT:  std::cout << "<"; break;
                        case Direccion::RIGHT: std::cout << ">"; break;
                    }
                    printed = true;
                    break;
                }
            }
            if (!printed) {
                int color = grid_[y][x];
                std::cout << COLORS[color % 4] << " " << RESET;
            }
        }
        std::cout << "\n";
    }

    // Números de columna arriba
    std::cout << " ";
    for (int x = 0; x < width_; ++x)
        std::cout << x % 10;
    std::cout << "\n";
}