#ifndef NEURON_H
#define NEURON_H

#include <QVector>


class Neuron
{

public:

    Neuron();

    void addWeights(const int & firstWeight,
                    const int & weightCount);

    void addExternalInputs(const int & firstExternal,
                           const int & externalCount);

    void addExternalInputs(const int & firstExternal,
                           const int & step,
                           const int & lastExternal);

    void debugWeigths();
    void debugIExternals();

private:

    QVector<int> externalInputsId;
    QVector<int> weightIds;

};


#endif // NEURON_H
