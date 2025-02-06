// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: Números enteros grandes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: /02/2025
// Archivo: bigunsigned.h
// contiene la implementación de los métodos de la clase big unsigned

#include "bigunsigned.h"

BigUnsigned::BigUnsigned(unsigned n = 0) {
  number_[0] = 0;
}

BigUnsigned::BigUnsigned(const unsigned char* array) {
  for (size_t i{0}; i < sizeof(array); ++i) {
    number_[i] = array[sizeof(array) - i - 1] - '0';
  }
}

BigUnsigned& BigUnsigned::operator=(const BigUnsigned& numero) {
    number_ = numero.number_;
}

std::ostream& operator<<(std::ostream& os, const BigUnsigned& numero) {
  for (size_t i{sizeof(numero)}; i > 0; --i) {
    os << numero.number()[i];
  }
  os << "\n";
  return os;
}

bool BigUnsigned::operator==(const BigUnsigned& numero) const {
  for (size_t i{0}; i < sizeof(numero); ++i) {
    if (number_[i] != numero.number()[i]) return false;
  }
  return true;
}

bool BigUnsigned::operator<(const BigUnsigned& numero) {
  for (size_t i{sizeof(numero)}; i > 0; ++i) {
    if (number_[i] < numero.number()[i]) return true;
    else if (number_[i] > numero.number()[i]) return false;
  }
}

BigUnsigned operator+(const BigUnsigned& numero) {
  bool carry{false};
  for (size_t i{0}; i < sizeof(numero); ++i) {
    
  }
}