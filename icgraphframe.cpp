#include "icgraphframe.h"
#include "icgraphsettings.h"
#include <QMouseEvent>
#include <QDebug>
#include <QMenu>

ICGraphFrame::ICGraphFrame(QWidget* parent, Qt::WindowFlags f) :
    QFrame(parent,f)
{
    dataPaint = new ICDataPaint();
    dataPaint->setPainter(&dataPainter);
    setMouseTracking(true);
    mouseDraging = false;
    mouseZooming = false;
    labelOverride = false;
    XYScroll = false;
}

ICGraphFrame::~ICGraphFrame()
{
    if (dataPaint) delete dataPaint;
}

void ICGraphFrame::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu   menu(this);
    QList<QAction*> actions;
    ICDataContainer *cont;
    bool fl = false;

    if (dataPaint) {
        for (int i = 0; i < dataPaint->dataContainerCount(); i++) {
            cont = dataPaint->dataContainer(i);
            if (cont) {
                if (cont->isVisible()) {
                    actions.append(menu.addAction(tr("Hide ") + cont->graphName()));
                }
                else {
                    actions.append(menu.addAction(tr("Show ") + cont->graphName()));
                }
            }
            actions[i]->setCheckable(true);
            actions[i]->setChecked(cont->isVisible());
        }
        actions.append(menu.addAction(tr("Zoom in")));
        actions.append(menu.addAction(tr("Zoom out")));
        actions.append(menu.addAction(tr("Auto zoom")));
        actions.append(menu.addAction(tr("Settings")));

        //Какой канал был включен-выключен?
        QAction *result = menu.exec(event->globalPos());
        for (int i = 0; i < dataPaint->dataContainerCount(); i++) {
            if (result == actions.at(i)) {
                cont = dataPaint->dataContainer(i);
                if (cont) {
                    cont->setVisible(!cont->isVisible());
                    fl = true;
                }
            }
        }

        if (actions.count() >= 4) {
            if (result == actions.at(actions.count()-2)) {
                dataPaint->resetRangeRect();
                repaint();
            }
            if (result == actions.at(actions.count()-3)) {
                dataPaint->zoomGraph(1,2);
                repaint();
            }
            if (result == actions.at(actions.count()-4)) {
                dataPaint->zoomGraph(1,0.5);
                repaint();
            }
        }
        if (result == actions.last()) {
            ICGraphSettings dlg;
            dlg.setDataPaint(dataPaint);
            if (labelOverride) {
                dlg.setGraphTempNames(graphTempLabels);
            }
            else {
                dlg.setGraphTempNames(QStringList());
            }
            if (XYScroll) dlg.setXYScroll(XYScroll);
            if (dlg.exec()) {
                dlg.applySettings();
                labelOverride = dlg.isLabelsOverride();
                if (labelOverride) {
                    graphTempLabels = dlg.graphTempNames();
                    dataPaint->setGraphNameTemplates(graphTempLabels);
                }
                XYScroll = dlg.isXYScroll();
                fl = true;
            }
        }
        actions.clear();
        if (fl) repaint();
    }
}

ICDataPaint *ICGraphFrame::graphDataPaint()
{
    return dataPaint;
}

void ICGraphFrame::setGraphTitle(QString title)
{
    if (dataPaint)
        dataPaint->setGraphTitle(title);
}

QString ICGraphFrame::graphTitle()
{
    QString str;
    if (dataPaint)
        str = dataPaint->getGraphTitle();
    return str;
}

void ICGraphFrame::setGraphAxX(QString title)
{
    if (dataPaint)
        dataPaint->setAxXTitle(title);
}

QString ICGraphFrame::graphAxX()
{
    QString str;
    if (dataPaint)
        str = dataPaint->getAxXTitle();
    return str;
}

void ICGraphFrame::setGraphAxY(QString title)
{
    if (dataPaint)
        dataPaint->setAxYTitle(title);
}

QString ICGraphFrame::graphAxY()
{
    QString str;
    if (dataPaint)
        str = dataPaint->getAxYTitle();
    return str;
}

void ICGraphFrame::setLabelsOverride(bool override)
{
    labelOverride = override;
    if (dataPaint) {
        if (labelOverride) {
            dataPaint->setGraphNameTemplates(graphTempLabels);
        }
        else {
            dataPaint->setGraphNameTemplates(QStringList());
        }
    }
}

bool ICGraphFrame::labelsOverride()
{
    return labelOverride;
}

void ICGraphFrame::setGraphPixelSize(int size)
{
    if (dataPaint)
        dataPaint->setPixelSize(size);
}

int ICGraphFrame::graphPixelSize()
{
    if (dataPaint)
        return dataPaint->pixelSize();
    return 1;
}

void ICGraphFrame::setGraphAxXSteps(int steps)
{
    if (dataPaint)
        dataPaint->setAxXSteps(steps);
}

int ICGraphFrame::graphAxXSteps()
{
    if (dataPaint)
        return dataPaint->axXSteps();
    return 10;
}

