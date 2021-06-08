//
// Created by Matanel on 02/06/2021.
//

#include "Activation.h"

Activation:: Activation (ActivationType act_type)
: _act_type (act_type)
    {

    }

ActivationType Activation::get_activation_type () const
{
  return _act_type;
}

Matrix &Activation::operator() (Matrix const &mat)
{
  auto *new_mat = new Matrix (mat);
  float scalar = 0;

  for (int i = 0; i < mat.get_rows () * mat.get_cols (); ++i)
    {
      if (_act_type == RELU)
        {
          if ((*new_mat)[i] < 0)
            {
              assign_value (*new_mat, i, 0);
            }
        }
      else
        {
          scalar += assign_value (*new_mat, i, std::exp ((*new_mat)[i]));
        }
    }

  if (_act_type == SOFTMAX)
    {
      *new_mat = (1 / scalar) * (*new_mat);
    }

  return *new_mat;
}
