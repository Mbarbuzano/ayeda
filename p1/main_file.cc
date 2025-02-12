// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 1: Números enteros grandes
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: /02/2025
// Archivo: main.cc
// Contiene la implementación del flujo del programa

#include "bigunsigned.h"
#include "biginteger.h"

int main() {
    // 📌 1️⃣ Prueba de Constructores
    unsigned char array[5]{9, 8, 7, 6, 5};
    BigUnsigned numero_i(12345);    
    BigUnsigned numero_ii(array);  
    BigUnsigned numero_iii{numero_i};       

    std::cout << "BigUnsigned numero_i: " << numero_i << "\n";
    std::cout << "BigUnsigned numero_ii: " << numero_ii << "\n";
    std::cout << "BigUnsigned numero_iii (copia de numero_i): " << numero_iii << "\n";

    // 📌 2️⃣ Prueba de Asignación
    numero_iii = numero_ii;
    std::cout << "Después de asignar numero_iii = numero_ii, numero_iii: " << numero_iii << "\n";

    // 📌 3️⃣ Prueba de Comparaciones
    std::cout << "¿numero_i == numero_ii? " << (numero_i == numero_ii) << "\n";
    std::cout << "¿numero_i < numero_ii? " << (numero_i < numero_ii) << "\n";

    // 📌 4️⃣ Prueba de Aritmética
    std::cout << "Suma (numero_i + numero_ii): " << (numero_i + numero_ii) << "\n";
    std::cout << "Resta (numero_ii - numero_i): " << (numero_ii - numero_i) << "\n";
    std::cout << "Multiplicación (numero_i * numero_ii): " << (numero_i * numero_ii) << "\n";
    std::cout << "División (numero_ii / numero_i): " << (numero_ii / numero_i) << "\n";
    std::cout << "Módulo (numero_ii % numero_i): " << (numero_ii % numero_i) << "\n";

    // 📌 5️⃣ Prueba de Incremento y Decremento
    std::cout << "Pre-incremento (++numero_i): " << ++numero_i << "\n";
    std::cout << "Post-incremento (numero_i++): " << numero_i++ << "\n";
    std::cout << "Valor de numero_i después de post-incremento: " << numero_i << "\n";

    std::cout << "Pre-decremento (--numero_ii): " << --numero_ii << "\n";
    std::cout << "Post-decremento (numero_ii--): " << numero_ii-- << "\n";
    std::cout << "Valor de numero_ii después de post-decremento: " << numero_ii << "\n";

    // 📌 6️⃣ Prueba de Entrada/Salida con BigInteger
    BigInteger d;
    std::cout << "Introduce un BigInteger: ";
    std::cin >> d;
    std::cout << "Número ingresado: " << d << "\n";

    // 📌 7️⃣ Algoritmo de Euclides para el MCD
    BigInteger uno(252), dos(105);
    std::cout << "MCD de " << uno << " y " << dos << " es: " << mcd(uno, dos) << "\n";

    return 0;
}

