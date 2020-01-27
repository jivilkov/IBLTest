#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <qglobal.h>

struct IBLData {
    qint16 head;
    qint16 counter;
    qint32 speedAcc1;
    qint32 speedAcc2;
    qint32 speedAcc3;
    qint16 countAcc1;
    qint16 countAcc2;
    qint16 countAcc3;
    qint32 angleInW1;
    qint32 angleInW2;
    qint32 angleInW3;
    qint32 syncLength;
    qint16 chanelStat;
    qint16 multiplex;
    qint16 CRC16;
    qint16 CRC16_check;
};

#endif // TABLEDATA_H
