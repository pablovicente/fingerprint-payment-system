#include "matching.h"
#include "qdebug.h"
#include "angle.h"

Matching::Matching()
{
}

std::vector<Minutia> transform(std::vector<Minutia> M1, int index)
{
    int XRef = M1[index].x;
    int YRef = M1[index].y;
    double ThetaRef = M1[index].angle;
    std::vector<Minutia> T(M1.size());
    double R[3][3] = {
        { cos(ThetaRef),-sin(ThetaRef),0},
        { sin(ThetaRef),cos(ThetaRef),0},
        {0,0,1}
    };

    /*!
     *  Realiza la transformacion de las coordenas
     *  para corregir el desplazamiento y la rotación
     */

    for(int i=0; i<(int)M1.size(); i++)
    {
        double B[3][1] = {
            {M1[i].x - XRef},
            {M1[i].y - YRef},
            {M1[i].angle - ThetaRef}
        };

        double product[3][1] = {{0}, {0}, {0}};

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 1; col++) {
                for (int inner = 0; inner < 3; inner++) {
                    product[row][col] += R[row][inner] * B[inner][col];
                }
            }
        }

        T[i].x = product[0][0];
        T[i].y= product[1][0];
        T[i].angle = product[2][0];
        T[i].type = M1[i].type;
    }

    return T;
}

float score(std::vector<Minutia> T1, std::vector<Minutia> T2)
{
    bool found;
    int j;
    int n = 0;

    for(int i=0; i<(int)T1.size(); i++) {
        found = false;
        j = 0;

        /*!
         * Se comprueba si los tipos de minucias son iguales
         * y si no está previamente emparejada
         */

        while(found==false && j<(int)T2.size()) {
            float dx = (T1[i].x - T2[j].x);
            float dy = (T1[i].y - T2[j].y);
            float d = sqrtf(powf(dx,2)+powf(dy,2));
            /*!
             * Si la distancia es menor que el threshold
             * se comprueba la orientacion
             */
            if(d < DISTANCE_THRESHOLD)   {
                float diffAngle = fabs(T1[i].angle - T2[j].angle) *180/CV_PI;
                diffAngle = fmin(diffAngle, 360-diffAngle);
                /*!
                 * Si la diferencia de orientacion es menor
                 * que el threshold se establece cuenta como matching
                 */
                if(diffAngle < ANGLE_THRESHOLD)   {
                    n++;
                    found = true;
                }
            }
            j++;
        }
    }

    return sqrtf(powf(n,2)/(T1.size()*T2.size()));
}


float Matching::match(std::vector<Minutia> M1, std::vector<Minutia> M2)
{
    std::vector<Minutia> T1, T2;
    float S,sm;
    S = 0;
    sm = 0;

    for(int i=0; i<(int)M1.size(); i++)
    {
        T1 = transform(M1, i);
        for(int j=0; j<(int)M2.size(); j++)
        {
            if(M1.at(i).type == M2.at(j).type)
            {
                T2 = transform(M2, j);
                sm = score(T1,T2);
                if(S < sm)
                    S = sm;
            }
        }
    }

    return S;
}
