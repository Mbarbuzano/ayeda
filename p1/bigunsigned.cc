// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: Números enteros grandes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: /02/2025
// Archivo: bigunsigned.h
// contiene la implementación de los métodos de la clase big unsigned

#include "bigunsigned.h"

// CONSTRUCTORES

BigUnsigned::BigUnsigned(unsigned n) {  // Constructor por defecto
  if (n == 0) {
    number_[0] = 0;
    return;
  }
  while (n > 0) {
    number_.push_back(n % 10);
    n /= 10;
  }
}

BigUnsigned::BigUnsigned(const unsigned char* array) {  // Constructor
  size_t length{std::strlen(reinterpret_cast<const char*>(array))};
  number_.resize(length);
  for (size_t i{0}; i < length; ++i) {
    number_[i] = array[length - i - 1] - '0';
  }
}

BigUnsigned::BigUnsigned(const BigUnsigned& numero) : number_(numero.number_) { }

// OPERADORES

BigUnsigned& BigUnsigned::operator=(
    const BigUnsigned& numero) {  // Operador de asignación
  if (this != &numero) {
    number_ = numero.number_;
  }
  return *this;
}

bool BigUnsigned::operator==(
    const BigUnsigned& numero) const {  // Operador de igualdad
  return number_ == numero.number_;
}

bool BigUnsigned::operator<(
    const BigUnsigned& numero) const {  // Operador menor
  if (number_.size() < numero.number_.size()) return true;
  if (number_.size() == numero.number_.size()) {
    for (size_t i{number_.size()}; i > 0; i-- > 0) {
      if (number_[i] < numero.number_[i]) return true;
      if (number_[i] == numero.number_[i]) continue;
    }
  }
  return false;
}

// Pre-incremento (++x): incrementa y devuelve *this
BigUnsigned& BigUnsigned::operator++() {
  BigUnsigned uno{'1'};
  *this = *this + uno;
  return *this;
}

// Post-incremento (x++): guarda copia, incrementa y devuelve la copia anterior
BigUnsigned BigUnsigned::operator++(int) {
  BigUnsigned temp = *this;  // Guardamos la versión actual
  ++(*this);                 // Llamamos a pre-incremento
  return temp;               // Devolvemos la versión antigua
}

// Pre-decremento (--x): decrementa y devuelve *this
BigUnsigned& BigUnsigned::operator--() {
  BigUnsigned nulo{'0'};
  if (*this == nulo) {
    throw std::underflow_error("No se puede decrementar 0.");
  }
  *this = *this - BigUnsigned(1);
  return *this;
}

// Post-decremento (x--): guarda copia, decrementa y devuelve la copia anterior
BigUnsigned BigUnsigned::operator--(int) {
  BigUnsigned nulo{'0'};
  if (*this == nulo) {
    throw std::underflow_error("No se puede decrementar 0.");
  }
  BigUnsigned temp = *this;  // Guardamos la versión actual
  --(*this);                 // Llamamos a pre-decremento
  return temp;               // Devolvemos la versión antigua
}

BigUnsigned BigUnsigned::operator+(const BigUnsigned& numero) {
  size_t max_size = std::max(number_.size(), numero.number_.size());
  BigUnsigned result;
  result.number_.resize(max_size);
  bool carry{false};
  for (size_t i = 0; i < max_size; ++i) {
    unsigned char digito1 = (i < number_.size()) ? number_[i] : 0;
    unsigned char digito2 = (i < numero.number_.size()) ? numero.number_[i] : 0;

    unsigned char suma = digito1 + digito2 + carry;
    carry = (suma >= 10);           // Si la suma es 10 o más, hay llevada
    result.number_[i] = suma % 10;  // Guardamos solo el dígito de las unidades
  }

  if (carry) result.number_.push_back(1);
  return result;
}

