// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 7: Árboles AVL
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/5/2026
// Archivo: nodo_b.h
// Contenido: declaración de la clase nodo_b

#pragma once

template <class Key>
class NodoB {
public:
    NodoB(const Key& k,
          NodoB<Key>* izq = nullptr,
          NodoB<Key>* der = nullptr)
        : dato_(k), izdo_(izq), drcho_(der) {}

    virtual ~NodoB() {}

    Key getDato() const { return dato_; }
    void setDato(const Key& k) { dato_ = k; }

    NodoB<Key>*& izdo()  { return izdo_; }
    NodoB<Key>*& drcho() { return drcho_; }
    NodoB<Key>*  izdo()  const { return izdo_; }
    NodoB<Key>*  drcho() const { return drcho_; }

protected:
    Key        dato_;
    NodoB<Key>* izdo_;
    NodoB<Key>* drcho_;
};
