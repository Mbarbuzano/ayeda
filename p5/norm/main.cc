// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 5: Ordenación
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 15/4/2026
// Archivo: main.cc
// Contenido: archivo principal de compilación


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>   // atoi, rand, srand
#include <ctime>     // time

#include "nif.h"
#include "static_sequence.h"
#include "sort_method.h"

// ─────────────────────────────────────────────────────────
//  Uso
// ─────────────────────────────────────────────────────────
void usage(const char* prog) {
  std::cerr << "Uso: " << prog
            << " -size <s> -ord <m> -init <i> [f] -trace <y|n>\n"
            << "  -size  <s>   Tamaño de la secuencia\n"
            << "  -ord   <m>   Método: a=Selección b=Burbuja c=MergeSort d=HeapSort e=Shell\n"
            << "  -init  <i>   Forma de introducir datos:\n"
            << "               manual  → introducir por teclado\n"
            << "               random  → generación aleatoria\n"
            << "               file f  → leer del fichero f\n"
            << "  -trace <y|n> Mostrar traza (y) o no (n)\n"
            << "  (Solo para -ord e): -alfa <a>  valor de alfa, 0 < a < 1 (defecto 0.5)\n";
}

// ─────────────────────────────────────────────────────────
//  Programa principal
// ─────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
  // Valores por defecto
  unsigned    size     = 0;
  char        method   = '\0';
  std::string initMode;
  std::string fileName;
  bool        trace    = false;
  double      alfa     = 0.5;

  // ── Parseo de argumentos ──────────────────────────────
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg == "-size" && i + 1 < argc) {
      size = static_cast<unsigned>(std::atoi(argv[++i]));
    } else if (arg == "-ord" && i + 1 < argc) {
      method = argv[++i][0];
    } else if (arg == "-init" && i + 1 < argc) {
      initMode = argv[++i];
      if (initMode == "file" && i + 1 < argc)
        fileName = argv[++i];
    } else if (arg == "-trace" && i + 1 < argc) {
      trace = (argv[++i][0] == 'y');
    } else if (arg == "-alfa" && i + 1 < argc) {
      alfa = std::atof(argv[++i]);
    }
  }

  // ── Validaciones básicas ──────────────────────────────
  if (size == 0 || method == '\0' || initMode.empty()) {
    usage(argv[0]);
    return 1;
  }
  if (method == 'e' && (alfa <= 0.0 || alfa >= 1.0)) {
    std::cerr << "Error: alfa debe estar en (0, 1)\n";
    return 1;
  }

  // ── Crear y rellenar la secuencia ─────────────────────
  staticSequence<nif> seq(size);

  if (initMode == "manual") {
    std::cout << "Introduce " << size << " NIFs (solo la parte numérica):\n";
    for (unsigned i = 0; i < size; ++i) {
      std::cin >> seq[i];
    }
  } else if (initMode == "random") {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    for (unsigned i = 0; i < size; ++i)
      seq[i] = nif::random();
  } else if (initMode == "file") {
    std::ifstream fin(fileName);
    if (!fin) {
      std::cerr << "Error: no se puede abrir el fichero '" << fileName << "'\n";
      return 1;
    }
    for (unsigned i = 0; i < size && fin; ++i)
      fin >> seq[i];
  } else {
    std::cerr << "Error: modo de inicialización desconocido '" << initMode << "'\n";
    return 1;
  }

  // ── Mostrar secuencia inicial ─────────────────────────
  std::cout << "\nSecuencia inicial:\n  ";
  printSequence(seq);

  // ── Crear el objeto de ordenación ────────────────────
  SortMethod<nif>* sorter = nullptr;

  switch (method) {
    case 'a': sorter = new Selection<nif>(seq, trace);        break;
    case 'b': sorter = new Bubble<nif>(seq, trace);           break;
    case 'c': sorter = new MergeSort<nif>(seq, trace);        break;
    case 'd': sorter = new HeapSort<nif>(seq, trace);         break;
    case 'e': sorter = new Shell<nif>(seq, trace, alfa);      break;
    default:
      std::cerr << "Error: método '" << method << "' no reconocido\n";
      usage(argv[0]);
      return 1;
  }

  // ── Ejecutar ordenación ───────────────────────────────
  std::cout << "\nEjecutando algoritmo...\n";
  if (trace) std::cout << "─── Traza ───\n";
  sorter->Sort();

  // ── Mostrar resultado ─────────────────────────────────
  std::cout << "\nSecuencia ordenada:\n  ";
  printSequence(seq);

  delete sorter;
  return 0;
}
