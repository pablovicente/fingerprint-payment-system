#include "paymentprocess.h"

PaymentProcess::PaymentProcess(QObject *parent) :
    QObject(parent)
{
}

void PaymentProcess::init(void)
{

    wiringPiSetup();
    Screen screen;
    Keypad keypad;
    ScanFingerprint scanner;
    ProcessFingerprint processFingerprint;
    Communication com;

    QString price;
    QString priceTag = "Precio: ";
    int cipherCounter = 0;
    int tries = 0;
    bool paymentValidated = false;
    bool scan = true;
    bool comma = false;
    cv::Mat temp;


    QThread thread;
    screen.doSetup(thread);
    screen.moveToThread(&thread);
    screen.scrollingString = "                        Todo lo que desee al alcance de sus manos";

    while(1)    {

        thread.start();


        char option = keypad.getKey();
        screen.sync.lock();

        switch(option)
        {
        case 'A':
            screen.clearScreen();
            keypad.reset();
            break;
        case 'B':
            screen.clearScreen();
            keypad.reset();
            break;
        case 'C':
            screen.clearScreen();
            keypad.reset();
            break;
        case 'D':
            screen.clearScreen();
            screen.displayText(0,priceTag);
            option = 'N';
            keypad.reset();
            qDebug() << "Introduzca el precio";
            while(option != 'D')
            {
                priceTag = "Precio: ";
                keypad.reset();
                option = keypad.getKey();
                if(option != 'A' && option != 'B' && option != 'C' && option != 'D' && option != '#')
                {
                    if(option == '*' && !comma) { price += "."; comma = true;}
                    else price += option;

                        cipherCounter++;
                        if(cipherCounter <= 8)
                        {
                            for(int i=8;i<16-cipherCounter;i++)
                                priceTag += " ";

                            priceTag += price;
                            qDebug() << priceTag;
                            screen.displayText(0, priceTag);
                        }
                        else if(cipherCounter > 8 && cipherCounter < 16)
                        {
                            screen.displayText(0, priceTag);

                            screen.displayText(1, price);
                            qDebug() << price;
                        }
                    
                }
            }


            while(tries < MAX_TRIES && !paymentValidated){
                screen.clearScreen();
                if(tries == 0) {
                    screen.displayText(0, "Ponga su huella");
                    qDebug() <<"Ponga su huella";
                } else {
                    screen.displayText(0, "Huella no valida");
                    qDebug() << "Huella no valida  Pruebe de nuevo";
                    screen.displayText(1, "Pruebe de nuevo");
                }

                MyFingerprint fingerprint;
                fingerprint.type = Index;

                while(scan)
                {
                    qDebug() << "TODAVIA NO";
                    scanner.scan().copyTo(temp);

                    if(temp.rows > 200)
                    {
                        screen.displayText(0, "Obteniendo características...");
                        processFingerprint.obtainMinutiaeFromSourceImage(temp, 304, fingerprint.minutiaes, 1, Scanner);
                        qDebug() << "YA";
                        scan = false;
                    }
                    else    {
                        QThread::sleep(1);
                    }
                }

                scan = true;
                screen.clearScreen();
                screen.displayText(0, "Validando identidad...");
                paymentValidated = com.makePayment(fingerprint, price,"EUR", "Paraiso");

                if(!paymentValidated) {
                    tries++;
                    screen.clearScreen();
                    screen.displayText(0, "Identidad no valida");
                    qDebug() << "identidad no valida";
                }

            }

            if(paymentValidated)   {
                screen.clearScreen();
                screen.displayText(0, "Pago realizado correctamente");
                qDebug() << "Pago realizado correctamente";
            }

            if(tries >= MAX_TRIES)   {
                screen.clearScreen();
                screen.displayText(0, "Identidad no valida");
                qDebug() << "identidad no valida";
            }

            break;
        default:
            screen.clearScreen();
        }

    }
}