void ICGraphFrame::setGraphAxYSteps(int steps)
{
    if (dataPaint)
        dataPaint->setAxYSteps(steps);
}

int ICGraphFrame::graphAxYSteps()
{
    if (dataPaint)
        return dataPaint->axYSteps();
    return 10;
}

void ICGraphFrame::setGraphFixYStep(bool fix)
{
    if (dataPaint)
        dataPaint->setFixYStep(fix);
}

bool ICGraphFrame::graphFixYStep()
{
    if (dataPaint)
        return dataPaint->fixYStep();
    return false;
}

void ICGraphFrame::setGraphYStep(double step)
{
    if (dataPaint)
        dataPaint->setYStep(step);
}

double ICGraphFrame::graphYStep()
{
    if (dataPaint)
        return dataPaint->YStep();
    return 0.01;
}

void ICGraphFrame::setTimeFormat(QString format)
{
    if (dataPaint)
        return dataPaint->setTimeFormat(format);
}

QString ICGraphFrame::timeFormat()
{
    if (dataPaint)
        return dataPaint->timeFormat();
    return QString("HH:mm:ss");
}

void ICGraphFrame::setXYScroll(bool allow)
{
    XYScroll = allow;
}

bool ICGraphFrame::isXYScroll()
{
    return XYScroll;
}

void ICGraphFrame::setGraphLabels(QStringList labels)
{
    graphTempLabels = labels;
    if (dataPaint) {
        if (labelOverride) {
            dataPaint->setGraphNameTemplates(graphTempLabels);
        }
        else {
            dataPaint->setGraphNameTemplates(QStringList());
        }
    }
}

QStringList ICGraphFrame::graphLabels()
{
    return graphTempLabels;
}

void ICGraphFrame::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() && Qt::LeftButton) {
        if (event->modifiers() && Qt::CTRL) {
            if (mouseZooming) {
                QRect r;
                r.setLeft(std::min(mouseZoomPos.x(),event->pos().x()));
                r.setTop(std::min(mouseZoomPos.y(),event->pos().y()));
                r.setWidth(std::abs(mouseZoomPos.x()-event->pos().x()));
                r.setHeight(std::abs(mouseZoomPos.y()-event->pos().y()));
                dataPaint->setZoomWindow(r);
                event->accept();
                repaint();
            }
        }
        else {
            if (mouseDraging) {
                QPoint pnt = event->pos();
                dataPaint->moveGraphXY(mousePressPos.x()-pnt.x(),mousePressPos.y()-pnt.y());
                mousePressPos = pnt;
                event->accept();
                repaint();
            }
        }
    }
    if(!event->isAccepted()) {
        if (mouseZooming) {
            dataPaint->applyZoomWindow();
            repaint();
        }
        mouseDraging = false;
        mouseZooming = false;
        QFrame::mouseMoveEvent(event);
    }
}

void ICGraphFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MidButton) {
        dataPaint->resetRangeRect();
        event->accept();
        repaint();
    }
    else if(event->button() == Qt::LeftButton) {
        if (event->modifiers() && Qt::CTRL) {
            mouseZoomPos = event->pos();
            mouseZooming = true;
        }
        else {
            mousePressPos = event->pos();
            mouseDraging = true;
        }
    }
    else {
        QFrame::mousePressEvent(event);
    }
}

void ICGraphFrame::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() && Qt::CTRL) {
            if (mouseZooming) {
                if ((dataPaint->zoomWindow().height() < 5)&&(dataPaint->zoomWindow().width() < 5)) {
                    dataPaint->clearZoomWindow();
                }
                else {
                    dataPaint->applyZoomWindow();
                }
                repaint();
            }
            mouseZooming = false;
        }
        mouseDraging = false;
    }
}

void ICGraphFrame::wheelEvent(QWheelEvent *event)
{
    if ((dataPaint)) {
        float x = 0;
        float y = event->delta()/120;
        if (XYScroll) {
            x = event->angleDelta().x()/120.0;
            y = event->angleDelta().y()/120.0;
        }
        if (event->modifiers() == Qt::ControlModifier) {
            y = ((2.0-y)/2.0);
            x = ((2.0-x)/2.0);
            dataPaint->zoomGraph(x,y);
            event->accept();
            repaint();
        }
        else if (event->modifiers() == Qt::AltModifier) {
            y = ((2.0+y)/2.0);
            x = ((2.0+x)/2.0);
            dataPaint->zoomGraph(y,x);
            event->accept();
            repaint();
        }
        else if (event->modifiers() == Qt::ShiftModifier) {
            dataPaint->moveGraph(-y,-x);
            event->accept();
            repaint();
        }
        else {
            dataPaint->moveGraph(x,y);
            event->accept();
            repaint();
        }
    }
    else {
        QFrame::wheelEvent(event);
    }
}

void ICGraphFrame::paintEvent(QPaintEvent *event)
{
    if (dataPaint) {
        dataPaint->setRenderRect(this->rect());
        dataPainter.begin(this);
        dataPaint->setPainter(&dataPainter);
        dataPaint->renderGraph();
        dataPainter.end();
        event->accept();
    }
}
