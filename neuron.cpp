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
                               const int & step,
                               const int & lastExternal)
{
    for(int i = firstExternal ; i <= lastExternal ;  i+=step)
    {
        externalInputsId.append(i);
    }
}

void Neuron::addInternalInputs(const int & first,
                               const int & step,
                               const int & last)
{
    for(int i = first ; i <= last ;  i+=step)
    {
        internalInputsId.append(i);
    }
}


void Neuron::debugWeigths()
{
    qDebug() << "weightIds"<< weightIds;
}


void Neuron::debugExternals()
{
    qDebug() << "externalInputsId"<< externalInputsId;
}


void Neuron::debugInternals()
{
    qDebug() << "internalInputsId"<< internalInputsId;
}
