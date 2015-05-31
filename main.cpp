#include "brain-generator.hpp"
#include "util.hpp"
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    // Init
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
