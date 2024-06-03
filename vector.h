#pragma once
#include <stddef.h>
#include "exception.h"

template<class T> class Vector {
public:
    Vector() = default;
    Vector(const Vector& vec) = delete;
    Vector& operator=(const Vector& vec) = delete;
    Vector(const long length) {
        if (length <= 0) { throw InvalidInputException(); }
        this->length = length;
        vec = new T[this->length];
        length_set = true;
    }
    ~Vector() {
        if (vec != nullptr) { delete[] vec; }
    }
    void set_length(const long length) {
        if (length_set == true) { return; }
        if (length <= 0) { throw InvalidInputException(); }
        this->length = length;
        vec = new T[this->length];
        length_set = true;
    }
    T& operator[](const long index) {
        if (index < 0 || index >= length) { throw IndexOutOfBoundsException(); }
        return vec[index];
    }
    long get_length() const { return length; }
private:
    long length = 0;
    T *vec = nullptr;
    bool length_set = false;
};
