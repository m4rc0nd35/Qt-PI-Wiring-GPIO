#ifndef CONTROLLE_H
#define CONTROLLE_H

#include <QThread>
#include <QDebug>
#include <wiringPi.h>

class Controlle : public QThread
{
    Q_OBJECT
public:
    explicit Controlle(QObject *parent = nullptr);
    void rotate();
    /* Set */
    void setOpenCollector();
    void setCloseCollector();
    void setFreePassCW();
    void setFreePassCCW();
    /* */
    bool freePassCW = false;
    bool freePassCCW = false;
    /* Status */
    bool rotateCW = false;
    bool rotateCCW = false;
    /* Pin OUT */
    int pinOutLocker = 0;
    int pinOutCollectot = 0;
    /* Pin IN */
    int pinInSensorCW = 0;
    int pinInSensorCCW = 0;
    int pinInIRCollector = 0;
    bool getStateCollector();

private:
    void run() override;

};

#endif // CONTROLLE_H
