#ifndef STYLESHEETPROVIDER_H
#define STYLESHEETPROVIDER_H

#include <QtCore>
class QString;

/*!
 * \brief The StyleSheetProvider class Clase que provee de estilos CSS
 */
class StyleSheetProvider
{
public:
    /*!
     * \brief StyleSheetProvider Constructor vacio
     */
    StyleSheetProvider();
    /*!
     * \brief getDefaultStyleLabelForm Metodo estatico que crea el estilo para el label normal
     * \return String con el estilo creado
     */
    static QString getDefaultStyleLabelForm();
    /*!
     * \brief getErrorStyleLabelForm Metodo estatico que crea el estilo para el label de error
     * \return String con el estilo creado
     */
    static QString getErrorStyleLabelForm();
};

#endif // STYLESHEETPROVIDER_H
