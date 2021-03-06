#ifndef LAYER_H
#define LAYER_H

#include "neuron.hpp"
#include <QJsonObject>
#include <QVector>

class Layer
{

public:

    enum ConnectionOrganisation{EVERY, GROUP};
    enum WeightOrganisation{UNIQUE, SHARED};

    Layer();

    void init();

    void setWeights(int & weightId);

    void setExternalInputs();

    void setInternalInputs(int & neuronId);

    QJsonObject getNeurons(int id);

    int getHigherWeightId();

    int neuronCount;
    ConnectionOrganisation connectionOrganisation;
    int connectionNumber;
    WeightOrganisation weightOrganisation;
    int inputCount;

private:

    QVector<Neuron> neurons;

};


#endif // LAYER_H