BigUnsigned BigUnsigned::operator-(const BigUnsigned& sustraendo) const {
  BigUnsigned result{*this};
  if (*this < sustraendo)
    throw std::runtime_error("El minuendo es menor que el sustraendo");
  bool carry{0};

  for (size_t i{0}; i < number_.size(); ++i) {
    if (result.number_[i] < sustraendo.number_[i] + carry) {
      result.number_[i] =
          (result.number_[i] + 10) - (sustraendo.number_[i] + carry);
      carry = true;
    } else {
      result.number_[i] -= (sustraendo.number_[i] + carry);
      carry = false;
    }
  }

  while (result.number_.size() > 1 && result.number_.back() == 0) {
    result.number_.pop_back();
  }

  return result;
}

BigUnsigned BigUnsigned::operator*(const BigUnsigned& multiplicador) const {
  BigUnsigned result;
  result.number_.resize(number_.size() + multiplicador.number_.size(),
                        0);  // Tamaño máximo posible

  for (size_t i = 0; i < number_.size(); ++i) {
    unsigned char carry = 0;
    for (size_t j = 0; j < multiplicador.number_.size(); ++j) {
      unsigned int prod = result.number_[i + j] +
                          (number_[i] * multiplicador.number_[j]) + carry;
      result.number_[i + j] = prod % 10;  // Guardamos la unidad
      carry = prod / 10;                  // Llevamos el acarreo
    }
    if (carry > 0) {
      result.number_[i + multiplicador.number_.size()] += carry;
    }
  }

  // Eliminar ceros a la izquierda
  while (result.number_.size() > 1 && result.number_.back() == 0) {
    result.number_.pop_back();
  }

  return result;
}

BigUnsigned BigUnsigned::operator/(const BigUnsigned& divisor) {
  BigUnsigned nulo = '0';
  if (divisor == nulo) {
    throw std::runtime_error("Error: División por cero.");
  }

  BigUnsigned cociente, resto;
  cociente.number_.resize(number_.size());

  for (size_t i = number_.size() - 1; i > 0; --i) {
    resto.number_.insert(resto.number_.begin(),
                         number_[i]);  // Desplazamos el dígito
    while (resto.number_.size() > 1 && resto.number_.back() == 0) {
      resto.number_.pop_back();
    }

    unsigned char factor = 0;
    while (divisor < resto) {
      resto = resto - divisor;
      factor++;
    }
    cociente.number_[i] = factor;
  }

  // Eliminar ceros a la izquierda
  while (cociente.number_.size() > 1 && cociente.number_.back() == 0) {
    cociente.number_.pop_back();
  }

  return cociente;
}

BigUnsigned BigUnsigned::operator%(const BigUnsigned& divisor) const {
  BigUnsigned nulo = '0';
  if (divisor == nulo) {
    throw std::runtime_error("Error: Módulo por cero.");
  }

  BigUnsigned resto;

  for (int i = number_.size() - 1; i >= 0; --i) {
    // Desplazamos el dígito al resto
    resto.number_.insert(resto.number_.begin(), number_[i]);

    // Eliminamos ceros a la izquierda
    while (resto.number_.size() > 1 && resto.number_.back() == 0) {
      resto.number_.pop_back();
    }

    // Restamos el divisor tantas veces como quepa en el resto
    while (divisor < resto) {
      resto = resto - divisor;
    }
  }

  return resto;
}

std::ostream& operator<<(std::ostream& os, const BigUnsigned& numero) {
  if (numero.number().empty()) {
    os << "0\n";
  }
  else {
    for (size_t i{numero.number().size()}; i > 0; i-- > 0) {
      os << static_cast<char>(numero.number()[i] + '0');
    }
  }
  os << "\n";
  return os;
}

std::istream& operator>>(std::istream& is, BigUnsigned& numero) {
  std::string cadena;
  is >> cadena;
  for (const char& a : cadena) {
    if (!isdigit(a)) {
      std::cout << "La entrada sólo puede contener números\n";
      exit(1);
    }
  }
  numero.number().resize(cadena.size());
  for (size_t i{0}; i < cadena.size(); ++i) {
    numero.number()[i] = cadena[cadena.size() - i - 1] - '0';
  }
  return is;
}