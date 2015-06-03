#ifndef NEURON_H
#define NEURON_H

#include <QVector>


class Neuron
{

public:

    Neuron();

    void addWeights(const int & weightId, const int & weightCount);

private:

    QVector<int> weightIds;

};


#endif // NEURON_H
