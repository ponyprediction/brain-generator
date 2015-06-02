#ifndef LAYER_H
#define LAYER_H


class Layer
{

public:

    enum ConnectionOrganisation{EVERY, GROUP};
    enum WeightOrganisation{UNIQUE, SHARED};
    enum OutType{UNIQUEID, PERCENTS};

    Layer();

    int neuronCount;
    ConnectionOrganisation connectionOrganisation;
    int connectionNumber;
    WeightOrganisation weightOrganisation;
    OutType outType;

};


#endif // LAYER_H
