// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: Números enteros grandes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: /02/2025
// Archivo: biginteger.cc
// contiene la implementación de los métodos de la clase big integer

#include "biginteger.h"

#include <cstdlib>  // Para std::abs

// Constructor desde un int
BigInteger::BigInteger(int n) {
  is_negative_ = (n < 0);
  number_ = BigUnsigned(std::abs(n));
}

// Constructor desde BigUnsigned
BigInteger::BigInteger(const BigUnsigned& num, bool negative)
    : number_(num), is_negative_(negative) {}

// Operador de asignación
BigInteger& BigInteger::operator=(const BigInteger& other) {
  number_ = other.number_;
  is_negative_ = other.is_negative_;
  return *this;
}

// Operador de igualdad
bool BigInteger::operator==(const BigInteger& other) const {
  return (is_negative_ == other.is_negative_ && number_ == other.number_);
}

// Operador menor
bool BigInteger::operator<(const BigInteger& other) const {
  if (is_negative_ != other.is_negative_) return is_negative_;
  return is_negative_ ? (other.number_ < number_) : (number_ < other.number_);
}

// Operador de suma
BigInteger BigInteger::operator+(const BigInteger& other) const {
  // Si ambos son negativos
  if (is_negative_ == other.is_negative_) {
    // Sumar los valores absolutos
    BigUnsigned sum = number() + other.number();
    return BigInteger(sum, is_negative_);  // Mantener el signo
  }
  // Si uno es negativo, el resultado depende de la comparación
  else if (*this < other) {
    // Resta los valores absolutos y conserva el signo del mayor
    BigUnsigned diff = other.number() - number_;
    return BigInteger(diff, other.is_negative_);
  } else {
    // Resta los valores absolutos y conserva el signo del mayor
    BigUnsigned diff = number_ - other.number();
    return BigInteger(diff, is_negative_);
  }
}

// Operador de resta
BigInteger BigInteger::operator-(const BigInteger& other) const {
  // Si ambos tienen el mismo signo
  if (is_negative_ == other.is_negative_) {
    // Si el valor absoluto de *this es mayor o igual, hacemos resta
    if (other < *this) {
      BigUnsigned diff = number_ - other.number_;
      return BigInteger(diff, is_negative_);
    } else {
      BigUnsigned diff = other.number() - number_;
      return BigInteger(diff, !is_negative_);
    }
  }
  // Si los signos son diferentes, efectivamente sumamos los valores absolutos
  else {
    BigUnsigned sum = number() + other.number_;
    return BigInteger(sum, is_negative_);
  }
}

// Multiplicacion
BigInteger BigInteger::operator*(const BigInteger& other) const {
  BigUnsigned product = number_ * other.number();
  // El signo es negativo si solo uno de los dos números es negativo
  bool result_sign = (is_negative_ != other.is_negative_);
  return BigInteger(product, result_sign);
}

// División
BigInteger BigInteger::operator/(const BigInteger& other) const {
  BigUnsigned nulo{'0'};
  if (other.number() == nulo) {
    throw std::invalid_argument("Error: División por cero.");
  }

  BigUnsigned quotient = number() / other.number();
  // El signo del resultado es negativo si solo uno de los dos números es
  // negativo
  bool result_sign = (is_negative_ != other.is_negative_);
  return BigInteger(quotient, result_sign);
}

// Operador de módulo
BigInteger BigInteger::operator%(const BigInteger& other) const {
  BigUnsigned nulo{'0'};
  if (other.number() == nulo) {
    throw std::invalid_argument("Error: División por cero.");
  }

  BigUnsigned remainder = number_ % other.number();
  // El signo del módulo sigue el signo del dividendo (este)
  return BigInteger(remainder, is_negative_);
}

// Operador de pre-incremento (++x)
BigInteger& BigInteger::operator++() {
  *this = *this + BigInteger(1);
  return *this;
}

// Operador de post-incremento (x++)
BigInteger BigInteger::operator++(int) {
  BigInteger temp = *this;
  ++(*this);
  return temp;
}

// Operador de pre-decremento (--x)
BigInteger& BigInteger::operator--() {
  *this = *this - BigInteger(1);
  return *this;
}

// Operador de post-decremento (x--)
BigInteger BigInteger::operator--(int) {
  BigInteger temp = *this;
  --(*this);
  return temp;
}

// Operador de flujo de salida
std::ostream& operator<<(std::ostream& os, const BigInteger& num) {
  if (num.is_negative()) os << "-";
  os << num.number();
  return os;
}

std::istream& operator>>(std::istream& is, BigInteger& num) {
  std::string input;
  is >> input;

  // Determinar si el número es negativo
  if (input[0] == '-') {
    num.SetNeg(true);  // Usar setter para asignar el signo
  } else {
    num.SetNeg(false);
  }

  // Crear un BigUnsigned a partir de los dígitos (ignorando el signo)
  BigUnsigned temp;  // Temporalmente creamos un BigUnsigned
  for (size_t i = (num.is_negative() ? 1 : 0); i < input.size(); ++i) {
    if (input[i] < '0' || input[i] > '9') {
      throw std::invalid_argument(
          "Entrada inválida: solo se permiten números.");
    }
    temp.number().push_back(input[i] -
                            '0');  // Convertir char a número y agregarlo
  }

  // Asignamos el BigUnsigned al número
  num.number() = temp;

  return is;
}

BigInteger mcd(const BigInteger& uno, const BigInteger& dos) {
  return (dos == BigInteger(0)) ? uno : mcd(dos, uno % dos);
}
