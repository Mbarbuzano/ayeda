// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: svexception.cc
// Contenido: implementación de la clase slidingvector

#include "svexception.h"

SVException::SVException(const std::string& message)
    : message_(message) {}

const char* SVException::what() const noexcept {
  return message_.c_str();
}