#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Activation.h"

class Dense {

 public:

  /**
   * Creates a new layer.
   * @param weight - Matrix, the given weigh for the layer.
   * @param bias - Matrix, the given bias for the layer.
   * @param act - ActivationType, the given function for the layer.
   */
  Dense (const Matrix &weight, const Matrix &bias, ActivationType act);

  /**
   * @return Matrix, the given weigh for the layer.
   */
  Matrix get_weights () const;

  /**
   * @return Matrix, the given bias for the layer.
   */
  Matrix get_bias () const;

  /**
   * @return Activation, the given function for the layer.
   */
  Activation get_activation  () const;


  /**
   * Apply the weight and the bias on a given matrix.
   * @param mat - Matrix, the input matrix to act on.
   * @return a Matrix, the output of the layer after the function been applied.
   */
  Matrix operator() (Matrix const &mat) const;


 private:

  Matrix _weight;
  Matrix _bias;
  Activation _act;

};

#endif //C___PROJECT_DENSE_H
