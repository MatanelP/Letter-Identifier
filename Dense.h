#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Activation.h"

class Dense {
 public:

  Dense (const Matrix& weight, const Matrix& bias, ActivationType act_type);

  Matrix get_weights () const;
  Matrix get_bias () const;
  ActivationType get_activation  () const;


  Matrix &operator() (Matrix const &mat);


 private:

  Matrix weight;
  Matrix bias;
  ActivationType act_type;

};

#endif //C___PROJECT_DENSE_H
