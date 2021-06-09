//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType {
  RELU,
  SOFTMAX
};

class Activation {

 public:

  /**
   * Creates a new Activation.
   * @param act_type - ActivationType, what kind of function will run.
   */
  explicit Activation (ActivationType act_type);

  /**
   * @return the ActivationType as in RELU or SOFTMAX
   */
  ActivationType get_activation_type () const;

  /**
   * Apply the function on the given matrix.
   * @param mat = Matrix, the current matrix to act on.
   * @return a new matrix, the result of the function on the input matrix.
   */
  Matrix operator() (Matrix const &mat) const;

 private:
  ActivationType _act_type;
};

#endif //ACTIVATION_H
