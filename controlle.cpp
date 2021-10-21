#include "controlle.h"

Controlle::Controlle(QObject *parent) : QThread(parent)
{
    /* Pin OUT */
    pinOutLocker = 0;
    pinOutCollectot = 0;
    /* Pin IN */
    pinInSensorCW = 0;
    pinInSensorCCW = 0;
    pinInIRCollector = 0;
    /* Setup */
    wiringPiSetup();
    pinMode(pinOutLocker, OUTPUT);
    pinMode(pinOutCollectot, OUTPUT);
    pinMode(pinInSensorCW, INPUT);
    pinMode(pinInSensorCCW, INPUT);
    pinMode(pinInIRCollector, INPUT);
//    start();
}

void Controlle::setOpenCollector()
{
    digitalWrite(pinOutCollectot, 0);
}

void Controlle::setCloseCollector()
{   
    digitalWrite(pinOutCollectot, 1);
}

void Controlle::setFreePassCW()
{
    freePassCW = true;
}

void Controlle::setFreePassCCW()
{
    freePassCCW = true;
}

bool Controlle::getStateCollector()
{
    return digitalRead(pinInIRCollector);
}

void Controlle::rotate()
{
    while (true) {
        if(digitalRead(pinInSensorCW) == 0)
        {
            rotateCW = true;
            qDebug() << "pinInSensorCW" << endl;
            continue;
        }else if(digitalRead(pinInSensorCCW) == 0){
            rotateCCW = true;
            qDebug() << "pinInSensorCCW" << endl;
            continue;
        }
    }
}

void Controlle::run()
{
    while (true) {
        freePassCW = false;
        freePassCCW = false;
        rotateCW = false;

        /* detect rotate */
        rotate();

        if(rotateCW)
        {
            while (digitalRead(pinInSensorCW) == 0) {
                msleep(1);
                if(freePassCW)
                    while (digitalRead(pinInSensorCCW) == 0)
                    {
                        msleep(1);
                        if(digitalRead(pinInSensorCW) == 1)
                        {
                            /* Authorization */
                            freePassCW = false;
                        }
                    }
                else
                {
                    digitalWrite(pinOutLocker, 0);
                    qDebug() << "CW Block" << endl;
                }
            }
        }

        if(rotateCCW)
        {
            while (digitalRead(pinInSensorCCW) == 0) {
                msleep(1);
                if(freePassCCW)
                    while (digitalRead(pinInSensorCW) == 0)
                    {
                        msleep(1);
                        if(digitalRead(pinInSensorCCW) == 1)
                        {
                            /* Authorization */
                            freePassCCW = false;
                        }
                    }
                else
                {
                    digitalWrite(pinOutLocker, 0);
                    qDebug() << "CCW Block" << endl;
                }
            }
        }
        msleep(1);
        digitalWrite(pinOutLocker, 1);
        digitalWrite(pinOutCollectot, 1);
        rotateCW = false;
        rotateCCW = false;
    }
}


