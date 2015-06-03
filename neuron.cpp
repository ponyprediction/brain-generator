#include "neuron.hpp"
#include <QDebug>


Neuron::Neuron()
{

}


void Neuron::addWeights(const int & weightId, const int & weightCount)
{
    for(int i = weightId ; i < weightId + weightCount ; i++)
    {
        weightIds.append(i);
    }
    qDebug() << weightIds;
}

