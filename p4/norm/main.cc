// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 26/3/2026
// Archivo: main.cc
// Contenido: archivo principal del proyecto

#include <iostream>
#include <stdexcept>
#include "nif.h"
#include "dispersion_function.h"
#include "exploration_function.h"
#include "hash_table.h"

int main(int argc, char* argv[]) {
  if (argc < 7) {
    std::cerr << "Uso: " << argv[0]
              << " -ts <tableSize> -fd <f> -hash <open|close>"
              << " [-bs <blockSize> -fe <f>]\n";
    return 1;
  }

  unsigned tableSize = 0;
  unsigned fdCode = 0;
  unsigned feCode = 0;
  unsigned blockSize = 0;
  std::string hashType;

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if      (arg == "-ts")   tableSize = std::stoi(argv[++i]);
    else if (arg == "-fd")   fdCode    = std::stoi(argv[++i]);
    else if (arg == "-hash") hashType  = argv[++i];
    else if (arg == "-bs")   blockSize = std::stoi(argv[++i]);
    else if (arg == "-fe")   feCode    = std::stoi(argv[++i]);
  }

  DispersionFunction<nif>* fd = nullptr;
  switch (fdCode) {
    case 1: fd = new DFModule<nif>(tableSize);  break;
    case 2: fd = new DFSum<nif>(tableSize);     break;
    case 3: fd = new DFRandom<nif>(tableSize);  break;
    default:
      std::cerr << "Función de dispersión no válida\n";
      return 1;
  }

  srand(time(nullptr));

  ExplorationFunction<nif>* fe = nullptr;
  Sequence<nif>* table = nullptr;

  if (hashType == "open") {
    table = new HashTable<nif, dynamicSequence<nif>>(tableSize, *fd);
  } else if (hashType == "close") {
    if (blockSize == 0) {
      std::cerr << "Dispersión cerrada requiere -bs\n";
      return 1;
    }
    switch (feCode) {
      case 1: fe = new EFLinear<nif>();                    break;
      case 2: fe = new EFQuadratic<nif>();                 break;
      case 3: fe = new EFDoubleDispersion<nif>(*fd);       break;
      case 4: fe = new EFRedispersion<nif>();              break;
      default:
        std::cerr << "Función de exploración no válida\n";
        return 1;
    }
    table = new HashTable<nif>(tableSize, *fd, *fe, blockSize);
  } else {
    std::cerr << "Tipo de dispersión no válido: use open o close\n";
    return 1;
  }

  int option = 0;
  do {
    std::cout << "\n1. Insertar\n2. Buscar\n0. Salir\nOpción: ";
    std::cin >> option;

    if (option == 1) {
      long val;
      std::cout << "NIF a insertar: ";
      std::cin >> val;
      nif k(val);
      if (table->insert(k))
        std::cout << "Insertado correctamente\n";
      else
        std::cout << "No se pudo insertar (tabla llena)\n";

    } else if (option == 2) {
      long val;
      std::cout << "NIF a buscar: ";
      std::cin >> val;
      nif k(val);
      if (table->search(k))
        std::cout << "Encontrado\n";
      else
        std::cout << "No encontrado\n";
    }

  } while (option != 0);

  delete table;
  delete fd;
  delete fe;

  return 0;
}
