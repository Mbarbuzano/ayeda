// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 26/3/2026
// Archivo: dynamic_sequence.h
// Contenido: declaración de la clase dynamicSequence

#pragma once

#include <list>
#include <iostream>
#include "sequence.h"

template<class Key>
class dynamicSequence : public Sequence<Key> {
 public:
  bool search(const Key& k) const override {
    for (const Key& element : data_) {
      if (element == k) return true;
    }
    return false;
  }

  bool insert(const Key& k) override {
    data_.push_back(k);
    return true;
  }

  void print() const override {
    for (const Key& element : data_) {
      std::cout << element << " ";
    }
  }

 private:
  std::list<Key> data_;
};
