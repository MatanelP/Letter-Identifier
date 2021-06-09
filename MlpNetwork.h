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
const matrix_dims bias_dims[] = {{128, 1},
                                 {64, 1},
                                 {20, 1},
                                 {10, 1}};

class MlpNetwork {

 public:

  /**
   * Creates a new network.
   * @param weights - array of Matrices, representing the weights.
   * @param biases - array of Matrices, representing the biases.
   */
  MlpNetwork (Matrix *weights, Matrix *biases);

  /**
   * Applying all needed calculation the get the final output of the network.
   * @param mat - Matrix, the input matrix.
   * @return a digit, the output digit representing the network after math.
   */
  digit operator() (Matrix const &mat) const;

 private:
  Matrix _weights[MLP_SIZE];
  Matrix _biases[MLP_SIZE];

  /**
   * creating all the needed layers and performing the chain of function on
   * the input matrix to get the matrix representing the network output.
   * @param mat - Matrix, the input matrix.
   * @return a Matrix, the output matrix representing the network after math.
   */
  Matrix get_output_array (const Matrix &mat) const;
};

#endif // MLPNETWORK_H
