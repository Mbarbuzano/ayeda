// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 5: Ordenación
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 29/4/2026
// Archivo: main.h
// Contenido: archivo principal de compilación

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "nif.h"
#include "abe.h"
#include "abb.h"

// ─── Uso ─────────────────────────────────────────────────────────────────────
void uso(const char* prog) {
  std::cerr << "Uso:\n"
            << "  " << prog << " -ab <abe|abb> -init <i> [s] [f]\n\n"
            << "  -ab  <abe|abb>   Tipo de árbol\n"
            << "  -init manual     Árbol vacío; inserción manual\n"
            << "  -init random <s> Genera s claves aleatorias\n"
            << "  -init file <s> <f> Lee s claves del fichero f\n";
}

// ─── Parseo de argumentos ─────────────────────────────────────────────────────
struct Opciones {
  std::string tipoAB;   // "abe" | "abb"
  std::string init;     // "manual" | "random" | "file"
  int         nElem = 0;
  std::string fichero;
};

Opciones parsearArgs(int argc, char* argv[]) {
  Opciones op;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-ab" && i + 1 < argc) {
      op.tipoAB = argv[++i];
    } else if (arg == "-init" && i + 1 < argc) {
      op.init = argv[++i];
      if (op.init == "random" && i + 1 < argc) {
        op.nElem = std::atoi(argv[++i]);
      } else if (op.init == "file" && i + 2 < argc) {
        op.nElem  = std::atoi(argv[++i]);
        op.fichero = argv[++i];
      }
    }
  }
  return op;
}

// ─── Inicialización del árbol ─────────────────────────────────────────────────
// Devuelve el vector de claves que quedaron efectivamente en el árbol
std::vector<Nif> inicializar(AB<Nif>* arbol, const Opciones& op) {
  std::vector<Nif> claves;

  if (op.init == "manual") {
    return claves;   // Vacío; el usuario inserta desde el menú
  }

  if (op.init == "random") {
    srand(time(nullptr));
    int insertados = 0;
    while (insertados < op.nElem) {
      Nif nif(rand() % 100000000L);
      if (arbol->insertar(nif)) { claves.push_back(nif); ++insertados; }
    }
    std::cout << "Árbol inicializado con " << op.nElem << " claves aleatorias.\n";

  } else if (op.init == "file") {
    std::ifstream fs(op.fichero);
    if (!fs) {
      std::cerr << "Error: no se puede abrir el fichero '" << op.fichero << "'\n";
      return claves;
    }
    int insertados = 0;
    Nif nif;
    while (insertados < op.nElem && fs >> nif) {
      if (arbol->insertar(nif)) { claves.push_back(nif); ++insertados; }
    }
    std::cout << "Árbol inicializado con " << insertados << " claves del fichero.\n";
  }

  return claves;
}

// ─── Menú ─────────────────────────────────────────────────────────────────────
void menu(AB<Nif>* arbol, const std::vector<Nif>& clavesArbol) {
  int opcion = -1;
  do {
    std::cout << "\n┌──────────────────────────────────────┐\n"
              << "│  [0] Salir                           │\n"
              << "│  [1] Insertar clave                  │\n"
              << "│  [2] Buscar clave                    │\n"
              << "│  [3] Mostrar inorden                 │\n"
              << "│  [4] Benchmark: 10 búsquedas         │\n"
              << "└──────────────────────────────────────┘\n"
              << "Opción: ";
    std::cin >> opcion;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cerr << "Entrada inválida.\n";
      continue;
    }

    switch (opcion) {
      case 0:
        std::cout << "Saliendo...\n";
        break;

      case 1: {
        Nif nif;
        std::cout << "Introduce el número del NIF: ";
        std::cin >> nif;
        if (arbol->insertar(nif)) {
          std::cout << "Clave " << nif << " insertada correctamente.\n";
        } else {
          std::cout << "La clave " << nif << " ya existe en el árbol.\n";
        }
        std::cout << "\n" << *arbol;
        break;
      }

      case 2: {
        Nif nif;
        std::cout << "Introduce el número del NIF a buscar: ";
        std::cin >> nif;
        int comparaciones = 0;
        if (arbol->buscarConContador(nif, comparaciones)) {
          std::cout << "Clave " << nif << " ENCONTRADA en el árbol.\n";
        } else {
          std::cout << "Clave " << nif << " NO encontrada.\n";
        }
        std::cout << "Comparaciones realizadas: " << comparaciones << "\n";
        break;
      }

      case 3:
        std::cout << "Recorrido inorden: ";
        arbol->inorden();
        break;

      case 4: {
        // Benchmark: 10 búsquedas de claves garantizadas en el árbol
        const int N_BUSQUEDAS = 10;

        if (clavesArbol.empty()) {
          std::cerr << "El árbol está vacío o fue inicializado en modo manual.\n"
                    << "Inserta claves primero con la opción [1].\n";
          break;
        }

        // Elegir 10 índices equidistantes del vector de claves
        // (cubre principio, mitad y final → variedad de profundidades)
        int total = static_cast<int>(clavesArbol.size());
        int paso  = std::max(1, total / N_BUSQUEDAS);

        std::cout << "\n── Benchmark: 10 búsquedas de claves presentes ──\n";
        std::cout << "  #   │ Clave          │ Comparaciones\n";
        std::cout << "──────┼────────────────┼───────────────\n";

        int totalComp = 0;
        for (int i = 0; i < N_BUSQUEDAS; ++i) {
          int idx = std::min(i * paso, total - 1);
          Nif clave = clavesArbol[idx];
          int comp = 0;
          arbol->buscarConContador(clave, comp);
          totalComp += comp;
          std::cout << "  " << std::setw(2) << (i + 1) << "  │ "
                    << std::setw(14) << std::left << clave << " │ "
                    << std::right << comp << "\n";
        }

        std::cout << "──────┴────────────────┴───────────────\n";
        std::cout << "  Media de comparaciones: "
                  << static_cast<double>(totalComp) / N_BUSQUEDAS << "\n";
        break;
      }

      default:
        std::cerr << "Opción no válida.\n";
    }

  } while (opcion != 0);
}

// ─── Main ─────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
  if (argc < 3) { uso(argv[0]); return 1; }

  Opciones op = parsearArgs(argc, argv);

  if (op.tipoAB.empty() || op.init.empty()) { uso(argv[0]); return 1; }
  if (op.tipoAB != "abe" && op.tipoAB != "abb") {
    std::cerr << "Error: tipo de árbol desconocido '" << op.tipoAB << "'\n";
    uso(argv[0]); return 1;
  }
  if (op.init != "manual" && op.init != "random" && op.init != "file") {
    std::cerr << "Error: modo de inicialización desconocido '" << op.init << "'\n";
    uso(argv[0]); return 1;
  }

  // Crear el árbol según el tipo elegido
  AB<Nif>* arbol = nullptr;
  if (op.tipoAB == "abe") {
    arbol = new ABE<Nif>();
    std::cout << "Árbol Binario Equilibrado (ABE)\n";
  } else {
    arbol = new ABB<Nif>();
    std::cout << "Árbol Binario de Búsqueda (ABB)\n";
  }

  // Inicializar con los datos indicados
  std::vector<Nif> claves = inicializar(arbol, op);

  // Mostrar árbol inicial
  std::cout << "\nEstado inicial:\n" << *arbol;

  // Ejecutar menú interactivo
  menu(arbol, claves);

  delete arbol;
  return 0;
}
