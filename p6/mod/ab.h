// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 5: Ordenación
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 29/4/2026
// Archivo: ab.h
// Contenido: declaración de la clase abstracta ab


#pragma once

#include <iostream>
#include <queue>
#include "nodo_b.h"

template <class Key>
class AB {
 public:
  AB() : raiz_(nullptr) {}
  virtual ~AB() { podar(raiz_); }

  virtual bool insertar(const Key& k) = 0;
  virtual bool buscar(const Key& k) const = 0;

  // Igual que buscar() pero devuelve el número de comparaciones realizadas
  virtual bool buscarConContador(const Key& k, int& comparaciones) const = 0;

  bool esVacio() const { return raiz_ == nullptr; }

  // Recorrido inorden: izdo - raiz - dcho
  void inorden() const { inordenRec(raiz_); std::cout << "\n"; }

  // Sobrecarga operator<< : recorrido por niveles
  template <class K>
  friend std::ostream& operator<<(std::ostream& os, const AB<K>& arbol);

 protected:
  NodoB<Key>* raiz_;

  void podar(NodoB<Key>*& nodo) {
    if (!nodo) return;
    podar(nodo->izdo());
    podar(nodo->dcho());
    delete nodo;
    nodo = nullptr;
  }

  void inordenRec(NodoB<Key>* nodo) const {
    if (!nodo) return;
    inordenRec(nodo->izdo());
    std::cout << "[" << nodo->dato() << "] ";
    inordenRec(nodo->dcho());
  }

  // Tamaño del subárbol (usado por ABE para equilibrio)
  int tamano(NodoB<Key>* nodo) const {
    if (!nodo) return 0;
    return 1 + tamano(nodo->izdo()) + tamano(nodo->dcho());
  }
};

template <class Key>
std::ostream& operator<<(std::ostream& os, const AB<Key>& arbol) {
  if (arbol.esVacio()) {
    os << "Nivel 0: [.]\n";
    return os;
  }

  // BFS: cola de punteros (incluyendo nulos para mostrar [.])
  std::queue<NodoB<Key>*> cola;
  cola.push(arbol.raiz_);
  int nivel = 0;

  while (!cola.empty()) {
    int nNivel = cola.size();
    bool todosNulos = true;

    // Comprobar si todos en este nivel son nulos
    // (usamos una cola auxiliar para no consumir la principal)
    std::queue<NodoB<Key>*> copia = cola;
    while (!copia.empty()) {
      if (copia.front() != nullptr) { todosNulos = false; break; }
      copia.pop();
    }
    if (todosNulos) break;

    os << "Nivel " << nivel << ":";
    for (int i = 0; i < nNivel; ++i) {
      NodoB<Key>* nodo = cola.front();
      cola.pop();
      if (nodo) {
        os << " [" << nodo->dato() << "]";
        cola.push(nodo->izdo());
        cola.push(nodo->dcho());
      } else {
        os << " [.]";
        // No metemos hijos de nulos (ya no los necesitamos)
        cola.push(nullptr);
        cola.push(nullptr);
      }
    }
    os << "\n";
    ++nivel;
  }
  return os;
}
