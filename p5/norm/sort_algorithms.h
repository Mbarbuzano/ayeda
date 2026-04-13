// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 5: Ordenación
// Autor: Marcos Barbuzano Socorro
// Correo: alu0101629469@ull.edu.es
// Fecha: 15/4/2026
// Archivo: sort_algorithms.h
// Contenido: declaración de la clase sort_algorithms


#pragma once
#include "static_sequence.h"
#include <iostream>
#include <cmath>   // pow()

// ─────────────────────────────────────────────────────────
//  Utilidad: imprimir la secuencia (para traza)
// ─────────────────────────────────────────────────────────
template <typename Key>
void printSequence(const staticSequence<Key>& seq) {
  for (unsigned i = 0; i < seq.size(); ++i)
    std::cout << seq[i] << ' ';
  std::cout << '\n';
}

// ─────────────────────────────────────────────────────────
//  a) SELECCIÓN  O(n²)
//     En cada pasada selecciona el mínimo del subarray
//     pendiente y lo lleva a su posición definitiva.
// ─────────────────────────────────────────────────────────
template <typename Key>
void selectionSort(staticSequence<Key>& seq, unsigned size, bool trace = false) {
  for (unsigned i = 0; i < size - 1; ++i) {
    unsigned minIdx = i;
    for (unsigned j = i + 1; j < size; ++j)
      if (seq[j] < seq[minIdx]) minIdx = j;

    if (minIdx != i) {
      Key tmp     = seq[i];
      seq[i]      = seq[minIdx];
      seq[minIdx] = tmp;
    }

    if (trace) { std::cout << "  Iter " << i + 1 << ": "; printSequence(seq); }
  }
}

// ─────────────────────────────────────────────────────────
//  b) BURBUJA  O(n²)
//     Hace flotar el mayor elemento hacia el final en cada
//     pasada; se detiene anticipadamente si no hay cambios.
// ─────────────────────────────────────────────────────────
template <typename Key>
void bubbleSort(staticSequence<Key>& seq, unsigned size, bool trace = false) {
  for (unsigned i = 0; i < size - 1; ++i) {
    bool swapped = false;
    for (unsigned j = 0; j < size - i - 1; ++j) {
      if (seq[j] > seq[j + 1]) {
        Key tmp    = seq[j];
        seq[j]     = seq[j + 1];
        seq[j + 1] = tmp;
        swapped    = true;
      }
    }
    if (trace) { std::cout << "  Iter " << i + 1 << ": "; printSequence(seq); }
    if (!swapped) break;  // ya ordenado
  }
}

// ─────────────────────────────────────────────────────────
//  c) MERGESORT  O(n log n)
//     Divide y vencerás: divide la secuencia en mitades,
//     ordena recursivamente y combina (merge).
// ─────────────────────────────────────────────────────────
template <typename Key>
void merge(staticSequence<Key>& seq, unsigned ini, unsigned mid, unsigned fin) {
  unsigned n1 = mid - ini + 1;
  unsigned n2 = fin - mid;

  // Arrays temporales
  Key* L = new Key[n1];
  Key* R = new Key[n2];

  for (unsigned i = 0; i < n1; ++i) L[i] = seq[ini + i];
  for (unsigned j = 0; j < n2; ++j) R[j] = seq[mid + 1 + j];

  unsigned i = 0, j = 0, k = ini;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) seq[k++] = L[i++];
    else               seq[k++] = R[j++];
  }
  while (i < n1) seq[k++] = L[i++];
  while (j < n2) seq[k++] = R[j++];

  delete[] L;
  delete[] R;
}

template <typename Key>
void mergeSortRec(staticSequence<Key>& seq, unsigned ini, unsigned fin, bool trace) {
  if (ini >= fin) return;
  unsigned mid = (ini + fin) / 2;
  mergeSortRec(seq, ini,     mid, trace);
  mergeSortRec(seq, mid + 1, fin, trace);
  merge(seq, ini, mid, fin);
  if (trace) { std::cout << "  Merge [" << ini << "," << fin << "]: "; printSequence(seq); }
}

template <typename Key>
void mergeSort(staticSequence<Key>& seq, unsigned ini, unsigned fin, bool trace = false) {
  mergeSortRec(seq, ini, fin, trace);
}

// ─────────────────────────────────────────────────────────
//  d) HEAPSORT  O(n log n)
//     Construye un max-heap y extrae elementos de mayor
//     a menor colocándolos al final de la secuencia.
// ─────────────────────────────────────────────────────────
template <typename Key>
void heapify(staticSequence<Key>& seq, unsigned size, unsigned root) {
  unsigned largest = root;
  unsigned left    = 2 * root + 1;
  unsigned right   = 2 * root + 2;

  if (left  < size && seq[left]  > seq[largest]) largest = left;
  if (right < size && seq[right] > seq[largest]) largest = right;

  if (largest != root) {
    Key tmp        = seq[root];
    seq[root]      = seq[largest];
    seq[largest]   = tmp;
    heapify(seq, size, largest);
  }
}

template <typename Key>
void heapSort(staticSequence<Key>& seq, unsigned size, bool trace = false) {
  // Construir max-heap
  for (int i = static_cast<int>(size) / 2 - 1; i >= 0; --i)
    heapify(seq, size, static_cast<unsigned>(i));

  // Extraer elementos del heap uno a uno
  for (unsigned i = size - 1; i > 0; --i) {
    Key tmp  = seq[0];
    seq[0]   = seq[i];
    seq[i]   = tmp;
    heapify(seq, i, 0);
    if (trace) { std::cout << "  Iter " << (size - i) << ": "; printSequence(seq); }
  }
}

// ─────────────────────────────────────────────────────────
//  e) SHELL SORT (Incrementos Decrecientes)  O(n^(3/2)) aprox.
//     Generalización del inserción directa: usa incrementos
//     h = alfa^k * n, reduciéndolos hasta h = 1.
//     Parámetro alfa: 0 < alfa < 1 (típico: 0.5 → Shell clásico)
// ─────────────────────────────────────────────────────────
template <typename Key>
void shellSort(staticSequence<Key>& seq, unsigned size, double alfa = 0.5, bool trace = false) {
  // Calcular incremento inicial: mayor h < size generado por alfa
  unsigned h = static_cast<unsigned>(alfa * size);
  if (h == 0) h = 1;

  unsigned iter = 0;
  while (h > 0) {
    // Inserción con paso h
    for (unsigned i = h; i < size; ++i) {
      Key tmp = seq[i];
      int j   = static_cast<int>(i) - static_cast<int>(h);
      while (j >= 0 && seq[static_cast<unsigned>(j)] > tmp) {
        seq[static_cast<unsigned>(j + static_cast<int>(h))] = seq[static_cast<unsigned>(j)];
        j -= static_cast<int>(h);
      }
      seq[static_cast<unsigned>(j + static_cast<int>(h))] = tmp;
    }
    if (trace) {
      std::cout << "  h=" << h << " (iter " << ++iter << "): ";
      printSequence(seq);
    }
    h = static_cast<unsigned>(alfa * h);
  }
}
