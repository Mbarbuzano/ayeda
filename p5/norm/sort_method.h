#pragma once
#include "staticSequence.h"
#include "SortAlgorithms.h"

// ─────────────────────────────────────────────────────────
//  Clase base abstracta SortMethod<Key>
// ─────────────────────────────────────────────────────────
template <typename Key>
class SortMethod {
 public:
  SortMethod(staticSequence<Key>& seq, bool trace)
    : seq_(seq), trace_(trace) {}

  virtual ~SortMethod() = default;

  virtual void Sort() = 0;

 protected:
  staticSequence<Key>& seq_;
  bool                 trace_;
};

// ─────────────────────────────────────────────────────────
//  a) Selección
// ─────────────────────────────────────────────────────────
template <typename Key>
class Selection : public SortMethod<Key> {
 public:
  using SortMethod<Key>::SortMethod;
  void Sort() override {
    selectionSort(this->seq_, this->seq_.size(), this->trace_);
  }
};

// ─────────────────────────────────────────────────────────
//  b) Burbuja
// ─────────────────────────────────────────────────────────
template <typename Key>
class Bubble : public SortMethod<Key> {
 public:
  using SortMethod<Key>::SortMethod;
  void Sort() override {
    bubbleSort(this->seq_, this->seq_.size(), this->trace_);
  }
};

// ─────────────────────────────────────────────────────────
//  c) MergeSort
// ─────────────────────────────────────────────────────────
template <typename Key>
class MergeSort : public SortMethod<Key> {
 public:
  using SortMethod<Key>::SortMethod;
  void Sort() override {
    if (this->seq_.size() == 0) return;
    mergeSort(this->seq_, 0, this->seq_.size() - 1, this->trace_);
  }
};

// ─────────────────────────────────────────────────────────
//  d) HeapSort
// ─────────────────────────────────────────────────────────
template <typename Key>
class HeapSort : public SortMethod<Key> {
 public:
  using SortMethod<Key>::SortMethod;
  void Sort() override {
    heapSort(this->seq_, this->seq_.size(), this->trace_);
  }
};

// ─────────────────────────────────────────────────────────
//  e) Shell (Incrementos Decrecientes)
//     El parámetro alfa se pasa en la construcción.
// ─────────────────────────────────────────────────────────
template <typename Key>
class Shell : public SortMethod<Key> {
 public:
  Shell(staticSequence<Key>& seq, bool trace, double alfa)
    : SortMethod<Key>(seq, trace), alfa_(alfa) {}

  void Sort() override {
    shellSort(this->seq_, this->seq_.size(), alfa_, this->trace_);
  }

 private:
  double alfa_;
};
