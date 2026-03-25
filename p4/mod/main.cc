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
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "nif.h"
#include "dispersion_function.h"
#include "exploration_function.h"
#include "hash_table.h"

// Crea la función de dispersión según el código
DispersionFunction<nif>* createFd(unsigned fdCode, unsigned tableSize) {
  switch (fdCode) {
    case 1: return new DFModule<nif>(tableSize);
    case 2: return new DFSum<nif>(tableSize);
    case 3: return new DFRandom<nif>(tableSize);
    default:
      std::cerr << "Función de dispersión no válida\n";
      return nullptr;
  }
}

// Crea la función de exploración según el código
ExplorationFunction<nif>* createFe(unsigned feCode, DispersionFunction<nif>& fd) {
  switch (feCode) {
    case 1: return new EFLinear<nif>();
    case 2: return new EFQuadratic<nif>();
    case 3: return new EFDoubleDispersion<nif>(fd);
    case 4: return new EFRedispersion<nif>();
    default:
      std::cerr << "Función de exploración no válida\n";
      return nullptr;
  }
}

// Ejecuta el experimento para una combinación ts/bs dada y escribe resultados
void runExperiment(unsigned ts, unsigned bs, unsigned fdCode, unsigned feCode,
                   const std::string& hashType, std::ostream& out) {
  const std::vector<double> alphas = {0.25, 0.50, 0.75};
  const unsigned NUM_SEARCHES = 10;

  out << "========================================\n";
  out << "ts=" << ts << "  bs=" << bs
      << "  fd=" << fdCode
      << "  hash=" << hashType;
  if (hashType == "close") out << "  fe=" << feCode;
  out << "\n";
  out << std::left << std::setw(8) << "alpha"
      << std::setw(18) << "claves insertadas"
      << "media comparaciones\n";
  out << "----------------------------------------\n";

  for (double alpha : alphas) {
    // Número de claves a insertar = alpha * ts * bs
    unsigned numKeys = static_cast<unsigned>(alpha * ts * bs);

    // Crear función de dispersión
    DispersionFunction<nif>* fd = createFd(fdCode, ts);
    if (!fd) return;

    // Crear tabla
    Sequence<nif>* table = nullptr;
    ExplorationFunction<nif>* fe = nullptr;

    if (hashType == "open") {
      table = new HashTable<nif, dynamicSequence<nif>>(ts, *fd);
    } else {
      fe = createFe(feCode, *fd);
      if (!fe) { delete fd; return; }
      table = new HashTable<nif>(ts, *fd, *fe, bs);
    }

    // Insertar numKeys claves aleatorias
    unsigned inserted = 0;
    while (inserted < numKeys) {
      nif k; // constructor por defecto: valor aleatorio
      nif::resetComparisons();
      if (table->insert(k)) ++inserted;
    }

    // 10 búsquedas de claves aleatorias (pueden o no estar en la tabla)
    unsigned totalComparisons = 0;
    for (unsigned s = 0; s < NUM_SEARCHES; ++s) {
      nif k;
      nif::resetComparisons();
      table->search(k);
      totalComparisons += nif::getComparisons();
    }

    double mean = static_cast<double>(totalComparisons) / NUM_SEARCHES;

    out << std::left << std::setw(8) << alpha
        << std::setw(18) << numKeys
        << std::fixed << std::setprecision(2) << mean << "\n";

    delete table;
    delete fd;
    delete fe;
  }
  out << "\n";
}

int main(int argc, char* argv[]) {
  // Modo experimento automático (sin argumentos extra)
  // Modo interactivo (con -ts -fd -hash [-bs -fe])

  if (argc == 1) {
    // ---- MODO EXPERIMENTO ----
    srand(time(nullptr));

    // Parámetros fijos para el experimento
    const unsigned fdCode = 1;  // Módulo
    const unsigned feCode = 1;  // Lineal (para dispersión cerrada)
    const std::string hashType = "close";

    // Los 3 casos pedidos
    const std::vector<std::pair<unsigned,unsigned>> cases = {
      {100, 2}, {500, 5}, {1000, 15}
    };

    // Salida a pantalla y a fichero
    std::ofstream file("resultados.txt");
    if (!file) {
      std::cerr << "No se pudo abrir resultados.txt\n";
      return 1;
    }

    std::string header =
      "Experimento: media de comparaciones por factor de carga\n"
      "Dispersión cerrada, fd=Módulo, fe=Lineal\n\n";
    std::cout << header;
    file << header;

    for (auto& [ts, bs] : cases) {
      runExperiment(ts, bs, fdCode, feCode, hashType, std::cout);
      runExperiment(ts, bs, fdCode, feCode, hashType, file);
    }

    std::cout << "Resultados guardados en resultados.txt\n";
    file.close();
    return 0;
  }

  // ---- MODO INTERACTIVO ----
  if (argc < 7) {
    std::cerr << "Uso: " << argv[0]
              << " -ts <tableSize> -fd <f> -hash <open|close>"
              << " [-bs <blockSize> -fe <f>]\n"
              << "     (sin argumentos: ejecuta el experimento automático)\n";
    return 1;
  }

  unsigned tableSize = 0, fdCode = 0, feCode = 0, blockSize = 0;
  std::string hashType;

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if      (arg == "-ts")   tableSize = std::stoi(argv[++i]);
    else if (arg == "-fd")   fdCode    = std::stoi(argv[++i]);
    else if (arg == "-hash") hashType  = argv[++i];
    else if (arg == "-bs")   blockSize = std::stoi(argv[++i]);
    else if (arg == "-fe")   feCode    = std::stoi(argv[++i]);
  }

  srand(time(nullptr));

  DispersionFunction<nif>* fd = createFd(fdCode, tableSize);
  if (!fd) return 1;

  ExplorationFunction<nif>* fe = nullptr;
  Sequence<nif>* table = nullptr;

  if (hashType == "open") {
    table = new HashTable<nif, dynamicSequence<nif>>(tableSize, *fd);
  } else if (hashType == "close") {
    if (blockSize == 0) {
      std::cerr << "Dispersión cerrada requiere -bs\n";
      delete fd;
      return 1;
    }
    fe = createFe(feCode, *fd);
    if (!fe) { delete fd; return 1; }
    table = new HashTable<nif>(tableSize, *fd, *fe, blockSize);
  } else {
    std::cerr << "Tipo de dispersión no válido: use open o close\n";
    delete fd;
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
      nif::resetComparisons();
      if (table->insert(k))
        std::cout << "Insertado correctamente"
                  << " (" << nif::getComparisons() << " comparaciones)\n";
      else
        std::cout << "No se pudo insertar (tabla llena)\n";

    } else if (option == 2) {
      long val;
      std::cout << "NIF a buscar: ";
      std::cin >> val;
      nif k(val);
      nif::resetComparisons();
      if (table->search(k))
        std::cout << "Encontrado";
      else
        std::cout << "No encontrado";
      std::cout << " (" << nif::getComparisons() << " comparaciones)\n";
    }

  } while (option != 0);

  delete table;
  delete fd;
  delete fe;

  return 0;
}
