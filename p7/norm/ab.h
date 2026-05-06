// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 7: Árboles AVL
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/5/2026
// Archivo: ab.h
// Contenido: declaración de la clase ab


#pragma once
#include "nodo_b.h"
#include "nodo_avl.h"
#include <iostream>
#include <queue>
#include <sstream>

template <class Key>
class AB {
public:
    AB() : raiz_(nullptr), traza_(false) {}
    virtual ~AB() { podar(raiz_); }

    bool esVacio() const { return raiz_ == nullptr; }

    virtual bool insertar(const Key& k) = 0;
    virtual bool buscar(const Key& k) const = 0;

    void setTraza(bool t) { traza_ = t; }
    bool getTraza()       { return traza_; }

    // Inorden
    void inorden() const { inorden(raiz_); std::cout << "\n"; }

    // Escritura por niveles (operador <<)
    friend std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
        arbol.write(os);
        return os;
    }

    void write(std::ostream& os) const {
        if (esVacio()) { os << "Árbol vacío\n"; }
        std::queue<NodoB<Key>*> q;
        q.push(raiz_);
        int nivel = 0;
        while (!q.empty()) {
            os << "Nivel " << nivel++ << ": ";
            int n = q.size();
            bool alguno = false;
            for (int i = 0; i < n; ++i) {
                NodoB<Key>* nodo = q.front(); q.pop();
                if (nodo == nullptr) {
                    os << "[.]";
                } else {
                    alguno = true;
                    // Si es nodoAVL y traza_ activa, mostramos el balance
                    NodoAVL<Key>* navl = dynamic_cast<NodoAVL<Key>*>(nodo);
                    if (navl && traza_)
                        os << "[" << nodo->getDato() << "(" << navl->getBal() << ")]";
                    else
                        os << "[" << nodo->getDato() << "]";
                    q.push(nodo->izdo());
                    q.push(nodo->drcho());
                }
                if (i + 1 < n) os << " ";
            }
            os << "\n";
            if (!alguno) break;
        }
    }

protected:
    NodoB<Key>* raiz_;
    bool traza_;

    void podar(NodoB<Key>*& nodo) {
        if (nodo == nullptr) return;
        podar(nodo->izdo());
        podar(nodo->drcho());
        delete nodo;
        nodo = nullptr;
    }

    void inorden(NodoB<Key>* nodo) const {
        if (nodo == nullptr) return;
        inorden(nodo->izdo());
        std::cout << nodo->getDato() << " ";
        inorden(nodo->drcho());
    }
};
