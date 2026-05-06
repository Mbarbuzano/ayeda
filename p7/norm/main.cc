// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 7: Árboles AVL
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 6/5/2026
// Archivo: main.cc
// Contenido: archivo principal de compilación


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "nif.h"
#include "abe.h"
#include "abb.h"
#include "avl.h"

// ── Ayuda ────────────────────────────────────────────────────────────────────
void usage(const char* prog) {
    std::cerr << "Uso: " << prog
              << " -ab <abe|abb|avl>"
              << " -init <manual|random [n]|file [n] [fichero]>"
              << " [-trace <y|n>]\n";
    std::exit(1);
}

// ── Menú ─────────────────────────────────────────────────────────────────────
void menu(AB<Nif>* arbol) {
    int opcion;
    do {
        std::cout << "\n[0] Salir\n"
                     "[1] Insertar clave\n"
                     "[2] Buscar clave\n"
                     "[3] Mostrar árbol inorden\n"
                     "Opción: ";
        std::cin >> opcion;
        switch (opcion) {
            case 1: {
                Nif k;
                std::cout << "Clave a insertar: "; std::cin >> k;
                if (arbol->insertar(k)) {
                    std::cout << "Insertado.\n";
                    arbol->write(std::cout);
                } else {
                    std::cout << "Clave ya existente o error.\n";
                }
                break;
            }
            case 2: {
                Nif k;
                std::cout << "Clave a buscar: "; std::cin >> k;
                std::cout << (arbol->buscar(k) ? "Encontrado.\n" : "No encontrado.\n");
                break;
            }
            case 3:
                arbol->inorden();
                break;
            case 0:
                std::cout << "Saliendo.\n";
                break;
            default:
                std::cout << "Opción no válida.\n";
        }
    } while (opcion != 0);
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::string tipoArbol;
    std::string modoInit;
    int    numElem   = 0;
    std::string fichero;
    bool   traza     = false;

    // ── Parseo de argumentos ──
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-ab") {
            if (++i >= argc) usage(argv[0]);
            tipoArbol = argv[i];
        } else if (arg == "-init") {
            if (++i >= argc) usage(argv[0]);
            modoInit = argv[i];
            if (modoInit == "random" || modoInit == "file") {
                if (i + 1 < argc && std::isdigit(argv[i+1][0]))
                    numElem = std::atoi(argv[++i]);
                if (modoInit == "file" && i + 1 < argc)
                    fichero = argv[++i];
            }
        } else if (arg == "-trace") {
            if (++i >= argc) usage(argv[0]);
            traza = (std::string(argv[i]) == "y");
        } else {
            usage(argv[0]);
        }
    }

    if (tipoArbol.empty() || modoInit.empty()) usage(argv[0]);

    // ── Crear árbol ──
    AB<Nif>* arbol = nullptr;
    if      (tipoArbol == "abe") arbol = new ABE<Nif>();
    else if (tipoArbol == "abb") arbol = new ABB<Nif>();
    else if (tipoArbol == "avl") {
        AVL<Nif>* avl = new AVL<Nif>();
        avl->setTraza(traza);
        arbol = avl;
    }
    else { std::cerr << "Tipo de árbol no válido: " << tipoArbol << "\n"; return 1; }

    arbol->setTraza(traza);

    // ── Inicializar árbol ──
    if (modoInit == "manual") {
        // Árbol vacío — el usuario inserta desde el menú
        std::cout << "Árbol vacío\n";
        arbol->write(std::cout);
    } else if (modoInit == "random") {
        for (int i = 0; i < numElem; ++i) {
            Nif k = Nif::random();
            if (arbol->insertar(k))
                arbol->write(std::cout);
        }
    } else if (modoInit == "file") {
        std::ifstream f(fichero);
        if (!f) { std::cerr << "No se puede abrir " << fichero << "\n"; return 1; }
        Nif k;
        int cnt = 0;
        while (cnt < numElem && f >> k) {
            if (arbol->insertar(k))
                arbol->write(std::cout);
            ++cnt;
        }
    }

    menu(arbol);

    delete arbol;
    return 0;
}
