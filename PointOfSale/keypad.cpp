#include "keypad.h"

Keypad::Keypad(QObject *parent) :
    QObject(parent)
{    
    MATRIX[0][0] = '1';
    MATRIX[0][1] = '2';
    MATRIX[0][2] = '3';
    MATRIX[0][3] = 'A';

    MATRIX[1][0] = '4';
    MATRIX[1][1] = '5';
    MATRIX[1][2] = '6';
    MATRIX[1][3] = 'B';

    MATRIX[2][0] = '7';
    MATRIX[2][1] = '8';
    MATRIX[2][2] = '9';
    MATRIX[2][3] = 'C';

    MATRIX[3][0] = '*';
    MATRIX[3][1] = '0';
    MATRIX[3][2] = '#';
    MATRIX[3][3] = 'D';

    ROW[0] = 1;
    ROW[1] = 4;
    ROW[2] = 5;
    ROW[3] = 6;

    COL[0] = 7;
    COL[1] = 0;
    COL[2] = 2;
    COL[3] = 3;

    reset();
}

void Keypad::reset(void)
{    
    QThread::sleep(1);

    for(int j=0;j<4;j++)  {
        pinMode(COL[j], OUTPUT);
        digitalWrite(COL[j], HIGH);
    }

    for(int i=0;i<4;i++) {
        pinMode(ROW[i], INPUT);
        pullUpDnControl(ROW[i], PUD_UP);
    }
}

char Keypad::getKey(void)
{
    int i,j;

    while(1) {
        for(j=0;j<4;j++)
        {
            digitalWrite(COL[j],LOW);
            for(i=0;i<4;i++)
            {
                if(digitalRead(ROW[i]) == LOW)
                {
                    previous = current;
                    current = MATRIX[i][j];

                    if(current != previous)
                    {
                        digitalWrite(COL[j],HIGH);

                        while(digitalRead(ROW[i]) == 0) {}
                        qDebug() << "Se ha pulsado " << MATRIX[i][j];
                        return MATRIX[i][j];
                    }
                }

            }
            digitalWrite(COL[j],HIGH);
        }
    }

}



