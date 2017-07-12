#include <QApplication>
#include <QtCore>

#include <stdlib.h>

#include "server.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Server server;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return server.exec();
}
