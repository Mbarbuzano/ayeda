// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 7: Árboles AVL
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/5/2026
// Archivo: nodo_avl.h
// Contenido: declaración de la clase nodo_avl


#pragma once
#include "nodo_b.h"

template <class Key>
class NodoAVL : public NodoB<Key> {
public:
    NodoAVL(const Key& k,
            NodoAVL<Key>* izq = nullptr,
            NodoAVL<Key>* der = nullptr)
        : NodoB<Key>(k, izq, der), bal_(0) {}

    int getBal() const { return bal_; }
    void setBal(int b) { bal_ = b; }

    NodoAVL<Key>*& izdo() {
        return reinterpret_cast<NodoAVL<Key>*&>(this->izdo_);
    }
    NodoAVL<Key>*& drcho() {
        return reinterpret_cast<NodoAVL<Key>*&>(this->drcho_);
    }
    NodoAVL<Key>* izdo()  const { return static_cast<NodoAVL<Key>*>(this->izdo_); }
    NodoAVL<Key>* drcho() const { return static_cast<NodoAVL<Key>*>(this->drcho_); }

private:
    int bal_;
};
