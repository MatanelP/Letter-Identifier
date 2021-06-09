//
// Created by Matanel on 02/06/2021.
//

#include "Dense.h"

/**
 * Creates a new layer.
 * @param weight - Matrix, the given weigh for the layer.
 * @param bias - Matrix, the given bias for the layer.
 * @param act - ActivationType, the given function for the layer.
 */
Dense::Dense (const Matrix &weight, const Matrix &bias, ActivationType act)
    : _weight (weight), _bias (bias), _act (act)
{}
Matrix Dense::get_weights () const
{

  /**
 * @return Matrix, the given weigh for the layer.
 */
  return _weight;
}

/**
 * @return Matrix, the given bias for the layer.
 */
Matrix Dense::get_bias () const
{
  return _bias;
}

/**
 * @return Activation, the given function for the layer.
 */
Activation Dense::get_activation () const
{
  return _act;
}

/**
 * Apply the weight and the bias on a given matrix.
 * @param mat - Matrix, the input matrix to act on.
 * @return a Matrix, the output of the layer after the function been applied.
 */
Matrix Dense::operator() (Matrix const &mat) const
{
  Matrix new_mat(_weight * mat + _bias);
  return _act (new_mat);
}




