#ifndef LAYER_H
#define LAYER_H


class Layer
{

public:

    enum ConnectionOrganisation{EVERY, GROUP};
    enum WeightOrganisation{UNIQUE, SHARED};

    Layer();
    Layer(const int & id);

    void getNeurons(int & weightId);

    int neuronCount;
    ConnectionOrganisation connectionOrganisation;
    int connectionNumber;
    WeightOrganisation weightOrganisation;
    int inputCount;

private:

    int id;

};


#endif // LAYER_H
