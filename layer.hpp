#ifndef LAYER_H
#define LAYER_H


class Layer
{

public:

    enum ConnectionOrganisation{EVERY, GROUP};
    enum WeightOrganisation{UNIQUE, SHARED};
    Layer();

    int neuronCount;
    ConnectionOrganisation connectionOrganisation;
    int connectionNumber;
    WeightOrganisation weightOrganisation;
};


#endif // LAYER_H
