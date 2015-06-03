#include "layer.hpp"
#include "neuron.hpp"
#include <QVector>


Layer::Layer()
{

}


void Layer::getNeurons(int & weightId)
{
    //
    QVector<Neuron> neurons;
    int weightCount = 0;
    //
    for(int i = 0 ; i < neuronCount ; i++)
    {
        switch (weightOrganisation)
        {
            case SHARED:
            {
                weightId -= weightCount;
                break;
            }
            case UNIQUE:
            {
                break;
            }
        }
        switch (connectionOrganisation)
        {
            case GROUP:
            {
                weightCount = connectionNumber;
                break;
            }
            case EVERY:
            {
                weightCount = inputCount / connectionNumber;
                break;
            }
        }
        neurons.append(Neuron());
        neurons[i].addWeights(weightId, weightCount);
        weightId += weightCount;
    }
}

