#include "minutia.h"

Minutia::Minutia()
{
}

Minutia::Minutia(double an, int x_pos, int y_pos, MinutiaType t)
{
    x = x_pos;
    y = y_pos;
    angle = an;
    type = t;
}

Minutia::Minutia(double an, int x_pos, int y_pos)
{
    x = x_pos;
    y = y_pos;
    angle = an;
}
