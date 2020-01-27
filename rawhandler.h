#ifndef RAWHANDLER_H
#define RAWHANDLER_H

#define ACC_SCALE .00015258789062361865f;
#define GYRO_SCALE .00002196f;
#define SYNC_SCALE .000000016666f;

#include "ibldata.h"
#include <QThread>

class RawHandler : public QThread
{
    Q_OBJECT

public:
    RawHandler();
    ~RawHandler();

    void setRawData(QByteArray b){ rawData.append(b); }
    void clearRawData(){ rawData.clear(); }
    qint64 countRawData(){ rawData.length(); }

protected:
    virtual void run();

private:
    QByteArray rawData;
    IBLData convert(QByteArray b);
};

#endif // RAWHANDLER_H
