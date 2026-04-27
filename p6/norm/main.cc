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
void inicializar(AB<Nif>* arbol, const Opciones& op) {
  if (op.init == "manual") {
    // Árbol vacío; el usuario inserta desde el menú
    return;
  }

  if (op.init == "random") {
    srand(time(nullptr));
    int insertados = 0;
    while (insertados < op.nElem) {
      Nif nif(rand() % 100000000L);
      if (arbol->insertar(nif)) ++insertados;
    }
    std::cout << "Árbol inicializado con " << op.nElem << " claves aleatorias.\n";

  } else if (op.init == "file") {
    std::ifstream fs(op.fichero);
    if (!fs) {
      std::cerr << "Error: no se puede abrir el fichero '" << op.fichero << "'\n";
      return;
    }
    int insertados = 0;
    Nif nif;
    while (insertados < op.nElem && fs >> nif) {
      if (arbol->insertar(nif)) ++insertados;
    }
    std::cout << "Árbol inicializado con " << insertados << " claves del fichero.\n";
  }
}

// ─── Menú ─────────────────────────────────────────────────────────────────────
void menu(AB<Nif>* arbol) {
  int opcion = -1;
  do {
    std::cout << "\n┌─────────────────────────┐\n"
              << "│  [0] Salir              │\n"
              << "│  [1] Insertar clave     │\n"
              << "│  [2] Buscar clave       │\n"
              << "│  [3] Mostrar inorden    │\n"
              << "└─────────────────────────┘\n"
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
        // Mostrar árbol por niveles tras cada inserción
        std::cout << "\n" << *arbol;
        break;
      }

      case 2: {
        Nif nif;
        std::cout << "Introduce el número del NIF a buscar: ";
        std::cin >> nif;
        if (arbol->buscar(nif)) {
          std::cout << "Clave " << nif << " ENCONTRADA en el árbol.\n";
        } else {
          std::cout << "Clave " << nif << " NO encontrada.\n";
        }
        break;
      }

      case 3:
        std::cout << "Recorrido inorden: ";
        arbol->inorden();
        break;

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
  inicializar(arbol, op);

  // Mostrar árbol inicial
  std::cout << "\nEstado inicial:\n" << *arbol;

  // Ejecutar menú interactivo
  menu(arbol);

  delete arbol;
  return 0;
}
