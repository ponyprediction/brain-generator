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


QString Neuron::getNeuronals()
{
    QString tmp = "";
    for(int i = 0 ; i < internalInputsId.size() ; i++)
    {
        if(i)
            tmp += ";";
        tmp += QString::number(internalInputsId[i]);
    }
    return tmp;
}


QString Neuron::getExternals()
{
    QString tmp = "";
    for(int i = 0 ; i < externalInputsId.size() ; i++)
    {
        if(i)
            tmp += ";";
        tmp += QString::number(externalInputsId[i]);
    }
    return tmp;
}


QString Neuron::getWeights()
{
    QString tmp = "";
    for(int i = 0 ; i < weightIds.size() ; i++)
    {
        if(i)
            tmp += ";";
        tmp += QString::number(weightIds[i]);
    }
    return tmp;
}


int Neuron::getHigherWeightId()
{
    int high = 0;
    for(int i = 0 ; i < weightIds.size() ; i++)
    {
        if(high < weightIds[i])
        {
            high = weightIds[i];
        }
    }
    return high;
}
