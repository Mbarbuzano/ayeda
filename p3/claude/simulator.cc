// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: simulator.cc
// Contenido: implementación de la clase simulator

#include "simulator.h"
#include "carnivore_ant.h"
#include <iostream>

Simulator::Simulator(std::unique_ptr<Tape> tape)
  : tape_(std::move(tape)) {}

void Simulator::AddAnt(Ant* ant) {
  ants_.push_back(ant);
}

void Simulator::Step() {
  for (Ant* ant : ants_) {
    if (!ant->IsAlive()) {
      continue;
    }

    // Carnivore necesita acceso a todas las hormigas
    if (auto carnivore = dynamic_cast<CarnivoreAnt*>(ant)) {
      carnivore->Step(*tape_, ants_);
    } else {
      ant->Step(*tape_);
    }
  }

  RemoveDeadAnts();
}

void Simulator::Run(int steps) {
  for (int i = 0; i < steps; ++i) {
    Step();
    Print();
  }
}

void Simulator::Print() const {
  tape_->Print(std::cout);
  std::cout << "\n";
}

void Simulator::RemoveDeadAnts() {
  std::vector<Ant*> alive;

  for (Ant* ant : ants_) {
    if (ant->IsAlive()) {
      alive.push_back(ant);
    } else {
      delete ant;
    }
  }

  ants_ = alive;
}