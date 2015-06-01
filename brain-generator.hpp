#ifndef BRAINGENERATOR_H
#define BRAINGENERATOR_H

#include <QString>


class BrainGenerator
{

public:



    struct Layer
    {
        enum ConnectionOrganisation{EVERY, GROUP};
        enum WeightOrganisation{UNIQUE, SHARED};
        enum OutType{UNIQUEID, PERCENTS};

        int neuronCount;
        ConnectionOrganisation connectionOrganisation;
        int connectionNumber;
        WeightOrganisation weightOrganisation;
        OutType outType;
    };

    static void generate(const QString & command);

    static void writeErrorParsing(const QStringList & args, const int & i);

};


#endif // BRAINGENERATOR_H
