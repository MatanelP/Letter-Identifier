//
// Created by Matanel on 02/06/2021.
//
#include "Matrix.h"

// Constructors:

Matrix::Matrix (int rows, int cols)
{
  _dims = new matrix_dims;
  _dims->rows = rows;
  _dims->cols = cols;
  _data = new float[rows * cols]{0}; //TODO: are all set to 0's?
}

Matrix::Matrix () : Matrix (1, 1)
{}

Matrix::Matrix (const Matrix &other)
{
  _dims = new matrix_dims;
  _dims->cols = other._dims->cols;
  _dims->rows = other._dims->rows;
  _data = new float[_dims->rows * _dims->cols]{0}; //TODO: are all set to 0's?
  for (int i = 0; i < (_dims->rows * _dims->cols); ++i)
    {
      _data[i] = other._data[i];
    }
}
// Destructor:
Matrix::~Matrix ()
{
  delete _dims;
  delete[] _data;
}

// Getters:
int Matrix::get_rows () const
{
  return _dims->rows;
}

int Matrix::get_cols () const
{
  return _dims->cols;
}

// Methods:
Matrix &Matrix::transpose ()
{
  auto *new_array = new float[_dims->rows * _dims->cols];
  for (int i = 0; i < _dims->rows; ++i)
    {
      for (int j = 0; j < _dims->cols; ++j)
        {
          // Index in the original matrix.
          int index1 = i * _dims->cols + j;
          // Index in the transpose matrix.
          int index2 = j * _dims->rows + i;
          new_array[index2] = _data[index1];
        }
    }
  for (int i = 0; i < _dims->rows * _dims->cols; i++)
    {
      _data[i] = new_array[i];
    }
  delete[] new_array;
  swap (_dims->cols, _dims->rows); //todo: can i use swap?
  return *this;
}

Matrix &Matrix::vectorize ()
{
  //todo: make sure you need to concatenate col by col and not wor by row.
//  transpose ();
  _dims->rows *= _dims->cols;
  _dims->cols = 1;
  return *this;
}

void Matrix::plain_print ()
{
  for (int i = 0; i < _dims->cols * _dims->rows; ++i)
    {
      cout << _data[i] << " ";
      if (!((i + 1) % _dims->cols))
        {
          cout << endl;
        }
    }
  cout << endl;
}

Matrix Matrix::dot (const Matrix &other)
{
  //todo: what if other matrix is not the same dims as this matrix?
  Matrix new_matrix (*this);
  for (int i = 0; i < _dims->cols * _dims->rows; ++i)
    {
      new_matrix._data[i] *= other._data[i];
    }
  return new_matrix;
}

float Matrix::norm ()
{
  float norm = 0;
  for (int i = 0; i < _dims->cols * _dims->rows; ++i)
    {
      norm += std::abs (_data[i] * _data[i]);
    }
  return std::sqrt (norm);
}



// Operators:

Matrix &Matrix::operator+ (const Matrix &mat)
{
  //todo: what if the matrices are mismatching in size?
  auto *new_mat = new Matrix (_dims->rows, mat._dims->cols);

  for (int i = 0; i < (_dims->rows * _dims->cols); ++i)
    {
      new_mat->_data[i] = mat._data[i] + _data[i];
    }
  return *new_mat;
}

Matrix &Matrix::operator= (const Matrix &mat)
{
  //todo: self assignment
  //todo: what if the matrices are mismatching in size?
  _dims->cols = mat._dims->cols;
  _dims->rows = mat._dims->rows;

  delete[] _data; //todo: should i do it?
  _data = new float[_dims->rows * _dims->cols];

  for (int i = 0; i < (_dims->rows * _dims->cols); ++i)
    {
      _data[i] = mat._data[i];
    }

  return *this;
}

Matrix &Matrix::operator* (const Matrix &mat)
{
  //todo: what if the matrices are mismatching in dimensions for mul?
  auto *new_mat = new Matrix (_dims->rows, mat._dims->cols);

  for (int i = 0; i < _dims->rows; i++)
    {
      for (int j = 0; j < mat._dims->cols; j++)
        {
          float sum = 0;
          for (int k = 0; k < _dims->cols; k++)
            {
              sum += _data[i * _dims->cols + k]
                     * mat._data[k * mat._dims->cols + j];
            }
          new_mat->_data[i * mat._dims->cols + j] = sum;
        }
    }

  return *new_mat;
}

Matrix &Matrix::operator* (const float c)
{
  //todo: what if the matrices are mismatching in dimensions for mul?
  auto *new_mat = new Matrix (_dims->rows, _dims->cols);

  for (int i = 0; i < (_dims->rows * _dims->cols); ++i)
    {
      new_mat->_data[i] = _data[i] * c;
    }
  return *new_mat;
}

Matrix &Matrix::operator+= (const Matrix &mat)
{
  //todo: what if the matrices are mismatching in dimensions for mul?
  for (int i = 0; i < (_dims->rows * _dims->cols); ++i)
    {
      _data[i] += mat._data[i];
    }
  return *this;
}

float &Matrix::operator() (int i, int j)
{
  //todo: what about out of bounds errors?
  return _data[(i) * _dims->cols + j];
}

float Matrix::operator() (int i, int j) const
{
  //todo: what about out of bounds errors?
  return _data[(i) * _dims->cols + j];
}

float &Matrix::operator[] (int i)
{
  //todo: what about out of bounds errors?
  return _data[i];
}

float Matrix::operator[] (int i) const
{
  //todo: what about out of bounds errors?
  return _data[i];
}

void read_binary_file (std::ifstream &ifs, Matrix &mat)
{
  ifs.seekg (0, std::ifstream::end);
  auto mat_byte_size = mat.get_cols () * mat.get_rows () * sizeof (float);
  if ((size_t) ifs.tellg () != mat_byte_size)
    {
//      TODO: make sure it is the right kind of error, also, what is
//       th file is larger then the matrix
      ifs.close ();
      throw std::invalid_argument{
          "The given file and matrix are not matching in size!"};
    }
  ifs.seekg (0, std::ifstream::beg);
  ifs.read ((char *) mat._data, (long) mat_byte_size);
}

Matrix &operator* (const float c, Matrix &mat)
{
  //todo: what if the matrices are mismatching in dimensions for mul?
  return mat * c;
}

std::ostream &operator<< (std::ostream &os, Matrix &mat)
{
  for (int i = 1; i <= mat._dims->rows; i++)
    {
      for (int j = 1; j <= mat._dims->cols; j++)
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

float assign_value (Matrix &mat, int index, float const value)
{
  //todo: what about out of bounds errors?
  mat._data[index] = value;
  return value;
}