// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 6: Árboles
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 29/4/2026
// Archivo: nif.h
// Contenido: declaración de la case nif

#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

class Nif {
 public:
  // Constructores
  Nif() : numero_(rand() % 100000000L), letra_(calcularLetra(numero_)) {}
  explicit Nif(long numero) : numero_(numero), letra_(calcularLetra(numero)) {}

  // Conversión implícita desde long (útil para random/file)
  operator long() const { return numero_; }

  // Operadores de comparación (necesarios para ABB y ABE)
  bool operator==(const Nif& otro) const { return numero_ == otro.numero_; }
  bool operator!=(const Nif& otro) const { return numero_ != otro.numero_; }
  bool operator< (const Nif& otro) const { return numero_ <  otro.numero_; }
  bool operator> (const Nif& otro) const { return numero_ >  otro.numero_; }
  bool operator<=(const Nif& otro) const { return numero_ <= otro.numero_; }
  bool operator>=(const Nif& otro) const { return numero_ >= otro.numero_; }

  // Entrada / salida
  friend std::ostream& operator<<(std::ostream& os, const Nif& n) {
    os << n.numero_ << n.letra_;
    return os;
  }

  friend std::istream& operator>>(std::istream& is, Nif& n) {
    is >> n.numero_;
    n.letra_ = calcularLetra(n.numero_);
    return is;
  }

 private:
  long numero_;
  char letra_;

  static char calcularLetra(long num) {
    const std::string letras = "TRWAGMYFPDXBNJZSQVHLCKE";
    return letras[num % 23];
  }
};
