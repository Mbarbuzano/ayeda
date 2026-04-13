#pragma once
#include "Sequence.h"
#include <stdexcept>

// Secuencia de tamaño fijo derivada de Sequence<Key>
template <typename Key>
class staticSequence : public Sequence<Key> {
 public:
  explicit staticSequence(unsigned sz) : size_(sz), data_(new Key[sz]) {}

  staticSequence(const staticSequence& other) : size_(other.size_), data_(new Key[other.size_]) {
    for (unsigned i = 0; i < size_; ++i) data_[i] = other.data_[i];
  }

  staticSequence& operator=(const staticSequence& other) {
    if (this != &other) {
      delete[] data_;
      size_ = other.size_;
      data_ = new Key[size_];
      for (unsigned i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }
    return *this;
  }

  ~staticSequence() override { delete[] data_; }

  Key  operator[](unsigned i) const override {
    if (i >= size_) throw std::out_of_range("staticSequence: índice fuera de rango");
    return data_[i];
  }

  Key& operator[](unsigned i) override {
    if (i >= size_) throw std::out_of_range("staticSequence: índice fuera de rango");
    return data_[i];
  }

  unsigned size() const override { return size_; }

 private:
  unsigned size_;
  Key*     data_;
};
