#include "layer.hpp"
#include "neuron.hpp"
#include "util.hpp"
#include <QVector>


Layer::Layer()
{
}

void Layer::init()
{
    for(int i = 0 ; i < neuronCount ; i++)
    {
        neurons.append(Neuron());
    }
}


void Layer::getNeurons()
{
    for(int i = 0 ; i < neuronCount ; i++)
    {
        neurons[i].debugIExternals();
    }
    for(int i = 0 ; i < neuronCount ; i++)
    {
        neurons[i].debugWeigths();
    }
}


void Layer::setWeights(int & weightId)
{
    //
    int weightPerNeuron = 0;
    //
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
}


void Layer::setExternalInputs()
{
    // First layer
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
            }
            break;
        }
    }
}


void Layer::setInternalInputs()
{
    switch (connectionOrganisation)
    {
        case GROUP:
        {

            break;
        }
        case EVERY:
        {

            break;
        }
    }
}
