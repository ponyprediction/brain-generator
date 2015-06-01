#include "brain-generator.hpp"
#include "util.hpp"
#include <QJsonObject>
#include <QFileInfo>
#include <QJsonDocument>


void BrainGenerator::generate(const QString &command)
{
    // Init
    bool ok = true;
    QFile file;
    QString filename;
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
        QJsonObject brain;

        brain["ratio"] = 0.0;

        document.setObject(brain);
        file.write(document.toJson());
    }
}
