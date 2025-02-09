// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: Números enteros grandes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: /02/2025
// Archivo: biginteger.h
// contiene la declaración de la clase big integer

#ifndef BIGINTEGER_H_
#define BIGINTEGER_H_

#include <iostream>
#include <vector>

class BigInteger {
 public:

  std::vector<unsigned char> number() const { return number_; }

  BigInteger(unsigned n = 0);
  BigInteger(const unsigned char* );
  BigInteger(const BigInteger&);

  BigInteger& BigInteger::operator=(const BigInteger&);

  bool operator==(const BigInteger&) const;
  bool operator<(const BigInteger&);

  BigInteger& operator++(); // Pre-incremento
  BigInteger operator++(int); // Post-incremento
  BigInteger& operator--(); // Pre-decremento
  BigInteger operator--(int); // Post-decremento

  BigInteger operator+(const BigInteger&);
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  BigInteger operator/(const BigInteger&, const BigInteger&);
  BigInteger operator%(const BigInteger&) const;

 private:
  std::vector<unsigned char> number_;
};

std::ostream& operator<<(std::ostream&, const BigInteger&);
std::istream& operator>>(std::istream&, BigInteger&);

#endif