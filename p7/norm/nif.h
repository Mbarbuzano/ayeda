// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 7: Árboles AVL
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/5/2026
// Archivo: nif.h
// Contenido: declaración de la clase nif


#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>

class Nif {
public:
    Nif() : nif_(0) {}
    explicit Nif(long n) : nif_(n) {}

    // Generación aleatoria
    static Nif random() {
        return Nif(rand() % 100000000L);
    }

    // Operadores de comparación
    bool operator==(const Nif& o) const { return nif_ == o.nif_; }
    bool operator!=(const Nif& o) const { return nif_ != o.nif_; }
    bool operator< (const Nif& o) const { return nif_ <  o.nif_; }
    bool operator> (const Nif& o) const { return nif_ >  o.nif_; }
    bool operator<=(const Nif& o) const { return nif_ <= o.nif_; }
    bool operator>=(const Nif& o) const { return nif_ >= o.nif_; }

    // E/S
    friend std::ostream& operator<<(std::ostream& os, const Nif& n) {
        os << std::setw(8) << std::setfill('0') << n.nif_;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Nif& n) {
        is >> n.nif_;
        return is;
    }

    // Para conversión implícita desde long en pruebas
    operator long() const { return nif_; }

private:
    long nif_;
};
