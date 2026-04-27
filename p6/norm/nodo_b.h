// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 5: Ordenación
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 29/4/2026
// Archivo: nodo_b.h
// Contenido: declaración de la clase nodo_b

#pragma once

template <class Key>
class NodoB {
 public:
  NodoB(const Key& dato, NodoB<Key>* izdo = nullptr, NodoB<Key>* dcho = nullptr)
      : dato_(dato), izdo_(izdo), dcho_(dcho) {}

  Key&       dato()       { return dato_; }
  const Key& dato() const { return dato_; }

  NodoB<Key>*& izdo() { return izdo_; }
  NodoB<Key>*& dcho() { return dcho_; }

  NodoB<Key>* izdo() const { return izdo_; }
  NodoB<Key>* dcho() const { return dcho_; }

 protected:
  Key         dato_;
  NodoB<Key>* izdo_;
  NodoB<Key>* dcho_;
};
