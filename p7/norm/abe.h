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
#include <queue>

template <class Key>
class ABE : public AB<Key> {
public:
    ABE() : AB<Key>() {}

    bool insertar(const Key& k) override {
        NodoB<Key>* nuevo = new NodoB<Key>(k);
        if (this->raiz_ == nullptr) { this->raiz_ = nuevo; return true; }
        std::queue<NodoB<Key>*> q;
        q.push(this->raiz_);
        while (!q.empty()) {
            NodoB<Key>* n = q.front(); q.pop();
            if (n->izdo() == nullptr) { n->izdo() = nuevo; return true; }
            q.push(n->izdo());
            if (n->drcho() == nullptr) { n->drcho() = nuevo; return true; }
            q.push(n->drcho());
        }
        return true;
    }

    bool buscar(const Key& k) const override {
        std::queue<NodoB<Key>*> q;
        if (this->raiz_) q.push(this->raiz_);
        while (!q.empty()) {
            NodoB<Key>* n = q.front(); q.pop();
            if (n->getDato() == k) return true;
            if (n->izdo())  q.push(n->izdo());
            if (n->drcho()) q.push(n->drcho());
        }
        return false;
    }
};
