#include "failedpredictions.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FailedPredictions w;
    w.show();
    return a.exec();
}
