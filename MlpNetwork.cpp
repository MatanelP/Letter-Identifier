//
// Created by Matanel on 02/06/2021.
//
#include "MlpNetwork.h"

/**
   * Creates a new network.
   * @param weights - array of Matrices, representing the weights.
   * @param biases - array of Matrices, representing the biases.
   */
MlpNetwork::MlpNetwork (Matrix *weights, Matrix *biases)
{
  for (int i = 0; i < MLP_SIZE; ++i)
    {
      _weights[i] = weights[i];
      _biases[i] = biases[i];
    }
}

/**
 * creating all the needed layers and performing the chain of function on
 * the input matrix to get the matrix representing the network output.
 * @param mat - Matrix, the input matrix.
 * @return a Matrix, the output matrix representing the network after math.
 */
Matrix MlpNetwork::get_output_array (const Matrix &mat) const
{
  Dense layer0 (_weights[0], _biases[0], RELU);
  Dense layer1 (_weights[1], _biases[1], RELU);
  Dense layer2 (_weights[2], _biases[2], RELU);
  Dense layer3 (_weights[3], _biases[3], SOFTMAX);
  return layer3 (layer2 (layer1 (layer0 (mat))));
}

/**
 * Applying all needed calculation the get the final output of the network.
 * @param mat - Matrix, the input matrix.
 * @return a digit, the output digit representing the network after math.
 */
digit MlpNetwork::operator() (Matrix const &mat) const
{
  Matrix output_array = get_output_array (mat);

  digit output;
  output.value = 0;
  output.probability = 0;
  for (int i = 0; i < weights_dims[MLP_SIZE-1].rows; ++i)
    {
      if (output_array[i] > output.probability)
        {
          output.value = i;
          output.probability = output_array[i];
        }
    }

  return output;
}
