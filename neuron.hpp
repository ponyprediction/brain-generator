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
                           const int & step,
                           const int & lastExternal);

    void addInternalInputs(const int & first,
                           const int & step,
                           const int & last);

    void debugWeigths();
    void debugExternals();
    void debugInternals();

private:

    QVector<int> externalInputsId;
    QVector<int> weightIds;
    QVector<int> internalInputsId;

};


#endif // NEURON_H
