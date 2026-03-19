// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: dispersion_function.h
// Contenido: declaración de la clase abstracta dispersion_function y sus variantes
// esta clase abstracta tiene tres implementaciones, que establece el contrato
// las tres siguientes beben de ella y se encargan de convertir, sumar y encangarse de 
// números aleatorios de las keys

#pragma once

#include <cstdlib>

template<class Key>
class DispersionFunction {
 public:
  virtual unsigned operator()(const Key&) const = 0;
  virtual ~DispersionFunction() {}
};

template<class Key>
class DFModule : public DispersionFunction<Key> {
 public:
  DFModule(unsigned tableSize) : tableSize_(tableSize) {}

  unsigned operator()(const Key& k) const override {
    return (long)k % tableSize_;
  }

 private:
  unsigned tableSize_;
};

template<class Key>
class DFSum : public DispersionFunction<Key> {
 public:
  DFSum(unsigned tableSize) : tableSize_(tableSize) {}

  unsigned operator()(const Key& k) const override {
    long val = (long)k;
    unsigned sum = 0;
    while (val > 0) {
      sum += val % 10;
      val /= 10;
    }
    return sum % tableSize_;
  }

 private:
  unsigned tableSize_;
};

template<class Key>
class DFRandom : public DispersionFunction<Key> {
 public:
  DFRandom(unsigned tableSize) : tableSize_(tableSize) {}

  unsigned operator()(const Key& k) const override {
    srand((long)k);
    return rand() % tableSize_;
  }

 private:
  unsigned tableSize_;
};