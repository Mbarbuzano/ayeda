// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: sliding_vector.h
// Contenido: declaración de la clase sliding_vector
// vamos a usar esta clase para manejar el tablero

#ifndef SLIDING_VECTOR_H
#define SLIDING_VECTOR_H

#include <vector>
#include "svexception.h"

template <class T>
class SlidingVector {
 public:
  SlidingVector(int index_min, int index_max);

  T& operator[](int index);
  const T& operator[](int index) const;

  int IndexMin() const;
  int IndexMax() const;

  void PushFront(const T& value);
  void PushBack(const T& value);

 private:
  std::vector<T> data_;
  int index_min_;
  int index_max_;

  int MapIndex(int index) const;
};

template <class T>
SlidingVector<T>::SlidingVector(int index_min, int index_max)
    : index_min_(index_min),
      index_max_(index_max),
      data_(index_max - index_min + 1) {}

template <class T>
int SlidingVector<T>::MapIndex(int index) const {
  if (index < index_min_ || index > index_max_) {
    throw SVException("SlidingVector: index out of range");
  }
  return index - index_min_;
}

template <class T>
T& SlidingVector<T>::operator[](int index) {
  return data_[MapIndex(index)];
}

template <class T>
const T& SlidingVector<T>::operator[](int index) const {
  return data_[MapIndex(index)];
}

template <class T>
int SlidingVector<T>::IndexMin() const {
  return index_min_;
}

template <class T>
int SlidingVector<T>::IndexMax() const {
  return index_max_;
}

template <class T>
void SlidingVector<T>::PushFront(const T& value) {
  data_.insert(data_.begin(), value);
  index_min_--;
}

template <class T>
void SlidingVector<T>::PushBack(const T& value) {
  data_.push_back(value);
  index_max_++;
}

#endif