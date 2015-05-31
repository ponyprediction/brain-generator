#ifndef BRAINGENERATOR_H
#define BRAINGENERATOR_H

#include <QString>


class BrainGenerator
{

public:

    enum ConnectionOrganisation{EVERY, GROUP};
    enum WeightOrganisation{UNIQUE, SHARED};
    enum OutType{UNIQUEID, PERCENTS};

    struct Layer
    {
        int neuronCount;
        ConnectionOrganisation connectionOrganisation;
        int connectionNumber;
        WeightOrganisation weightOrganisation;
        OutType outType;
    };

    static void generate(const QString & command);

};


#endif // BRAINGENERATOR_H
