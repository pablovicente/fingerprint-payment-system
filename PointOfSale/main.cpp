#include <QCoreApplication>
#include <settings.h>
#include "paymentprocess.h"
#include "screen.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString idDevice;
    QString keyDevice;

    if(!Settings::loadSettings(idDevice, keyDevice))   {
        Screen screen;
        screen.clearScreen();
        screen.displayText(0,"Dispositivo no identificado");

        return 0;
    }
    else    {
        PaymentProcess paymentProc;
        paymentProc.init();
    }
    return a.exec();
}

