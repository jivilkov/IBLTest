#include "datamodel.h"

DataModel::DataModel()
{

}

DataModel::~DataModel()
{

}

int DataModel::rowCount(const QModelIndex&) const
{
    return tableData.length();
}

int DataModel::columnCount(const QModelIndex&) const
{
    return COL_SIZE;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole){
        int row = index.row();
        int col = index.column();
        IBLData table = tableData.at(row);

        switch(col){
                case    0: return QString("0x%0").arg(QString::number(table.head & 0xFFFF, 16).toUpper());
                case    1: return table.counter;
                case    2: return table.speedAcc1;
                case    3: return table.speedAcc2;
                case    4: return table.speedAcc3;
                case    5: return table.countAcc1;
                case    6: return table.countAcc2;
                case    7: return table.countAcc3;
                case    8: return table.angleInW1;
                case    9: return table.angleInW2;
                case   10: return table.angleInW3;
                case   11: return table.syncLength;
                case   12: return QString::number(table.chanelStat & 0xFFFF, 2);
                case   13: return table.multiplex;
                case   14: return QString("0x%0").arg(QString::number(table.CRC16 & 0xFFFF, 16).toUpper());
                case   15: return QString("0x%0").arg(QString::number(table.CRC16_check & 0xFFFF, 16).toUpper());
        }
    }

    if (role == Qt::TextAlignmentRole) return QVariant(Qt::AlignCenter);
    return QVariant();

}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    if (orientation == Qt::Horizontal){
        switch(section){
            case    0: return QString("Head");
            case    1: return QString("Counter");
            case    2: return QString("SAcc1");
            case    3: return QString("SAcc2");
            case    4: return QString("SAcc3");
            case    5: return QString("CAcc1");
            case    6: return QString("CAcc2");
            case    7: return QString("CAcc3");
            case    8: return QString("W1");
            case    9: return QString("W2");
            case   10: return QString("W3");
            case   11: return QString("Sync");
            case   12: return QString("ChanelStat");
            case   13: return QString("Multiplex");
            case   14: return QString("CRC16");
            case   15: return QString("CRC16_check");
        }
        return QVariant();
    }
    else return section; //for vertical
}

void DataModel::addTableData(IBLData t)
{
    tableData.append(t);

    emit    layoutAboutToBeChanged();   // собираюсь внести изменения в таблицу!!
    emit    layoutChanged();            // внести изменения
}

int DataModel::count()
{
    return tableData.length();
}

void DataModel::clear()
{
    tableData.clear();
    emit    layoutAboutToBeChanged();   // собираюсь внести изменения в таблицу!!
    emit    layoutChanged();            // внести изменения
}
