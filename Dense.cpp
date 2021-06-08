//
// Created by Matanel on 02/06/2021.
//

#include "Dense.h"

Dense::Dense(const Matrix& weight, const Matrix& bias, ActivationType act_type)
    : weight (weight), bias (bias), act_type (act_type)
{}
Matrix Dense::get_weights () const
{
  return weight;
}
Matrix Dense::get_bias () const
{
  return bias;
}
ActivationType Dense::get_activation () const
{
  return act_type;
}

Matrix Dense::operator() (Matrix const &mat)
{
  Matrix new_mat(weight * mat + bias);
  Activation act (act_type);
  return act (new_mat);
}




