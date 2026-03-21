// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 26/3/2026
// Archivo: exploration_function.h
// Contenido: declaración de la clase exploration_function

#pragma once

#include <cstdlib>
#include "dispersion_function.h"

template<class Key>
class ExplorationFunction {
 public:
  virtual unsigned operator()(const Key&, unsigned) const = 0;
  virtual ~ExplorationFunction() {}
};

template<class Key>
class EFLinear : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const override {
    return i;
  }
};

template<class Key>
class EFQuadratic : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const override {
    return i * i;
  }
};

template<class Key>
class EFDoubleDispersion : public ExplorationFunction<Key> {
 public:
  EFDoubleDispersion(DispersionFunction<Key>& f) : f_(f) {}

  unsigned operator()(const Key& k, unsigned i) const override {
    return f_(k) * i;
  }

 private:
  DispersionFunction<Key>& f_;
};

template<class Key>
class EFRedispersion : public ExplorationFunction<Key> {
 public:
  unsigned operator()(const Key& k, unsigned i) const override {
    srand((long)k);
    unsigned result = 0;
    for (unsigned j = 0; j < i; j++) {
      result = rand();
    }
    return result;
  }
};

