#include "screen.h"

#define LCD_COLS 16

Screen::Screen(QObject *parent) :
    QObject(parent)
{
    //Initialise LCD(int rows, int cols, int bits, int rs, int enable, int d0, int d1, int d2, int d3, int$
    lcdHandler = lcdInit (2, 16,4, LCD_RS, LCD_E ,LCD_D4 , LCD_D5, LCD_D6,LCD_D7,0,0,0,0);
    if (lcdHandler) {
        printf ("lcdInit failed! \n");
    }

    position[0] = 0;
    position[1] = 0;
    timer = 0 ;
}


void Screen::displayText(int line, QString message)
{
    const char* buffer = message.toStdString().c_str();
    lcdPosition(lcdHandler,0,line);           //Position cursor on the first line in the first column
    lcdPuts(lcdHandler, buffer);  //Print the text on the LCD at the current cursor postion
}


void Screen::scrollMessage (int line, int width, QString message)
{
    const char* buffer = message.toStdString().c_str();
    char buf [32] ;

    if (millis () < timer)
        return ;

    timer = millis () + 200 ;

    strncpy (buf, &buffer[position[line]], width) ;
    buf [width] = 0 ;
    lcdPosition (lcdHandler, 0, line) ;
    lcdPuts     (lcdHandler, buf) ;

    if (++position[line] == ((int)strlen(buffer) - width))
        position[line] = 0 ;

}

/*
 * waitForEnter:
 *********************************************************************************
 */

void Screen::waitForEnter (void)
{
    printf ("Press ENTER to continue: ") ;
    (void)fgetc (stdin) ;
}

void Screen::clearScreen(void)
{
    lcdClear(lcdHandler);
}

void Screen::doSetup(QThread &thread)
{
    connect(&thread, SIGNAL(started()), this, SLOT(doWork()));
}

void Screen::doWork()
{
    for(;;){
        sync.lock();
        //if(stop)
        //    pauseCond.wait(&sync); // in this place, your thread will stop to execute until someone calls resume
        sync.unlock();
        scrollMessage(0,LCD_COLS,  scrollingString);
    }
}


void Screen::resume(void)
{
    sync.lock();
    stop = false;
    sync.unlock();    
}

void Screen::pause(void)
{
    sync.lock();
    stop = true;
    sync.unlock();
}
