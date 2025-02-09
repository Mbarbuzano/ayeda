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
// contiene la declaración de la clase big unsigned

#ifndef BIGUNSIGNED_H_
#define BIGUNSIGNED_H_

#include <iostream>
#include <vector>

class BigUnsigned {
 public:

  std::vector<unsigned char> number() const { return number_; }

  BigUnsigned(unsigned n = 0);
  BigUnsigned(const unsigned char* );
  BigUnsigned(const BigUnsigned&);

  BigUnsigned& operator=(const BigUnsigned&);

  bool operator==(const BigUnsigned&) const;
  bool operator<(const BigUnsigned&);

  BigUnsigned& operator++(); // Pre-incremento
  BigUnsigned operator++(int); // Post-incremento
  BigUnsigned& operator--(); // Pre-decremento
  BigUnsigned operator--(int); // Post-decremento

  BigUnsigned operator+(const BigUnsigned&);
  BigUnsigned operator-(const BigUnsigned&) const;
  BigUnsigned operator*(const BigUnsigned&) const;
  BigUnsigned operator/(const BigUnsigned&, const BigUnsigned&);
  BigUnsigned operator%(const BigUnsigned&) const;

 private:
  std::vector<unsigned char> number_;
};

std::ostream& operator<<(std::ostream&, const BigUnsigned&);
std::istream& operator>>(std::istream&, BigUnsigned&);

#endif