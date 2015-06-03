#include "neuron.hpp"
#include <QDebug>


Neuron::Neuron()
{

}


void Neuron::addWeights(const int & firstWeight, const int & weightCount)
{
    for(int i = firstWeight ; i < firstWeight + weightCount ; i++)
    {
        weightIds.append(i);
    }
}

void Neuron::addExternalInputs(const int & firstExternal,
                               const int & externalCount)
{
    for(int i = firstExternal ; i < firstExternal + externalCount ; i++)
    {
        externalInputsId.append(i);
    }
}

void Neuron::addExternalInputs(const int & firstExternal,
                               const int & step,
                               const int & lastExternal)
{
    for(int i = firstExternal ; i <= lastExternal ;  i+=step)
    {
        externalInputsId.append(i);
    }
}

void Neuron::debug()
{
    qDebug() << "externalInputsId"<< externalInputsId;
    qDebug() << "weightIds"<< weightIds;
}

