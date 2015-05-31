#include "util.hpp"
#include <QCoreApplication>


int main(int argc, char *argv[])
{
    // Init
    QCoreApplication a(argc, argv);
    Util::init();

    // The end
    return 0;
}
