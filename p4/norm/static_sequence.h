// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 26/3/2026
// Archivo: static_sequence.h
// Contenido: declaración de la clase static_sequence

#pragma once

#include "sequence.h"

template<class Key>
class staticSequence : public Sequence<Key> {
 public:
  staticSequence(unsigned blockSize) : blockSize_(blockSize), size_(0) {
    data_ = new Key[blockSize_];
  }

  ~staticSequence() {
    delete[] data_;
  }

  bool search(const Key& k) const override {
    for (unsigned i = 0; i < size_; i++) {
      if (data_[i] == k) return true;
    }
    return false;
  }

  bool insert(const Key& k) override {
    if (isFull()) return false;
    data_[size_++] = k;
    return true;
  }

  bool isFull() const {
    return size_ == blockSize_;
  }

 private:
  Key* data_;
  unsigned blockSize_;
  unsigned size_;
};