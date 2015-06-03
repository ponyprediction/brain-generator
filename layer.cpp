#include "layer.hpp"
#include "neuron.hpp"
#include "util.hpp"
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QDebug>


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


QJsonObject Layer::getNeurons(int id)
{
    QJsonObject neuron;
    neuron["externalInputIds"] = neurons[id].getExternals();
    neuron["neuronalInputIds"] = neurons[id].getNeuronals();
    neuron["brainalInputIds"] = "";
    neuron["weightIds"] = neurons[id].getWeights();
    return neuron;
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
            int first = 0;
            int step = 1;
            int last = first + connectionNumber -1;
            for(int i = 0 ; i < neuronCount ; i++)
            {
                neurons[i].addExternalInputs(first, step,last);
                first += connectionNumber;
                last += connectionNumber;
            }
            break;
        }
        case EVERY:
        {
            for(int i = 0 ; i < neuronCount ; i++)
            {
                int first = i % connectionNumber;
                int step = connectionNumber;
                int last = inputCount-1;
                neurons[i].addExternalInputs(first, step, last);
            }
            break;
        }
    }
}


void Layer::setInternalInputs(int & neuronId)
{
    switch (connectionOrganisation)
    {
        case GROUP:
        {
            int first = neuronId;
            int step = 1;
            int last = first + connectionNumber -1;
            for(int i = 0 ; i < neuronCount ; i++)
            {
                neurons[i].addInternalInputs(first, step,last);
                first += connectionNumber;
                last += connectionNumber;
            }
            break;
        }
        case EVERY:
        {
            for(int i = 0 ; i < neuronCount ; i++)
            {
                int first = neuronId + i % connectionNumber;
                int step = connectionNumber;
                int last = first + inputCount - 1;
                neurons[i].addInternalInputs(first, step, last);
            }
            break;
        }
    }
}
