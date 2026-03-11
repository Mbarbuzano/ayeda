// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: carnivore_ant.h
// Contenido: declaración de CarnivoreAnt
// Se mueve en diagonal. Cuando coincide con otra hormiga en la misma
// celda le roba Voracity% de su TTL. Si el TTL de la víctima llega
// a 0 o menos, muere.

#ifndef CARNIVORE_ANT_H_
#define CARNIVORE_ANT_H_

#include <string>
#include <vector>
#include "ant.h"

class CarnivoreAnt : public Ant {
 public:
  // voracity: porcentaje de TTL que roba (0-100)
  CarnivoreAnt(int x, int y, int direction, int ttl,
               const std::string& gale_rule, int voracity);

  void Step(Tape& tape) override;
  std::string GetType() const override;

  // El simulador llama a esto antes de cada Step para dar acceso
  // a la lista completa de hormigas
  void SetAnts(std::vector<Ant*>* ants);
  int GetVoracity() const { return voracity_; }

 private:
  std::string gale_rule_;
  int voracity_;              // porcentaje (0-100)
  std::vector<Ant*>* ants_;

  void EatAnts();             // roba TTL a las hormigas en la misma celda
};

#endif
