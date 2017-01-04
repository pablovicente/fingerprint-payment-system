#include "settings.h"

Settings::Settings()
{
}

bool Settings::loadSettings(QString &idDevice, QString &keyDevice)
{
    QSettings settings;    
    idDevice = settings.value("idDevice").toString();
    keyDevice = settings.value("keyDevice").toString();

    Communication com;
    if(idDevice == "" || keyDevice == "" || !com.authenticateDevice(idDevice,keyDevice))  {
            return false;
    }

    return true;

}

void Settings::saveSettings(QString idDevice, QString keyDevice)
{
    QSettings settings;
    settings.setValue("idDevice", idDevice);
    settings.setValue("keyDevice", keyDevice);
}

