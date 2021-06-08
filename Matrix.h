// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::swap;

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims {
  int rows, cols;
} matrix_dims;

class Matrix {

 public:

  // Constructors:
  Matrix (int rows, int cols);

  Matrix ();

  Matrix (const Matrix &other);

  // Destructor:
  ~Matrix ();

  // Getters:
  int get_rows () const;

  int get_cols () const;

  // Methods:
  Matrix &transpose ();

  Matrix &vectorize ();

  void plain_print ();

  Matrix dot (const Matrix &other);

  float norm ();

  friend void read_binary_file (std::ifstream &ifs, Matrix &mat);

  // Operators:
  Matrix &operator+ (const Matrix &mat);

  Matrix &operator= (const Matrix &mat);

  Matrix &operator* (const Matrix &mat);

  Matrix &operator* (float c);

  friend Matrix &operator* (float c, Matrix &mat);

  Matrix &operator+= (const Matrix &mat);

  float &operator() (int i, int j);

  float operator() (int i, int j) const;

  float &operator[] (int i);

  float operator[] (int i) const;

  friend float assign_value (Matrix &mat, int index, float value);

  friend std::ostream &operator<< (std::ostream &os, Matrix &mat);

 private:
  matrix_dims *_dims;
  float *_data;

};

#endif //MATRIX_H
