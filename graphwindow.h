#ifndef GRAPHIWINDOW_H
#define GRAPHIWINDOW_H


#define TIME_STEP 1.0f  // Частота отображения

#include "ibldata.h"
#include <QWidget>
#include <QLayout>

#include "chart.h"
#include <QPoint>

#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

class GraphWindow : public QChartView
{
    Q_OBJECT
public:
    explicit GraphWindow(QList<quint8> sCols, QWidget *parent = 0);
    void setData(IBLData iblData);
    void repaintGraph();
signals:

public slots:

private:
    Chart *chart;

    QList<quint8> selectedColumns;

    // Контейнер для всех контейнеров с данными для графиков
    QList<QLineSeries*> lineSeries;

    // Контейнеры для всех осреденений (в т.ч. без) выбранных полей
    QList<QList<QPointF>*> graphicsData;
    QList<QList<QPointF>*> graphicsAverageData;
    int countAverageData;

    // Оси
    QValueAxis *axisX;
    QValueAxis *axisY;

    QChartView *chartView;

    void setter(quint8 n, qreal count, qreal value);

    qreal maxY;
    qreal minY;

    bool m_isTouching;

protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void wheelEvent(QWheelEvent * event);
};

#endif // GRAPHIWINDOW_H
