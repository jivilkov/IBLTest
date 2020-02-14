#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <qglobal.h>

struct IBLData {
    qint16 head;
    quint16 counter;
    float speedAcc1;
    float speedAcc2;
    float speedAcc3;
    qint16 countAcc1;
    qint16 countAcc2;
    qint16 countAcc3;
    float angleInW1;
    float angleInW2;
    float angleInW3;
    float syncLength;
    qint16 chanelStat;
    qint16 multiplex;
    qint16 CRC16;
    qint16 CRC16_check;
};

#endif // TABLEDATA_H
