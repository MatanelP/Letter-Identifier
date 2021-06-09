// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>
#include <fstream>

#define MINIMUM_TO_PRINT 0.1

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

  /**
   * Creates a new matrix with the specified rows and columns.
   * @param rows, int - number of rows.
   * @param cols, int - number of columns.
   */
  Matrix (int rows, int cols);

  /**
   * Creates a new matrix with the 1 row and 1 column.
   */
  Matrix ();

  /**
   * Creates a new matrix witch is identical to the given matrix.
   * @param other, Matrix - another matrix to copies data and values from.
   */
  Matrix (const Matrix &other);

  // Destructor:

  /**
   * freeing up memory allocated for the matrix 1 dim array of floats.
   */
  ~Matrix ();

  // Getters:

  /**
   * @return an int, the number of rows.
   */
  int get_rows () const;

  /**
   * @return an int, the number of columns.
   */
  int get_cols () const;

  // Methods:

  /**
   * Transforms a matrix into its transpose matrix.
   * @return a reference to the Transformed matrix.
   */
  Matrix &transpose ();

  /**
   * Transforms a matrix into a column vector.
   * @return a reference to the Transformed matrix.
   */
  Matrix &vectorize ();

  /**
   * Prints matrix elements.
   */
  void plain_print () const;

  /**
   * Returns a matrix which is the dot product of this matrix and another matrix m:
   * @param other, Matrix - another matrix for the calculation.
   * @return a new matrix which is the dot product.
   */
  Matrix dot (const Matrix &other) const;

  /**
   * @return the Frobenius norm of the matrix.
   */
  float norm () const;

  /**
   * Fills matrix elements from a binary file.
   * @param ifs, ifstream- the input binary file.
   * @param mat
   * @return the given ifs.
   */
  friend std::ifstream &read_binary_file (std::ifstream &ifs, Matrix &mat);

  // Operators:

  /**
   * Matrices addition.
   * @param mat - Matrix, the other matrix to add.
   * @return a new Matrix witch is the sum of the two.
   */
  Matrix operator+ (const Matrix &mat) const;

  /**
   * takes a matrix and changes the current matrix to be equal to it.
   * @param mat - Matrix, the other matrix.
   * @return a reference to the current matrix after the changes.
   */
  Matrix &operator= (const Matrix &mat);

  /**
   * Matrices multiplication.
   * @param mat - Matrix, the other matrix.
   * @return a new Matrix witch is the multiply of the two.
   */
  Matrix operator* (const Matrix &mat) const;

  /**
   * Scalar multiplication on the right.
   * @param c - float, the scalar to multiply with.
   * @return a new Matrix witch is the multiply of the two.
   */
  Matrix operator* (float c) const;

  /**
   * Scalar multiplication on the left.
   * @param c - float, the scalar to multiply with.
   * @param mat - Matrix, the matrix to multiply with.
   * @return a new Matrix witch is the multiply of the two.
   */
  friend Matrix operator* (float c, Matrix &mat);

  /**
   * Matrix addition accumulation.
   * @param mat the other matrix to add to the current one.
   * @return a reference to the current matrix after the changes.
   */
  Matrix &operator+= (const Matrix &mat);

  /**
   * Parenthesis indexing.
   * @param i - int, indicating the requested row.
   * @param j - int, indicating the requested column.
   * @return a reference to the value represented as (i,j) in the matrix.
   */
  float &operator() (int i, int j);

  /**
   * Parenthesis indexing.
   * @param i - int, indicating the requested row.
   * @param j - int, indicating the requested column.
   * @return the value represented as (i,j) in the matrix as a constant.
   */
  float operator() (int i, int j) const;

  /**
   * Brackets indexing.
   * @param i - int, indicating the requested element position in the array.
   * @return a reference to the value represented as _data[i] in the matrix.
   */
  float &operator[] (int i);

  /**
   * Brackets indexing.
   * @param i - int, indicating the requested element position in the array.
   * @return  the value represented as _data[i] in the matrix as a constant.
   */
  float operator[] (int i) const;

  /**
   * Pretty export of the matrix.
   * @param os - ostream, the output stream.
   * @param mat - Matrix, to export.
   * @return ostream, with the representation wanted.
   */
  friend std::ostream &operator<< (std::ostream &os, const Matrix &mat);

 private:
  matrix_dims _dims{};
  float *_data;
  int _size;

};

#endif //MATRIX_H
