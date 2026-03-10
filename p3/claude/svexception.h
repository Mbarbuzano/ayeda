// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3: Hormiga de Langton Evolucionada
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 11/3/2026
// Archivo: svexception.h
// Contenido: declaración de la clase svexception
// esta clase es un manejador de excepciones de la clase slidingvector

#ifndef SVEXCEPTION_H
#define SVEXCEPTION_H

#include <exception>
#include <string>

class SVException : public std::exception {
 public:
  SVException(const std::string& message);

  const char* what() const noexcept override;

 private:
  std::string message_;
};

#endif