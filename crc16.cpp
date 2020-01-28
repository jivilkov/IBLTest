#include "crc16.h"

quint16 CRC16::of(QList<quint16> pcBlock)
{
    quint16 crc = 0xFFFF;
    quint16 index = 0;
    quint16 len = pcBlock.length();
    while (index < len){
        crc = (crc << 8) ^ CRC16Table[((crc >> 8) ^ pcBlock[index]) & 0xFF];
        index++;
        crc = crc & 0xFFFF;
    }
    return crc;
}
