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

// CONSTRUCTORES

BigUnsigned::BigUnsigned(unsigned n) { // Constructor por defecto
  if (n == 0) {
    number_[0] = 0;
    return;
  }
  while (n > 0) {
    number_.push_back(n % 10);
    n /= 10;
  }
}

BigUnsigned::BigUnsigned(const unsigned char* array) { // Constructor 
  size_t length{std::strlen(reinterpret_cast<const char*>(array))};
  number_.resize(length);
  for (size_t i{0}; i < length; ++i) {
    number_[i] = array[length - i - 1] - '0';
  }
}

BigUnsigned::BigUnsigned(const BigUnsigned& numero) { // Constructor de copia
  number_ = numero.number_;
}

// OPERADORES

BigUnsigned& BigUnsigned::operator=(const BigUnsigned& numero) { // Operador de asignación
  if (this != &numero) { 
    number_ = numero.number_;
  }
  return *this;
}

bool BigUnsigned::operator==(const BigUnsigned& numero) const { // Operador de igualdad
  return number_ == numero.number_;
}

bool BigUnsigned::operator<(const BigUnsigned& numero) const { // Operador menor
  if (number_.size() < numero.number_.size()) return true;
  if (number_.size() == numero.number_.size()) {
    for (size_t i{number_.size()}; i > 0; i-- > 0) {
      if (number_[i] < numero.number_[i]) return true;
      if (number_[i] == numero.number_[i]) continue;
    }
  }
  return false;
}

BigUnsigned BigUnsigned::operator++() {} // Pre-incremento
BigUnsigned& BigUnsigned::operator++(int inc) {} // Post-incremento
BigUnsigned BigUnsigned::operator--() {} // Pre-decremento
BigUnsigned& BigUnsigned::operator--(int dec) {} // Post-decremento

BigUnsigned BigUnsigned::operator+(const BigUnsigned& numero) {
  bool carry{false};
  for (size_t i{0}; i < numero.number().size(); ++i) {
    number_[i] = number()[i] + numero.number()[i] + carry;
    carry = false;
    if (number_[i] >= 10) {
      number_[i] = number_[i] - '10';
      carry = true;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const BigUnsigned& numero) {
  if (numero.number().empty()) {
    os << "0\n";
  }
  else {
    for (size_t i{numero.number().size()}; i > 0; i-- > 0) {
      os << static_cast<char>(numero.number()[i] + '0');
    }
  }
  os << "\n";
  return os;
}

std::istream& operator>>(std::istream& is, BigUnsigned& numero) {
  
}