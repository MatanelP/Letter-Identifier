//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"
#include "Digit.h"


#define MLP_SIZE 4

//
const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

class MlpNetwork{

 public:

  MlpNetwork (Matrix *weights, Matrix *biases);

  digit operator() (Matrix const &mat);


 private:
  Matrix _weights[MLP_SIZE];
  Matrix _biases[MLP_SIZE];


};

#endif // MLPNETWORK_H
