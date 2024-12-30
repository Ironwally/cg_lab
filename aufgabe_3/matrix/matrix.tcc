// Aufgabe 3 - matrix.tcc implementieren

#include <cassert>

#include "math.h"

template <class FLOAT, size_t N>
SquareMatrix<FLOAT, N>::SquareMatrix(): SquareMatrix({}) {}

template <class FLOAT, size_t N>
SquareMatrix<FLOAT, N>::SquareMatrix(std::initializer_list<Vector<FLOAT, N>> values) {
    auto iterator = values.begin();
    for (size_t c = 0; c < N; ++c) {
        //matrix[c] = (iterator != values.end()) ? *iterator++ : Vector<FLOAT, N>(); if other doesn't work
        matrix[c] = (iterator != values.end()) ? *iterator++ : (c > 0 ? matrix[c - 1] : Vector<FLOAT, N>());
    }
}

// returns the product of two matices
template <class FLOAT, size_t N>
SquareMatrix<FLOAT, N> operator*(const SquareMatrix<FLOAT, N> factor1, const SquareMatrix<FLOAT, N> factor2) {
    SquareMatrix<FLOAT, N> product;
    for (size_t r = 0u; r < N; ++r) {  // for each row in product
        for (size_t c = 0u; c < N; ++c) {  // for each column in product
            product[c][r] = 0;
            for (size_t k = 0u; k < N; ++k) {  // for each element in the row and column
                product[c][r] += factor1[k][r] * factor2[c][k];
            }
        }
    }
    return product;
}

// returns reference to the i-th column vector
template <class FLOAT, size_t N>
Vector<FLOAT, N> & SquareMatrix<FLOAT, N>::operator[](std::size_t i) {
    return matrix[i];
}

// returns i-th column vector
template <class FLOAT, size_t N>
Vector<FLOAT, N> SquareMatrix<FLOAT, N>::operator[](std::size_t i) const {
    return matrix[i];
}

// returns the value at the given row and column
template <class FLOAT, size_t N>
FLOAT SquareMatrix<FLOAT, N>::at(size_t row, size_t column) const {
    return matrix[column][row];
}

// returns the reference value at the given row and column
template <class FLOAT, size_t N>
FLOAT & SquareMatrix<FLOAT, N>::at(size_t row, size_t column) {
    return matrix[column][row];
}

// returns the product of this SquareMatrix and the given vector
template <class FLOAT, size_t N>
Vector<FLOAT,N> SquareMatrix<FLOAT, N>::operator*(const Vector<FLOAT,N> vector) {
    Vector<FLOAT, N> product;
    for (size_t r = 0; r < N; ++r) {  // for each row in matrix
        product[r] = 0;
        for (size_t c = 0; c < N; ++c) { // for each column in matrix and vector
            product[r] += matrix[c][r] * vector[c];
        }
    }
    return product;
}