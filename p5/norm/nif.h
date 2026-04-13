// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 5: Ordenación
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 15/4/2026
// Archivo: nif.h
// Contenido: declaración de la clase nif


#pragma once
#include <iostream>
#include <cstdlib>  // rand()
#include <iomanip>

// Clase nif: representa un Número de Identificación Fiscal (8 dígitos + letra)
class nif {
 public:
  // Constructores
  nif() : valor_(0) {}
  explicit nif(long v) : valor_(v % 100000000L) {}  // 8 dígitos máximo

  // Generación aleatoria
  static nif random() { return nif(static_cast<long>(rand()) % 100000000L); }

  // Operadores de comparación (necesarios para los algoritmos de ordenación)
  bool operator<(const nif& other)  const { return valor_ < other.valor_; }
  bool operator>(const nif& other)  const { return valor_ > other.valor_; }
  bool operator<=(const nif& other) const { return valor_ <= other.valor_; }
  bool operator>=(const nif& other) const { return valor_ >= other.valor_; }
  bool operator==(const nif& other) const { return valor_ == other.valor_; }
  bool operator!=(const nif& other) const { return valor_ != other.valor_; }

  // Entrada / salida
  friend std::ostream& operator<<(std::ostream& os, const nif& n) {
    os << std::setw(8) << std::setfill('0') << n.valor_ << letra(n.valor_);
    return os;
  }

  friend std::istream& operator>>(std::istream& is, nif& n) {
    is >> n.valor_;
    return is;
  }

 private:
  long valor_;

  // Letra NIF según el valor numérico
  static char letra(long v) {
    static const char letras[] = "TRWAGMYFPDXBNJZSQVHLCKE";
    return letras[v % 23];
  }
};
