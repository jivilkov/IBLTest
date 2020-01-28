#ifndef RAWHANDLER_H
#define RAWHANDLER_H

#define SIZE_PACK 44
#define ACC_SCALE .00015258789062361865f;
#define GYRO_SCALE .00002196f;
#define SYNC_SCALE .000000016666f;

#include "ibldata.h"
#include <QDebug>
#include <QThread>

class RawHandler : public QThread
{
    Q_OBJECT

public:
    RawHandler();
    ~RawHandler();

    void setRawData(QByteArray b){ rawData.append(b); }
    void stop(){ workFlag = false; }

    QList<QByteArray> getRawPacks();
    QList<IBLData> getIblPacks();

    qint32 rawPackAvailable(){ return rawPackBuffer.length(); }
    qint32 iblPackAvailable(){ return iblPackBuffer.length(); }

protected:
    virtual void run();

private:
    IBLData convert(QByteArray b);

    QByteArray rawData;
    QList<QByteArray> rawPackBuffer;
    QList<IBLData> iblPackBuffer;

    bool workFlag;
};

#endif // RAWHANDLER_H
