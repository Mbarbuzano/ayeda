// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 5: Ordenación
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 29/4/2026
// Archivo: abe.h
// Contenido: declaración de la clase ABE

#pragma once

#include <queue>
#include "ab.h"

template <class Key>
class ABE : public AB<Key> {
 public:
  ABE() : AB<Key>() {}

  // Insertar manteniendo el equilibrio perfecto
  // Estrategia: BFS para encontrar el primer nodo con hueco
  bool insertar(const Key& k) override {
    if (buscar(k)) return false;   // No admite duplicados

    NodoB<Key>* nuevo = new NodoB<Key>(k);

    if (!this->raiz_) {
      this->raiz_ = nuevo;
      return true;
    }

    // BFS: primer nodo con hueco (izdo antes que dcho)
    std::queue<NodoB<Key>*> cola;
    cola.push(this->raiz_);

    while (!cola.empty()) {
      NodoB<Key>* actual = cola.front();
      cola.pop();

      if (!actual->izdo()) {
        actual->izdo() = nuevo;
        return true;
      } else {
        cola.push(actual->izdo());
      }

      if (!actual->dcho()) {
        actual->dcho() = nuevo;
        return true;
      } else {
        cola.push(actual->dcho());
      }
    }
    return false;
  }

  bool buscar(const Key& k) const override {
    return buscarRec(this->raiz_, k);
  }

 private:
  bool buscarRec(NodoB<Key>* nodo, const Key& k) const {
    if (!nodo) return false;
    if (nodo->dato() == k) return true;
    return buscarRec(nodo->izdo(), k) || buscarRec(nodo->dcho(), k);
  }
};
