#ifndef DATAMODEL_H
#define DATAMODEL_H

#define COL_SIZE 16

#include "ibldata.h"

#include <QAbstractTableModel>
#include <QTime>
#include <QList>

class DataModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    DataModel();
    ~DataModel();

    void addTableData(IBLData t);
    int count();

private:
    int             rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int             columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant        data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant        headerData(int section, Qt::Orientation orientation, int role) const;
    QList <IBLData> tableData;
};

#endif // DATAMODEL_H
