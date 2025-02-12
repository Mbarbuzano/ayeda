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

#include "bigunsigned.h"

class BigInteger {
 public:
  // Constructores
  BigInteger(int n = 0);
  BigInteger(const BigUnsigned&, bool negative = false);

  // Getters
  inline BigUnsigned number() const { return number_; }
  inline BigUnsigned number() { return number_; }
  inline bool is_negative() const { return is_negative_; }
  inline bool is_negative() { return is_negative_; }

  //Setters
  void SetNeg(const bool& is_negative) { is_negative_ = is_negative; }

  // Operadores de asignación y comparación
  BigInteger& operator=(const BigInteger&);
  bool operator==(const BigInteger&) const;
  bool operator<(const BigInteger&) const;

  // Operadores aritméticos
  BigInteger operator+(const BigInteger&) const;
  BigInteger operator-(const BigInteger&) const;
  BigInteger operator*(const BigInteger&) const;
  BigInteger operator/(const BigInteger&) const;
  BigInteger operator%(const BigInteger&) const;

  // Operadores de incremento y decremento
  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger& operator--();
  BigInteger operator--(int);

 private:
  BigUnsigned number_;  // Valor absoluto
  bool is_negative_;    // Indica si es negativo
};

std::ostream& operator<<(std::ostream&, const BigInteger&);
std::istream& operator>>(std::istream&, BigInteger&);

BigInteger mcd(const BigInteger& uno, const BigInteger& dos);

#endif
