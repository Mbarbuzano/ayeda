// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 5: Ordenación
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 15/4/2026
// Archivo: sequence.h
// Contenido: declaración de la clase sequence


#pragma once
#include <cstddef>

// Clase base abstracta genérica para secuencias
template <typename Key>
class Sequence {
 public:
  virtual ~Sequence() = default;

  // Acceso por índice (lectura)
  virtual Key  operator[](unsigned i) const = 0;
  // Acceso por índice (escritura)
  virtual Key& operator[](unsigned i)       = 0;

  virtual unsigned size() const = 0;
};
