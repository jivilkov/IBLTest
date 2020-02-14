#include "graphwindow.h"
#include <QtGui/QMouseEvent>

#define ALIGN_POINTS 100.0f
#define SCALE_HORIZONT_SCROLLING 100.0f

GraphWindow::GraphWindow(QList<quint8> sCols, QWidget *parent) : QChartView(parent), m_isTouching(false)
{
    chart = new Chart();
    chart->setAnimationOptions(QChart::NoAnimation);
    setRubberBand(QChartView::RectangleRubberBand);

    // Create series for select cols
    selectedColumns = sCols;

    for (int i=0; i<selectedColumns.length(); i++) {
        graphicsData.append(new QList<QPointF>);
        graphicsAverageData.append(new QList<QPointF>);
        QLineSeries *s = new QLineSeries();
        s->setUseOpenGL(false);
        lineSeries.append(s);
        chart->addSeries(lineSeries.at(i));
    }

    chart->createDefaultAxes();

    this->setChart(chart);
    this->setRenderHint(QPainter::Antialiasing);
}

void GraphWindow::setData(IBLData iblData)
{

    for (int i=0; i<selectedColumns.length(); i++){
        switch (selectedColumns.at(i)){
            case 0: setter(i, iblData.counter, iblData.head); break;
            case 1: setter(i, iblData.counter, iblData.counter); break;
            case 2: setter(i, iblData.counter, iblData.speedAcc1); break;
            case 3: setter(i, iblData.counter, iblData.speedAcc2); break;
            case 4: setter(i, iblData.counter, iblData.speedAcc3); break;
            case 5: setter(i, iblData.counter, iblData.countAcc1); break;
            case 6: setter(i, iblData.counter, iblData.countAcc2); break;
            case 7: setter(i, iblData.counter, iblData.countAcc3); break;
            case 8: setter(i, iblData.counter, iblData.angleInW1); break;
            case 9: setter(i, iblData.counter, iblData.angleInW2); break;
            case 10: setter(i, iblData.counter, iblData.angleInW3); break;
            case 11: setter(i, iblData.counter, iblData.syncLength); break;
        }
    }
}

void GraphWindow::setter(quint8 n, qreal count, qreal value){

    QPointF point(count, value);
    graphicsData[n]->append(point);

    // AVERAGE
    if (graphicsData.at(n)->count() >= ALIGN_POINTS) {
        qreal count=0;
        qreal value=0;

        for (int i=0; i<ALIGN_POINTS; i++){
             qreal x, y;
             x = graphicsData.at(n)->at(i).x();
             y = graphicsData.at(n)->at(i).y();
             count += x / ALIGN_POINTS;
             value += y / ALIGN_POINTS;
        }

        QPointF midPoint(count, value);
        graphicsAverageData[n]->append(midPoint);
        graphicsData.at(n)->clear();
    }
}

bool GraphWindow::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}

void GraphWindow::mousePressEvent(QMouseEvent *event)
{
    if (m_isTouching) return;
    QChartView::mousePressEvent(event);
}

void GraphWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isTouching) return;
    QChartView::mouseMoveEvent(event);
}

void GraphWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isTouching) m_isTouching = false;

    // Because we disabled animations when touch event was detected
    // we must put them back on.
    chart->setAnimationOptions(QChart::NoAnimation);
    QChartView::mouseReleaseEvent(event);
}

void GraphWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus: chart->zoomIn(); break;
    case Qt::Key_Minus: chart->zoomOut(); break;
    case Qt::Key_Left:
        //chart->axisX()->setMin(chart->axisX() - SCALE_HORIZONT_SCROLLING);
        //chart->axisX()->setMax(chart->axisX() - SCALE_HORIZONT_SCROLLING);


        //axisX->setMin(axisX->min() - SCALE_HORIZONT_SCROLLING);
        //axisX->setMax(axisX->max() - SCALE_HORIZONT_SCROLLING);
        break;
    case Qt::Key_Right:
        //axisX->setMin(axisX->min() + SCALE_HORIZONT_SCROLLING);
        //axisX->setMax(axisX->max() + SCALE_HORIZONT_SCROLLING);
        break;
    }
}

void GraphWindow::wheelEvent(QWheelEvent *event)
{
   qreal delta = event->delta();
   if (delta > 0) chart->zoomIn();
   else chart->zoomOut();
}

void GraphWindow::repaintGraph()
{
    for (int i=0; i<selectedColumns.length(); i++){
        lineSeries[i]->clear();
        lineSeries[i]->append(*graphicsAverageData.at(i));
    }
}
