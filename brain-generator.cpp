#include "brain-generator.hpp"
#include "layer.hpp"
#include "util.hpp"
#include "neuron.hpp"
#include <QJsonObject>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>
#include <QDebug>
#include <vector>


void BrainGenerator::generate(const QString &command)
{
    // Init
    bool ok = true;
    QFile file;
    QString filename;
    QString name = "";
    QJsonObject brain;
    brain["ratio"] = 0.0;
    int inputCount = 0;
    QVector<Layer> layers;
    OutType outType;
    int weightCount = 0;
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
    // Parsing command
    if(ok)
    {
        QStringList args = command.split(' ');
        Layer currentLayer;
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
                        name += QString::number(inputCount);
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
                        name += "-" + QString::number(args[i].toInt(&ok));
                        currentLayer.inputCount = inputCount;
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
                        if(args[i] == acceptedArgs[EVERY] )
                        {
                            currentLayer.connectionOrganisation = Layer::EVERY;
                            name += "e";
                        }
                        else if(args[i] == acceptedArgs[GROUP])
                        {
                            currentLayer.connectionOrganisation = Layer::GROUP;
                            name += "g";
                        }
                        i++;
                        currentLayer.connectionNumber = args[i].toInt(&ok);
                         name += QString::number(args[i].toInt(&ok));
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
                            name += "u";
                        }
                        else if(args[i] == acceptedArgs[SHARED])
                        {
                            currentLayer.weightOrganisation = Layer::SHARED;
                            name += "s";
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
                        name += "-" + QString::number(args[i].toInt(&ok));
                        currentLayer.inputCount = layers.last().neuronCount;
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
                            outType = OutType::UNIQUEID;
                        }
                        else if(args[i] == acceptedArgs[PERCENTS])
                        {
                            outType = OutType::PERCENTS;
                        }
                        brain["outType"] = args[i];
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
        // neuronCount
        int neuronCount = 0;
        for(int i = 0 ; i < layers.size() ; i++)
        {
            neuronCount += layers[i].neuronCount;
        }
        brain["neuronCount"] = neuronCount;
        // inputCount
        brain["inputCount"] = inputCount;
        // outputCount
        brain["outputCount"] = layers.last().neuronCount;
        // command
        brain["command"] = command;
    }
    // Prepare neurons
    if(ok)
    {
        int weightId = 0;
        int neuronId = 0;
        for(int i = 0 ; i < layers.size() ; i++)
        {
            layers[i].init();
            layers[i].setWeights(weightId);
            if(!i)
            {
                layers[i].setExternalInputs();
            }
            else
            {
                layers[i].setInternalInputs(neuronId);
                neuronId += layers[i-1].neuronCount;
            }
        }
    }
    // Add neurons
    if(ok)
    {
        QJsonArray neurons;
        for(int i = 0 ; i < layers.size() ; i++)
        {
            for(int j = 0 ; j < layers[i].neuronCount ; j++)
            {
                neurons << layers[i].getNeurons(j);
            }
        }
        brain["neurons"] = neurons;
    }
    // Weight count
    if(ok)
    {

        for(int i = 0 ; i < layers.size() ; i++)
        {
            if(weightCount < layers[i].getHigherWeightId())
            {
                weightCount = layers[i].getHigherWeightId();
            }
        }
        weightCount += 1;
        brain["weightCount"] = weightCount;
    }
    // Weights
    if(ok)
    {
        QString weights;
        for(int i = 0 ; i < weightCount ; i++)
        {
            if(i)
            {
                weights += ";";
            }
            weights += QString::number(Util::getRandomFloat(-1.0, 1.0), 'f', 6);
        }
        brain["weights"] = weights;
    }
    //
    if(ok)
    {
        filename = Util::getLineFromConf("brainFilename", &ok);
        filename.replace("NAME", name);
    }
    // Open up JSON
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
    if(ok)
    {
        Util::writeSuccess("Brain ready at "
                           + QFileInfo(file).absoluteFilePath());
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
