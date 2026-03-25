// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 26/3/2026
// Archivo: nif.h
// Contenido: declaración de la clase Nif

#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

class nif {
 public:
  static unsigned comparisons;

  static void resetComparisons() { comparisons = 0; }
  static unsigned getComparisons() { return comparisons; }

  nif() {
    value_ = rand() % 100000000;
  }

  nif(long n) : value_(n) {}

  operator long() const {
    return value_;
  }

  bool operator==(const nif& other) const {
    ++comparisons;
    return value_ == other.value_;
  }

  bool operator!=(const nif& other) const {
    ++comparisons;
    return value_ != other.value_;
  }

  friend std::ostream& operator<<(std::ostream& os, const nif& n) {
    os << n.value_;
    return os;
  }

 private:
  long value_;
};

inline unsigned nif::comparisons = 0;
