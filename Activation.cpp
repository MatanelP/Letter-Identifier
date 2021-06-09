//
// Created by Matanel on 02/06/2021.
//

#include "Activation.h"

/**
 * Creates a new Activation.
 * @param act_type - ActivationType, what kind of function will run.
 */
Activation::Activation (ActivationType act_type)
    : _act_type (act_type)
{}

/**
 * @return the ActivationType as in RELU or SOFTMAX
 */
ActivationType Activation::get_activation_type () const
{
  return _act_type;
}

/**
 * Apply the function on the given matrix.
 * @param mat = Matrix, the current matrix to act on.
 * @return a new matrix, the result of the function on the input matrix.
 */
Matrix Activation::operator() (Matrix const &mat) const
{
  Matrix new_mat (mat);
  float scalar = 0;
  for (int i = 0; i < mat.get_rows () * mat.get_cols (); ++i)
    {
      if (_act_type == RELU)
        {
          if (new_mat[i] < 0)
            {
              new_mat[i] = 0;
            }
        }
      else
        {
          new_mat[i] = std::exp (new_mat[i]);
          scalar += new_mat[i];
        }
    }
  if (_act_type == SOFTMAX)
    {
      return (1 / scalar) * (new_mat);
    }
  return new_mat;
}
