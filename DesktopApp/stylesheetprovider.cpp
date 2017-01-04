#include "stylesheetprovider.h"



StyleSheetProvider::StyleSheetProvider()
{
}

QString StyleSheetProvider::getDefaultStyleLabelForm()
{
    QString style;
    style = "font-family: helvetica neue; font-weight: 100; color: white; border: 1.5px solid rgba(244,244,244,0); background-color: rgba(240,240,240,0);";
    return style;
}

QString StyleSheetProvider::getErrorStyleLabelForm()
{
    QString style;
    style = "font-family: helvetica neue; font-weight: 100; color: #de2222; border-radius: 4px; border: 1.5px solid rgba(244,244,244,200); background-color: rgba(240,240,240,200);";
    return style;
}
