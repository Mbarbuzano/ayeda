// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 7: Árboles AVL
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/5/2026
// Archivo: avl.h
// Contenido: declaración de la clase avl


#pragma once
#include "abb.h"
#include "nodo_avl.h"
#include <iostream>

template <class Key>
class AVL : public ABB<Key> {
public:
    AVL() : ABB<Key>(), raizAVL_(nullptr), traza_(false) {}

    void setTraza(bool t) { traza_ = t; }

    bool insertar(const Key& k) override {
        NodoAVL<Key>* nuevo = new NodoAVL<Key>(k);
        bool crece = false;
        if (!insertarBal(raizAVL_, nuevo, crece)) {
            delete nuevo;
            return false;
        }
        this->raiz_ = raizAVL_;
        return true;
    }

    bool buscar(const Key& k) const override {
        return ABB<Key>::buscar(k);
    }

private:
    NodoAVL<Key>* raizAVL_;
    bool traza_;

    bool insertarBal(NodoAVL<Key>*& nodo, NodoAVL<Key>* nuevo, bool& crece) {
        if (nodo == nullptr) { nodo = nuevo; crece = true; return true; }
        if (nuevo->getDato() == nodo->getDato()) return false;
        if (nuevo->getDato() < nodo->getDato()) {
            if (!insertarBal(nodo->izdo(), nuevo, crece)) return false;
            if (crece) insertarIzdo(nodo, crece);
        } else {
            if (!insertarBal(nodo->drcho(), nuevo, crece)) return false;
            if (crece) insertarDrcho(nodo, crece);
        }
        return true;
    }

    void syncRaiz() { this->raiz_ = raizAVL_; }

    void insertarIzdo(NodoAVL<Key>*& nodo, bool& crece) {
        switch (nodo->getBal()) {
            case -1: nodo->setBal(0); crece = false; break;
            case  0: nodo->setBal(1); break;
            case  1:
                if (traza_) { syncRaiz(); std::cout << "Desbalanceo:\n"; this->write(std::cout); }
                if (nodo->izdo()->getBal() == 1) rotII(nodo);
                else                              rotID(nodo);
                crece = false;
                break;
        }
    }

    void insertarDrcho(NodoAVL<Key>*& nodo, bool& crece) {
        switch (nodo->getBal()) {
            case  1: nodo->setBal(0); crece = false; break;
            case  0: nodo->setBal(-1); break;
            case -1:
                if (traza_) { syncRaiz(); std::cout << "Desbalanceo:\n"; this->write(std::cout); }
                if (nodo->drcho()->getBal() == -1) rotDD(nodo);
                else                               rotDI(nodo);
                crece = false;
                break;
        }
    }

    void rotII(NodoAVL<Key>*& nodo) {
        NodoAVL<Key>* n1 = nodo->izdo();
        if (traza_) std::cout << "Rotación II en [" << nodo->getDato() << "(" << nodo->getBal() << ")]:\n";
        nodo->izdo() = n1->drcho(); n1->drcho() = nodo;
        if (n1->getBal() == 1) { nodo->setBal(0); n1->setBal(0); }
        else                   { nodo->setBal(1); n1->setBal(-1); }
        nodo = n1;
        if (traza_) { syncRaiz(); this->write(std::cout); }
    }

    void rotDD(NodoAVL<Key>*& nodo) {
        NodoAVL<Key>* n1 = nodo->drcho();
        if (traza_) std::cout << "Rotación DD en [" << nodo->getDato() << "(" << nodo->getBal() << ")]:\n";
        nodo->drcho() = n1->izdo(); n1->izdo() = nodo;
        if (n1->getBal() == -1) { nodo->setBal(0); n1->setBal(0); }
        else                    { nodo->setBal(-1); n1->setBal(1); }
        nodo = n1;
        if (traza_) { syncRaiz(); this->write(std::cout); }
    }

    void rotID(NodoAVL<Key>*& nodo) {
        NodoAVL<Key>* n1 = nodo->izdo();
        NodoAVL<Key>* n2 = n1->drcho();
        if (traza_) std::cout << "Rotación ID en [" << nodo->getDato() << "(" << nodo->getBal() << ")]:\n";
        n1->drcho() = n2->izdo(); n2->izdo() = n1;
        nodo->izdo() = n2->drcho(); n2->drcho() = nodo;
        if (n2->getBal() ==  1) nodo->setBal(-1); else nodo->setBal(0);
        if (n2->getBal() == -1) n1->setBal(1);    else n1->setBal(0);
        n2->setBal(0); nodo = n2;
        if (traza_) { syncRaiz(); this->write(std::cout); }
    }

    void rotDI(NodoAVL<Key>*& nodo) {
        NodoAVL<Key>* n1 = nodo->drcho();
        NodoAVL<Key>* n2 = n1->izdo();
        if (traza_) std::cout << "Rotación DI en [" << nodo->getDato() << "(" << nodo->getBal() << ")]:\n";
        n1->izdo() = n2->drcho(); n2->drcho() = n1;
        nodo->drcho() = n2->izdo(); n2->izdo() = nodo;
        if (n2->getBal() == -1) nodo->setBal(1);  else nodo->setBal(0);
        if (n2->getBal() ==  1) n1->setBal(-1);   else n1->setBal(0);
        n2->setBal(0); nodo = n2;
        if (traza_) { syncRaiz(); this->write(std::cout); }
    }
};
