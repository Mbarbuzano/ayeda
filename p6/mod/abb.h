// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 5: Ordenación
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 29/4/2026
// Archivo: abb.h
// Contenido: declaración de la clase abb

#pragma once

#include "ab.h"

template <class Key>
class ABB : public AB<Key> {
 public:
  ABB() : AB<Key>() {}

  // Insertar respetando la propiedad BST (recursivo)
  bool insertar(const Key& k) override {
    return insertarRec(this->raiz_, k);
  }

  bool buscar(const Key& k) const override {
    return buscarRec(this->raiz_, k);
  }

  bool buscarConContador(const Key& k, int& comparaciones) const override {
    comparaciones = 0;
    return buscarRecC(this->raiz_, k, comparaciones);
  }

 private:
  bool insertarRec(NodoB<Key>*& nodo, const Key& k) {
    if (!nodo) {
      nodo = new NodoB<Key>(k);
      return true;
    }
    if (k == nodo->dato()) return false;   // Duplicado
    if (k < nodo->dato())  return insertarRec(nodo->izdo(), k);
    else                   return insertarRec(nodo->dcho(), k);
  }

  bool buscarRec(NodoB<Key>* nodo, const Key& k) const {
    if (!nodo) return false;
    if (k == nodo->dato()) return true;
    if (k < nodo->dato())  return buscarRec(nodo->izdo(), k);
    else                   return buscarRec(nodo->dcho(), k);
  }

  // Versión con contador: cada comparación de dato cuenta como 1
  bool buscarRecC(NodoB<Key>* nodo, const Key& k, int& c) const {
    if (!nodo) return false;
    ++c;
    if (k == nodo->dato()) return true;
    if (k < nodo->dato())  return buscarRecC(nodo->izdo(), k, c);
    else                   return buscarRecC(nodo->dcho(), k, c);
  }
};
