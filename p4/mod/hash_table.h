// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 26/3/2026
// Archivo: hash_table.h
// Contenido: declaración de la clase hash_table

#pragma once

#include <iostream>
#include "dispersion_function.h"
#include "exploration_function.h"
#include "static_sequence.h"
#include "dynamic_sequence.h"

template<class Key, class Container = staticSequence<Key>>
class HashTable : public Sequence<Key> {
 public:
  HashTable(unsigned tableSize, DispersionFunction<Key>& fd,
            ExplorationFunction<Key>& fe, unsigned blockSize)
      : tableSize_(tableSize), fd_(fd), fe_(fe), blockSize_(blockSize) {
    table_ = new Container*[tableSize_];
    for (unsigned i = 0; i < tableSize_; i++) {
      table_[i] = new Container(blockSize_);
    }
  }

  ~HashTable() {
    for (unsigned i = 0; i < tableSize_; i++) {
      delete table_[i];
    }
    delete[] table_;
  }

  bool search(const Key& k) const override {
    unsigned pos = fd_(k);
    if (table_[pos]->search(k)) return true;
    for (unsigned i = 1; i < tableSize_; i++) {
      unsigned newPos = (pos + fe_(k, i)) % tableSize_;
      if (table_[newPos]->search(k)) return true;
      if (!table_[newPos]->isFull()) return false;
    }
    return false;
  }

  bool insert(const Key& k) override {
    unsigned pos = fd_(k);
    if (table_[pos]->insert(k)) return true;
    for (unsigned i = 1; i < tableSize_; i++) {
      unsigned newPos = (pos + fe_(k, i)) % tableSize_;
      if (table_[newPos]->insert(k)) return true;
    }
    return false;
  }

  void print() const {
    for (unsigned i = 0; i < tableSize_; i++) {
      std::cout << "[" << i << "] ";
      table_[i]->print();
      std::cout << "\n";
    }
  }

 private:
  unsigned tableSize_;
  unsigned blockSize_;
  DispersionFunction<Key>& fd_;
  ExplorationFunction<Key>& fe_;
  Container** table_;
};


template<class Key>
class HashTable<Key, dynamicSequence<Key>> : public Sequence<Key> {
 public:
  HashTable(unsigned tableSize, DispersionFunction<Key>& fd)
      : tableSize_(tableSize), fd_(fd) {
    table_ = new dynamicSequence<Key>[tableSize_];
  }

  ~HashTable() {
    delete[] table_;
  }

  bool search(const Key& k) const override {
    unsigned pos = fd_(k);
    return table_[pos].search(k);
  }

  bool insert(const Key& k) override {
    unsigned pos = fd_(k);
    return table_[pos].insert(k);
  }

  void print() const {
    for (unsigned i = 0; i < tableSize_; i++) {
      std::cout << "[" << i << "] ";
      table_[i].print();
      std::cout << "\n";
    }
  }

 private:
  unsigned tableSize_;
  DispersionFunction<Key>& fd_;
  dynamicSequence<Key>* table_;
};