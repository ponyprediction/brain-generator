#include "brain-generator.hpp"
#include "layer.hpp"
#include "util.hpp"
#include <QJsonObject>
#include <QFileInfo>
#include <QJsonDocument>
#include <QStringList>
#include <QDebug>
#include <vector>


void BrainGenerator::generate(const QString &command)
{
    // Init
    bool ok = true;
    QFile file;
    QString filename;
    QJsonObject brain;
    brain["ratio"] = 0.0;
    int inputCount = 0;
    QVector<Layer> layers;
    // Parsing command
    if(ok)
    {
        QStringList args = command.split(' ');
        Layer currentLayer;
        // Define the difereent accepted commands
        QStringList acceptedArgs;
        enum AcceptedArg{EVERY=0, IN, GROUP, LAYER, OUT,
                         PERCENTS, SHARED, UNIQUE, UNIQUEID};
        acceptedArgs << "every" << "in" << "group" << "layer" << "out"
                     << "percents" << "shared" << "unique" << "uniqueid" ;
        // Define the different states
        enum class State{IN, LAYER, CONNECTION, WEIGHTS, LAYER_OR_OUT,
                         OUT, OUT_TYPE, DONE};
        State state = State::IN;
        // Parsing
        for(int i = 0 ; i < args.size() ; i++)
        {
            switch(state)
            {

                case State::IN:
                {
                    if(args[i] == acceptedArgs[IN])
                    {
                        i++;
                        inputCount = args[i].toInt(&ok);
                        if(!ok)
                        {
                            Util::writeError("not a number after argument "
                                             + args[i]);
                        }
                        state = State::LAYER;
                    }
                    else
                    {
                        ok = false;
                        writeErrorParsing(args, i);
                    }
                    break;
                }

                case State::LAYER:
                {
                    if(args[i] == acceptedArgs[LAYER])
                    {
                        i++;
                        currentLayer = Layer();
                        currentLayer.neuronCount = args[i].toInt(&ok);
                        if(!ok)
                        {
                            writeErrorParsing(args, i);
                        }
                        state = State::CONNECTION;
                    }
                    else
                    {
                        ok = false;
                        writeErrorParsing(args, i);
                    }
                    break;
                }

                case State::CONNECTION:
                {
                    if(args[i] == acceptedArgs[EVERY]
                            || args[i] == acceptedArgs[GROUP])
                    {
                        i++;
                        if(args[i] == acceptedArgs[EVERY] )
                        {
                            currentLayer.connectionOrganisation = Layer::EVERY;
                        }
                        else if(args[i] == acceptedArgs[GROUP])
                        {
                            currentLayer.connectionOrganisation = Layer::GROUP;
                        }
                        currentLayer.connectionNumber = args[i].toInt(&ok);
                        if(!ok)
                        {
                            writeErrorParsing(args, i);
                        }
                        state = State::WEIGHTS;
                    }
                    else
                    {
                        ok = false;
                        writeErrorParsing(args, i);
                    }
                    break;
                }

                case State::WEIGHTS:
                {
                    if(args[i] == acceptedArgs[UNIQUE]
                            || args[i] == acceptedArgs[SHARED])
                    {
                        if(args[i] == acceptedArgs[UNIQUE] )
                        {
                            currentLayer.weightOrganisation = Layer::UNIQUE;
                        }
                        else if(args[i] == acceptedArgs[SHARED])
                        {
                            currentLayer.weightOrganisation = Layer::SHARED;
                        }
                        state = State::LAYER_OR_OUT;
                    }
                    else
                    {
                        ok = false;
                        writeErrorParsing(args, i);
                    }
                    break;
                }

                case State::LAYER_OR_OUT:
                {
                    layers << currentLayer;
                    if(args[i] == acceptedArgs[LAYER])
                    {
                        i++;
                        currentLayer = Layer();
                        currentLayer.neuronCount = args[i].toInt(&ok);
                        if(!ok)
                        {
                            writeErrorParsing(args, i);
                        }
                        state = State::CONNECTION;
                    }
                    else if(args[i] == acceptedArgs[OUT])
                    {
                        state = State::OUT_TYPE;
                    }
                    else
                    {
                        ok = false;
                        writeErrorParsing(args, i);
                    }
                    break;
                }

                case State::OUT_TYPE:
                {
                    if(args[i] == acceptedArgs[UNIQUEID]
                            || args[i] == acceptedArgs[PERCENTS])
                    {
                        if(args[i] == acceptedArgs[UNIQUEID] )
                        {
                            currentLayer.outType = Layer::UNIQUEID;
                        }
                        else if(args[i] == acceptedArgs[PERCENTS])
                        {
                            currentLayer.outType = Layer::PERCENTS;
                        }
                        state = State::DONE;
                    }
                    else
                    {
                        ok = false;
                        writeErrorParsing(args, i);
                    }
                    break;
                }

                case State::DONE:
                {

                }

                default:
                {
                    Util::write("LAYER");
                    Util::write("Bob");
                    break;
                }

            }
        }
    }
    //
    if(ok)
    {
        filename = Util::getLineFromConf("brainFilename", &ok);
        filename.replace("NAME", "bob");
    }
    // Open up JSON ..
    if(ok)
    {
        file.setFileName(filename);
        if (!file.open(QFile::WriteOnly))
        {
            ok = false;
            Util::writeError("cannot open file "
                             + QFileInfo(file).absoluteFilePath());
        }
    }
    // Write down Json
    if(ok)
    {
        QJsonDocument document;
        document.setObject(brain);
        file.write(document.toJson());
    }
}

void BrainGenerator::writeErrorParsing(const QStringList & args, const int & i)
{
    QString error;
    for(int j = 0 ; j < i ; j++)
    {
        if(j)
            error += " ";
        error += args[j];
    }
    error += " [" + args[i] + "]";
    for(int j = i+1 ; j < args.size() ; j++)
    {
        error += " ";
        error += args[j];
    }
    Util::writeError("not a valid argument : " + error);
}
