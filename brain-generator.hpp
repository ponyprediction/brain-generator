#ifndef BRAINGENERATOR_H
#define BRAINGENERATOR_H

#include <QString>


class BrainGenerator
{

public:

    enum class OutType{UNIQUEID, PERCENTS};

    static void generate(const QString & command);

    static void writeErrorParsing(const QStringList & args, const int & i);

};


#endif // BRAINGENERATOR_H
