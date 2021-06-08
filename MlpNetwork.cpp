//
// Created by Matanel on 02/06/2021.
//
#include "MlpNetwork.h"

MlpNetwork::MlpNetwork (Matrix *weights, Matrix *biases)
{
  for (int i = 0; i < MLP_SIZE; ++i)
    {
      _weights[i] = weights[i];
      _biases[i] = biases[i];
    }
}

digit MlpNetwork::operator() (Matrix const &mat)
{

  Dense layer0 (_weights[0], _biases[0], RELU);
  Dense layer1 (_weights[1], _biases[1], RELU);
  Dense layer2 (_weights[2], _biases[2], RELU);
  Dense layer3 (_weights[3], _biases[3], SOFTMAX);

  Matrix output_array = layer3 (layer2 (layer1 (layer0 (mat))));

//  output_array.plain_print();

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
