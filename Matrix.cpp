//
// Created by Matanel on 02/06/2021.
//
#include "Matrix.h"


// Constructors:
/**
 * Creates a new matrix with the specified rows and columns.
 * @param rows, int - number of rows.
 * @param cols, int - number of columns.
 */
Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
    {
      std::cerr << BAD_PARAMETERS_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  _dims.rows = rows;
  _dims.cols = cols;
  _size = _dims.rows * _dims.cols;
  _data = new (std::nothrow) float[rows * cols]{0};
  if (_data == nullptr)
    {
      std::cerr << ALLOC_FAIL_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
}

/**
 * Creates a new matrix with the 1 row and 1 column.
 */
Matrix::Matrix () : Matrix (1, 1)
{}

/**
 * Creates a new matrix witch is identical to the given matrix.
 * @param other, Matrix - another matrix to copies data and values from.
 */
Matrix::Matrix (const Matrix &other)
{
  _dims.cols = other._dims.cols;
  _dims.rows = other._dims.rows;
  _size = _dims.rows * _dims.cols;
  _data = new (std::nothrow) float[_size]{0};
  if (_data == nullptr)
    {
      std::cerr << ALLOC_FAIL_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  for (int i = 0; i < (_dims.rows * _dims.cols); ++i)
    {
      _data[i] = other._data[i];
    }
}

// Destructor:
/**
 * freeing up memory allocated for the matrix 1 dim array of floats.
 */
Matrix::~Matrix ()
{
  delete[] _data;
}

// Getters:

/**
 * @return an int, the number of rows.
 */
int Matrix::get_rows () const
{
  return _dims.rows;
}

/**
 * @return an int, the number of columns.
 */
int Matrix::get_cols () const
{
  return _dims.cols;
}

// Methods:

/**
 * Transforms a matrix into its transpose matrix.
 * @return a reference to the Transformed matrix.
 */
Matrix &Matrix::transpose ()
{
  auto *new_array = new (std::nothrow) float[_size];
  if (new_array == nullptr)
    {
      std::cerr << ALLOC_FAIL_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }

  for (int i = 0; i < _dims.rows; ++i)
    {
      for (int j = 0; j < _dims.cols; ++j)
        {
          // Index in the original matrix.
          int index1 = i * _dims.cols + j;
          // Index in the transpose matrix.
          int index2 = j * _dims.rows + i;
          new_array[index2] = _data[index1];
        }
    }
  delete[] _data;
  _data = new_array;
  swap (_dims.cols, _dims.rows);
  return *this;
}

/**
 * Transforms a matrix into a column vector.
 * @return a reference to the Transformed matrix.
 */
Matrix &Matrix::vectorize ()
{
  _dims.rows *= _dims.cols;
  _dims.cols = 1;
  return *this;
}

/**
 * Prints matrix elements.
 */
void Matrix::plain_print () const
{
  for (int i = 0; i < _size; ++i)
    {
      cout << _data[i] << " ";
      if (!((i + 1) % _dims.cols))
        {
          cout << endl;
        }
    }
  cout << endl;
}

/**
 * Returns a matrix which is the dot product of this matrix and another.
 * @param other, Matrix - another matrix for the calculation.
 * @return a new matrix which is the dot product.
 */
Matrix Matrix::dot (const Matrix &other) const
{
  if (other._dims.cols != _dims.cols || other._dims.rows != _dims.rows)
    {
      std::cerr << MISMATCHING_MATRICES_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  Matrix new_matrix (*this);
  for (int i = 0; i < _size; ++i)
    {
      new_matrix._data[i] *= other._data[i];
    }
  return new_matrix;
}

/**
 * @return the Frobenius norm of the matrix.
 */
float Matrix::norm () const
{
  float norm = 0;
  for (int i = 0; i < _size; ++i)
    {
      norm += std::abs (_data[i] * _data[i]);
    }
  return std::sqrt (norm);
}

/**
 * Fills matrix elements from a binary file.
 * @param ifs, ifstream- the input binary file.
 * @param mat
 * @return the given ifs.
 */
std::ifstream &read_binary_file (std::ifstream &ifs, Matrix &mat)
{
  ifs.seekg (0, std::ifstream::end);
  auto mat_byte_size = mat._size * sizeof (float);
  if ((size_t) ifs.tellg () < mat_byte_size)
    {
      ifs.close ();
      std::cerr << MISMATCHING_MATRICES_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  ifs.seekg (0, std::ifstream::beg);
  ifs.read ((char *) mat._data, (long) mat_byte_size);
  return ifs;
}

// Operators:

/**
   * Matrices addition.
   * @param mat - Matrix, the other matrix to add.
   * @return a new Matrix witch is the sum of the two.
   */
Matrix Matrix::operator+ (const Matrix &mat) const
{
  if (mat._dims.cols != _dims.cols || mat._dims.rows != _dims.rows)
    {
      std::cerr << MISMATCHING_MATRICES_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  Matrix new_mat (_dims.rows, mat._dims.cols);
  for (int i = 0; i < _size; ++i)
    {
      new_mat._data[i] = mat._data[i] + _data[i];
    }
  return new_mat;
}

/**
  * takes a matrix and changes the current matrix to be equal to it.
  * @param mat - Matrix, the other matrix.
  * @return a reference to the current matrix after the changes.
  */
Matrix &Matrix::operator= (const Matrix &mat)
{
  if (this == &mat)
    {
      return *this;
    }

  _dims.cols = mat._dims.cols;
  _dims.rows = mat._dims.rows;
  _size = _dims.rows * _dims.cols;

  delete[] _data;
  _data = new float[_size];

  for (int i = 0; i < _size; ++i)
    {
      _data[i] = mat._data[i];
    }

  return *this;
}

/**
  * Matrices multiplication.
  * @param mat - Matrix, the other matrix.
  * @return a new Matrix witch is the multiply of the two.
  */
Matrix Matrix::operator* (const Matrix &mat) const
{
  if (mat._dims.rows != _dims.cols)
    {
      std::cerr << MISMATCHING_MATRICES_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }

  Matrix new_mat (_dims.rows, mat._dims.cols);
  for (int i = 0; i < _dims.rows; i++)
    {
      for (int j = 0; j < mat._dims.cols; j++)
        {
          float sum = 0;
          for (int k = 0; k < _dims.cols; k++)
            {
              sum += _data[i * _dims.cols + k]
                     * mat._data[k * mat._dims.cols + j];
            }
          new_mat._data[i * mat._dims.cols + j] = sum;
        }
    }

  return new_mat;
}

/**
   * Scalar multiplication on the right.
   * @param c - float, the scalar to multiply with.
   * @return a new Matrix witch is the multiply of the two.
   */
Matrix Matrix::operator* (const float c) const
{
  Matrix new_mat (_dims.rows, _dims.cols);

  for (int i = 0; i < _size; ++i)
    {
      new_mat._data[i] = _data[i] * c;
    }
  return new_mat;
}

/**
 * Scalar multiplication on the left.
 * @param c - float, the scalar to multiply with.
 * @param mat - Matrix, the matrix to multiply with.
 * @return a new Matrix witch is the multiply of the two.
 */
Matrix operator* (const float c, Matrix &mat)
{
  return mat * c;
}

/**
 * Matrix addition accumulation.
 * @param mat the other matrix to add to the current one.
 * @return a reference to the current matrix after the changes.
 */
Matrix &Matrix::operator+= (const Matrix &mat)
{
  if (mat._dims.cols != _dims.cols || mat._dims.rows != _dims.rows)
    {
      std::cerr << MISMATCHING_MATRICES_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  for (int i = 0; i < _size; ++i)
    {
      _data[i] += mat._data[i];
    }
  return *this;
}

/**
 * Parenthesis indexing.
 * @param i - int, indicating the requested row.
 * @param j - int, indicating the requested column.
 * @return a reference to the value represented as (i,j) in the matrix.
 */
float &Matrix::operator() (int i, int j)
{
  if (i * _dims.cols + j < 0 || i * _dims.cols + j >= _size)
    {
      std::cerr << OUT_OF_BOUND_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  return _data[i * _dims.cols + j];
}

/**
   * Parenthesis indexing.
   * @param i - int, indicating the requested row.
   * @param j - int, indicating the requested column.
   * @return the value represented as (i,j) in the matrix as a constant.
   */
float Matrix::operator() (int i, int j) const
{
  if (i * _dims.cols + j < 0 || i * _dims.cols + j >= _size)
    {
      std::cerr << OUT_OF_BOUND_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  return _data[i * _dims.cols + j];
}

/**
   * Brackets indexing.
   * @param i - int, indicating the requested element position in the array.
   * @return a reference to the value represented as _data[i] in the matrix.
   */
float &Matrix::operator[] (int i)
{
  if (i < 0 || _size <= i)
    {
      std::cerr << OUT_OF_BOUND_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  return _data[i];
}

/**
   * Brackets indexing.
   * @param i - int, indicating the requested element position in the array.
   * @return  the value represented as _data[i] in the matrix as a constant.
   */
float Matrix::operator[] (int i) const
{
  if (i < 0 || _size <= i)
    {
      std::cerr << OUT_OF_BOUND_ERR_MSG << endl;
      exit (EXIT_FAILURE);
    }
  return _data[i];
}

/**
   * Pretty export of the matrix.
   * @param os - ostream, the output stream.
   * @param mat - Matrix, to export.
   * @return ostream, with the representation wanted.
   */
std::ostream &operator<< (std::ostream &os, const Matrix &mat)
{
  for (int i = 0; i < mat._dims.rows; i++)
    {
      for (int j = 0; j < mat._dims.cols; j++)
        {
          if (mat (i, j) >= MINIMUM_TO_PRINT)
            {
              os << "  ";
            }
          else
            {
              os << "**";
            }
        }
      os << endl;
    }

  return os;
}