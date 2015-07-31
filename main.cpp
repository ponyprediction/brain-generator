#include "brain-generator.hpp"
#include "util.hpp"
#include <QCoreApplication>
#include <time.h>
#include <QTime>


int main(int argc, char *argv[])
{
    // Init
    QTime time = QTime::currentTime();
    unsigned int seed = time.msec();
    qsrand(seed);
    QCoreApplication a(argc, argv);
    Util::init();
    QString command;
    // Command from terminal or conf.xml ?
    if(argc > 1)
    {
        for(int i = 1 ; i < argc ; i++)
        {
            if(i-1)
            {
                command += " ";
            }
            command += argv[i];
        }
    }
    else
    {
        command = Util::getLineFromConf("command");
    }
    // Go
    BrainGenerator::generate(command);
    // The end
    return 0;
}
