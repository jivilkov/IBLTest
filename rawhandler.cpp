#include "rawhandler.h"

RawHandler::RawHandler()
{
    workFlag = false;
}

RawHandler::~RawHandler()
{

}

void RawHandler::run()
{
    workFlag = true;
    qDebug() << "rawhandler thread started";
    while(workFlag){
        msleep(10);
        if (rawData.size() >= SIZE_PACK){
            QByteArray pack = rawData.left(SIZE_PACK);
            rawPackBuffer.append(pack);
            iblPackBuffer.append(convert(pack));
            rawData.remove(0, SIZE_PACK);
        }
    }

    qDebug() << "rawhandler thread stopped";
}

IBLData RawHandler::convert(QByteArray b)
{

    // Check errors!

    IBLData ibl;
    ibl.head = ((b[1] & 0xFF) << 8) + ((b[0] & 0xFF));
    ibl.counter = ((b[3] & 0xFF) << 8) + ((b[2] & 0xFF));

    qint32 speedAcc;
    speedAcc = ((b[7] & 0xFF) << 24) + ((b[6] & 0xFF) << 16) +
               ((b[5] & 0xFF) << 8) + ((b[4] & 0xFF));
    ibl.speedAcc1 = speedAcc * ACC_SCALE;

    speedAcc = ((b[11] & 0xFF) << 24) + ((b[10] & 0xFF) << 16) +
               ((b[9] & 0xFF) << 8) + ((b[8] & 0xFF));
    ibl.speedAcc2 = (speedAcc) * ACC_SCALE;

    speedAcc = ((b[15] & 0xFF) << 24) + ((b[14] & 0xFF) << 16) +
               ((b[13] & 0xFF) << 8) + ((b[12] & 0xFF));
    ibl.speedAcc3 = (speedAcc) * ACC_SCALE;

    ibl.countAcc1 = (((b[17] & 0xFF) << 8) + (b[16] & 0xFF));
    ibl.countAcc2 = (((b[19] & 0xFF) << 8) + (b[18] & 0xFF));
    ibl.countAcc3 = (((b[21] & 0xFF) << 8) + (b[20] & 0xFF));

    qint32 angleIncrement;
    angleIncrement = ((b[25] & 0xFF) << 24) + ((b[24] & 0xFF) << 16) +
                     ((b[23] & 0xFF) << 8) + ((b[22] & 0xFF));
    ibl.angleInW1 = angleIncrement * GYRO_SCALE;

    angleIncrement = ((b[29] & 0xFF) << 24) + ((b[28] & 0xFF) << 16) +
                     ((b[27] & 0xFF) << 8) + ((b[26] & 0xFF));
    ibl.angleInW2 = angleIncrement * GYRO_SCALE;

    angleIncrement = ((b[33] & 0xFF) << 24) + ((b[32] & 0xFF) << 16) +
                     ((b[31] & 0xFF) << 8) + ((b[30] & 0xFF));
    ibl.angleInW3 = angleIncrement * GYRO_SCALE;

    ibl.syncLength = (((b[37] & 0xFF) << 24) + ((b[36] & 0xFF) << 16) +
                     ((b[35] & 0xFF) << 8) + ((b[34] & 0xFF))) * SYNC_SCALE;

    ibl.chanelStat = (((b[39] & 0xFF) << 8) + (b[38] & 0xFF));
    ibl.multiplex = (((b[41] & 0xFF) << 8) + (b[40] & 0xFF));

    ibl.CRC16 = ((b[43] & 0xFF) << 8) + (b[42] & 0xFF);

    b.remove(42, 2);
    b.remove(0, 2);

    return ibl;
}

QList<IBLData> RawHandler::getIblPacks()
{
    QList<IBLData> packs = iblPackBuffer;
    iblPackBuffer.clear();
    return packs;
}

QList<QByteArray> RawHandler::getRawPacks()
{
    QList<QByteArray> packs = rawPackBuffer;
    rawPackBuffer.clear();
    return packs;
}
