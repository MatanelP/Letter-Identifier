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

  Activation (ActivationType act_type);

  ActivationType get_activation_type () const;

  Matrix &operator() (Matrix const &mat);

 private:
  ActivationType _act_type;
};

#endif //ACTIVATION_H
