#include "layer.hpp"
#include "neuron.hpp"
#include "util.hpp"
#include <QVector>


Layer::Layer() :
    Layer(0)
{

}


Layer::Layer(const int & id) :
    id(id)
{

}


void Layer::getNeurons(int & weightId)
{
    // Init
    Util::write("#" + QString::number(id));
    QVector<Neuron> neurons;
    int weightPerNeuron = 0;
    for(int i = 0 ; i < neuronCount ; i++)
    {
        neurons.append(Neuron());
    }
    //
    if(!id) // first layer
    {
        switch (connectionOrganisation)
        {
            case GROUP:
            {
                int firstExternalId = 0;
                int externalIdPerNeuron = connectionNumber;
                for(int i = 0 ; i < neuronCount ; i++)
                {
                    neurons[i].addExternalInputs(firstExternalId,
                                                 externalIdPerNeuron);
                    firstExternalId += externalIdPerNeuron;
                }
                break;
            }
            case EVERY:
            {
                for(int i = 0 ; i < neuronCount ; i++)
                {
                    int firstExternal = i % connectionNumber;
                    int step = connectionNumber;
                    int lastExternal = inputCount-1;
                    neurons[i].addExternalInputs(firstExternal, step,
                                                 lastExternal);
                    //externalId += externalIdPerNeuron;
                }
                break;
            }
        }
    }
    else
    {
    }
    // Weights
    for(int i = 0 ; i < neuronCount ; i++)
    {
        switch (weightOrganisation)
        {
            case SHARED:
            {
                weightId -= weightPerNeuron;
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
                weightPerNeuron = connectionNumber;
                break;
            case EVERY:
                weightPerNeuron = inputCount / connectionNumber;
                break;
        }
        neurons[i].addWeights(weightId, weightPerNeuron);
        weightId += weightPerNeuron;
    }
    //
    for(int i = 0 ; i < neuronCount ; i++)
    {
        neurons[i].debug();
    }
}

