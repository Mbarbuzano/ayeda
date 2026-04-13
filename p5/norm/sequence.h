#pragma once
#include <cstddef>

// Clase base abstracta genérica para secuencias
template <typename Key>
class Sequence {
 public:
  virtual ~Sequence() = default;

  // Acceso por índice (lectura)
  virtual Key  operator[](unsigned i) const = 0;
  // Acceso por índice (escritura)
  virtual Key& operator[](unsigned i)       = 0;

  virtual unsigned size() const = 0;
};
