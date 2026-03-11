// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: simulator.h
// Contenido: declaración de Simulator

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "ant.h"
#include "tape.h"

class Simulator {
 public:
  Simulator(std::unique_ptr<Tape> tape);
  ~Simulator();

  void AddAnt(Ant* ant);
  void SetCell(int x, int y, int color);  // inicializa celdas no blancas

  // Ejecuta un paso
  void Step();

  // Bucle interactivo: avanza un paso por cada Enter
  // Para cuando no quedan hormigas o el usuario interrumpe
  void Run();

  // Guarda el estado actual en fichero con el formato del guión
  void Save(const std::string& filename) const;

  void Print(std::ostream& os = std::cout) const;

  bool HasLivingAnts() const;

 private:
  std::unique_ptr<Tape> tape_;
  std::vector<Ant*> ants_;
  int step_count_;

  void RemoveDeadAnts();
  void ReproduceAnts();   // genera nueva hormiga si dos del mismo tipo coinciden
  void PrintAntInfo(std::ostream& os) const;
};

#endif
