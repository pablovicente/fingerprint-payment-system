#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore>
#include <QSettings>
#include "communication.h"

/*!
 * \brief The Settings class Clase encargada de gestionar el almacenamiento local
 */
class Settings
{
public:
    /*!
     * \brief Settings Constructor vacio
     */
    Settings();
    /*!
     * \brief loadSettings Metodo encargado de almacenar la informacion en local
     * \param idDevice String con el id del dispositivo
     * \param keyDevice String con la contraseña del dispositivo
     * \return Boolean que indica si se ha podido cargar la configuracion
     */
    static bool loadSettings(QString &idDevice, QString &keyDevice);
    /*!
     * \brief saveSettings Metodo encargado de cargar la informacion en local
     * \param idDevice String con el id del dispositivo
     * \param keyDevice String con la contraseña del dispositivo
     */
    static void saveSettings(QString idDevice, QString keyDevice);
};

#endif // SETTINGS_H

