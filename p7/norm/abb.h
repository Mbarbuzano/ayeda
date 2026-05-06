// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 7: Árboles AVL
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/5/2026
// Archivo: abe.h
// Contenido: declaración de la clase abe


#pragma once
#include "ab.h"

template <class Key>
class ABB : public AB<Key> {
public:
    ABB() : AB<Key>() {}

    bool insertar(const Key& k) override {
        if (buscar(k)) return false;
        insertar(this->raiz_, k);
        return true;
    }

    bool buscar(const Key& k) const override {
        return buscar(this->raiz_, k);
    }

private:
    void insertar(NodoB<Key>*& nodo, const Key& k) {
        if (nodo == nullptr) {
            nodo = new NodoB<Key>(k);
            return;
        }
        if (k < nodo->getDato())
            insertar(nodo->izdo(), k);
        else
            insertar(nodo->drcho(), k);
    }

    bool buscar(NodoB<Key>* nodo, const Key& k) const {
        if (nodo == nullptr)            return false;
        if (k == nodo->getDato())       return true;
        if (k < nodo->getDato())        return buscar(nodo->izdo(), k);
        return buscar(nodo->drcho(), k);
    }
};
