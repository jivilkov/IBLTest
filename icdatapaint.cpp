#include "icdatapaint.h"
#include <QTranslator>
#include <QDebug>
#include <QPen>
#include <QTime>
#ifdef __APPLE__
#include <math.h>
#endif

#ifndef _GLIBCXX_MATH_H
#include <math.h>
#endif

QColor defaultColors[] = {Qt::darkGreen, Qt::blue, Qt::darkRed, Qt::darkCyan,  Qt::cyan, Qt::darkYellow,
                 Qt::darkBlue, Qt::red, Qt::green,  Qt::darkMagenta,
                 Qt::magenta, Qt::yellow};

ICDataPaint::ICDataPaint()
{
    renderMode = WIDGET_MODE;
    graphPainter = 0;
    axXTitle = tr("Time");
    axYTitle = tr("Value");
    graphTitle = tr("Graph");
    tmFormat = QString("HH:mm:ss");
    fixedScale = false;
    zoomRectShow = false;
    graphPixelSize = 1;
    graphAxXSteps = 10;
    graphAxYSteps = 10;
    graphFixYStep = false;
    graphYStep = 0.01;
    margin = 0;
}

void ICDataPaint::setRenderMode(int m)
{
    renderMode = m;
}

void ICDataPaint::setDataContainer(QList<ICDataContainer *> container)
{
    graphContainer = container;
    foreach (ICDataContainer *cont, graphContainer) {
        if (cont->color() == QColor()) {
            cont->setColor(defaultColors[graphContainer.count()]);
        }
        if (graphContainer.count() < graphNameTemp.count()) {
            cont->setGraphName(graphNameTemp.at(graphContainer.count()));
        }
    }

    updateRangeRect();
}

void ICDataPaint::setDataContainer(ICDataContainer *container) {
    clearContainers();
    addDataContainer(container);
}

void ICDataPaint::addDataContainer(ICDataContainer *container)
{
    if (container->color() == QColor()) {
        container->setColor(defaultColors[graphContainer.count()]);
    }
    if (graphContainer.count() < graphNameTemp.count()) {
        container->setGraphName(graphNameTemp.at(graphContainer.count()));
    }
    graphContainer.append(container);
    updateRangeRect();
}

void ICDataPaint::clearContainers()
{
    graphContainer.clear();
}

ICDataContainer *ICDataPaint::dataContainer(int index)
{
    if (index < graphContainer.count()) return graphContainer[index];
    return 0;
}

int ICDataPaint::dataContainerCount()
{
    return graphContainer.count();
}

void ICDataPaint::setPainter(QPainter *painter)
{
    graphPainter = painter;
}

void ICDataPaint::setRenderRect(QRect r)
{
    renderingRect = r;
    renderingRect.setLeft(renderingRect.left()+20);
    renderingRect.setTop(renderingRect.top()+25);
    renderingRect.setWidth(renderingRect.width()-20);
    renderingRect.setHeight(renderingRect.height()-20);
}

void ICDataPaint::setRangeRect(QRectF r)
{
    graphRange = r;
}

void ICDataPaint::setGraphTitle(QString title)
{
    graphTitle = title;
}

void ICDataPaint::setAxXTitle(QString title)
{
    axXTitle = title;
}

void ICDataPaint::setAxYTitle(QString title)
{
    axYTitle = title;
}

QString ICDataPaint::getGraphTitle()
{
    return graphTitle;
}

QString ICDataPaint::getAxXTitle()
{
    return axXTitle;
}

QString ICDataPaint::getAxYTitle()
{
    return axYTitle;
}

void ICDataPaint::renderGraph(QPainter *painter, QRect rend, QRectF rang, int mode)
{
    QPainter *paint;
    QRect render;
    QRectF range;
    int paintMode = renderMode;
    if ((mode == WIDGET_MODE)||(mode == PRINTER_MODE)) {
        paintMode = mode;
    }

    qDebug() << "renderGraph";

    if (painter) {
        paint = painter;

        if ((rend.width()>0)&&(rend.height()>0)) {
            render = rend;
            render.setLeft(render.left()+20);
            render.setTop(render.top()+25);
            render.setWidth(render.width()-20);
            render.setHeight(render.height()-20);
            if ((rang.width()>0)&&(rang.height()>0)) {
                range = rang;
            }
            else {
                range = graphRange;
            }
        }
        else {
            render = renderingRect;
            range = graphRange;
        }
    }
    else {
        paint = graphPainter;
        render = renderingRect;
        range = graphRange;
    }    

    if (paint&&(graphContainer.count()>0)) {        
        if (graphFixYStep) {            
            float middle = (range.top() + range.bottom())/2;
            middle = floor(middle/graphYStep)*graphYStep;
            range.setTop(middle-graphYStep*(float)graphAxYSteps/2.0f);
            range.setHeight(graphYStep*graphAxYSteps);

            qDebug() << "range fixed:" << range.bottom() << ":" << range.top();
        }
        QColor col(Qt::gray);
        QPen    p(col);
        p.setStyle(Qt::DashLine);
        p.setWidth(2);
        paint->setClipping(false);
        paint->setPen(p);

        paint->drawRect(render);

        QFont           f("Arial Narrow", 7);
        if (paintMode == WIDGET_MODE)
            f.setPointSize(10);

        QFontMetrics    fm(f);

        paint->setFont(f);

        p.setWidth(1);
        p.setColor(QColor(Qt::black));
        p.setStyle(Qt::SolidLine);
        paint->setPen(p);

        QRect           r_title = fm.boundingRect(graphTitle);
        QRect           r_vtitle = fm.boundingRect(axYTitle);
        QRect           r_htitle = fm.boundingRect(axXTitle);

        int             w = render.width();
        int             h = render.height();

        int             title_width = r_title.width();
        int             vtitle_width = r_vtitle.width();
        int             htitle_width = r_htitle.width();

        //Вывести заголовок
        paint->drawText(QPoint(w / 2 - title_width / 2 + render.x(), render.y() - 15), graphTitle);

        paint->rotate(90);
        paint->drawText(QPoint(h / 2 - vtitle_width / 2 + render.y(), -3 - render.x() - render.width()), axYTitle);
        paint->rotate(-90);

        paint->drawText(QPoint(render.x() + render.width() - htitle_width, render.y() - 2), axXTitle);

        //Вывести "легенду" если графиков больше чем 1
        if (graphContainer.count() > 1) {
            QList<double> legend_width;
            double full_width = 0;
            foreach(ICDataContainer *container, graphContainer) {
                QRect r_label = fm.boundingRect(QString("  ") + container->graphName() + QString("  "));
                legend_width.append(r_label.width());
                full_width += legend_width.last();
            }

            int label_x_pos = render.x() + w / 2 - full_width / 2, i = 0;

            foreach(ICDataContainer *container, graphContainer) {
                p.setColor(container->color());
                paint->setPen(p);
                paint->drawText(label_x_pos, render.y() - 2, QString("  ") + container->graphName() + QString("  "));
                label_x_pos += legend_width.at(i);
                i++;
            }
        }

        p.setColor(QColor(Qt::black));
        p.setStyle(Qt::SolidLine);
        paint->setPen(p);

        float           v_min = range.top();
        float           v_max = range.bottom();
        float           step = (v_max - v_min) / graphAxYSteps;

        //Если нет размаха минимум-максимум - то ахтунг, надо что-то делать
        if (step == 0) {
            v_min -= 0.1;
            v_max += 0.1;
        }

        //Чуть-чуть расширить картинку

        if (paintMode == PRINTER_MODE)
            f.setPointSize(4);
        else
            f.setPointSize(7);

        paint->setFont(f);

        for (int i = 0; i <= graphAxYSteps; i ++) {
            double       v = v_min + step * i;
            QString     v_string = QString::number(v, 'f', graphContainer.at(0)->timePrecision());
            int         y_pos = render.height() * (1.0f - (float)i / graphAxYSteps) + render.y();

            //Вывести метку на оси
            paint->drawText(2, y_pos, v_string);

            //Вывести линии уровня
            p.setStyle(Qt::DashDotDotLine);
            p.setColor(QColor(Qt::lightGray));
            paint->setPen(p);
            paint->drawLine(render.x(), y_pos, render.x() + render.width(), y_pos);
            p.setStyle(Qt::SolidLine);
            p.setColor(QColor(Qt::black));
            paint->setPen(p);
        }

        //Шкала времени
        double  t_start = range.left();
        double  t_finish = range.right();
        double  t_step = (t_finish - t_start) / graphAxXSteps;

        for (int i = 0; i <= graphAxXSteps; i++) {
            double  time_point = t_start + t_step * i;
            int     msec = ((int)(time_point*1000))%1000;
            int     sec = (int)time_point;
            int     hour = sec / 3600;
            int     min = (sec - hour * 3600) / 60;
            int     x_pos = render.x() + render.width() * (float)i / graphAxXSteps;
            sec %= 60;
            QTime tm = QTime(hour, min, sec, msec);

            QString time_label = tm.toString(tmFormat);
            QRect   r_label = fm.boundingRect(time_label);

            p.setStyle(Qt::DotLine);
            p.setColor(QColor(Qt::lightGray));
            paint->setPen(p);
            paint->drawLine(x_pos, render.y(), x_pos, render.y() + render.height());
            p.setStyle(Qt::SolidLine);
            p.setColor(QColor(Qt::black));
            paint->setPen(p);
            if (paintMode == PRINTER_MODE)
                paint->drawText(x_pos - r_label.width() / 2, render.y() + render.height() + 5, time_label);
            else
                paint->drawText(x_pos - r_label.width() / 2, render.y() + render.height() + 15, time_label);
        }


        //Уже отрисовка самого графика
        float scaleX, scaleY, x, y, x2, y2, ppx;
        long pcount, start;
        ICRange rg;
        paint->setClipping(true);
        paint->setClipRect(render);

        foreach(ICDataContainer *container, graphContainer) {

            if (container->isVisible()) {
                qDebug() << "*5";
                p.setColor(container->color());
                p.setWidth(graphPixelSize);
                paint->setPen(p);
                pcount = container->pointCount();
                start = 0;
                scaleY = (float)render.height() / range.height();
                while ((start < pcount)&&(container->timePoint(start)<range.left())) start++;
                while ((pcount > start)&&(container->timePoint(pcount)>(range.left()+range.width()))) pcount--;

                if (container->isTimeFixed()) {                    
                    scaleX = (float)render.width() / (pcount-start);
                    x = render.x(); x2 = render.x() + scaleX;
                    ppx = (float)(pcount-start) / (float)render.width();
                    if (ppx < 2e2) {
                        for (long i = start; i < pcount - 1; i ++) {
                            qDebug() << "*8";
                            y = (v_max - container->data(i)) * scaleY + render.top();
                            y2 = (v_max - container->data(i + 1)) * scaleY + render.top();
                            paint->drawLine(x, y, x2, y2);
                            x = x2;
                            x2 += scaleX;
                        }
                    }
                    else if (ppx < 1e4) {
                        scaleX *=1e2;
                        pcount /= 100;
                        start /= 100;
                        for (long i = start; i < pcount; i ++) {
                            rg = container->data100(i);
                            y = (v_max - rg.min) * scaleY + render.top();
                            y2 = (v_max - rg.max) * scaleY + render.top();
                            paint->drawLine(x, y, x, y2);
                            x += scaleX;
                        }
                    }
                    else if (ppx < 1e6) {
                        scaleX *=1e4;
                        pcount /= 10000;
                        start /= 10000;
                        for (long i = start; i < pcount; i ++) {
                            rg = container->data1e4(i);
                            y = (v_max - rg.min) * scaleY + render.top();
                            y2 = (v_max - rg.max) * scaleY + render.top();
                            paint->drawLine(x, y, x, y2);
                            x += scaleX;
                        }
                    }
                    else if (ppx < 1e8) {
                        scaleX *=1e6;
                        pcount /= 1000000;
                        start /= 1000000;
                        for (long i = start; i < pcount; i ++) {
                            rg = container->data1e6(i);
                            y = (v_max - rg.min) * scaleY + render.top();
                            y2 = (v_max - rg.max) * scaleY + render.top();
                            paint->drawLine(x, y, x, y2);
                            x += scaleX;
                        }
                    }
                    else {                        
                        scaleX *=1e8;
                        pcount /= 100000000;
                        start /= 100000000;
                        for (long i = start; i < pcount; i ++) {
                            rg = container->data1e8(i);
                            y = (v_max - rg.min) * scaleY + render.top();
                            y2 = (v_max - rg.max) * scaleY + render.top();
                            paint->drawLine(x, y, x, y2);
                            x += scaleX;
                        }
                    }
                }
                else {                    
                    scaleX = (float)render.width() / range.width();
                    y2 = (v_max - container->data(start)) * scaleY + render.top();
                    x2 = render.left();
                    qDebug() << "will paint " << pcount << " pointz";
                    for (long i = start; i < pcount - 1; i ++) {
                        x = x2; y = y2;
                        x2 = (container->timePoint(i)-container->timePoint(start))*scaleX + render.left();
                        y2 = (v_max - container->data(i + 1)) * scaleY + render.top();
                        paint->drawLine(x, y, x2, y2);
                    }
                }
            }

        }
        if (zoomRectShow&&(paintMode == WIDGET_MODE)) {
            p.setColor(QColor(Qt::black));
            paint->setPen(p);
            paint->drawRect(zoomRect);
        }

        p.setColor(QColor(Qt::gray));
        paint->setPen(p);
    }
}

void ICDataPaint::zoomGraph(float zoomX, float zoomY)
{
    graphRange.setLeft(graphRange.left()*zoomX);
    graphRange.setRight(graphRange.right()*zoomX);
    graphRange.setTop(graphRange.top()*zoomY);
    graphRange.setBottom(graphRange.bottom()*zoomY);
    if (graphRange.left() < defaultRect.left()) {
        graphRange.setLeft(defaultRect.left());
    }
    if (graphRange.width() > defaultRect.width()) {
        graphRange.setWidth(defaultRect.width());
    }
    if (graphRange.height() <= 0.0001) {
        graphRange.setHeight(0.0001);
    }
}

void ICDataPaint::zoomGraph(QRect r)
{
    if (graphContainer.count()) {
        if ((graphContainer.at(0))&&(r.width()>5)&&(r.height()>5)) {
            float scX, scY;
            scX = (graphRange.width()) / (float)renderingRect.width();
            scY = (graphRange.height()) / (float)renderingRect.height();
            float b = graphRange.bottom();
            graphRange.moveLeft(graphRange.left()+(r.left()-renderingRect.left())*scX);
            graphRange.setWidth(r.width()*scX);
            graphRange.setHeight(r.height()*scY);
            graphRange.moveBottom(b-(r.top()-renderingRect.top())*scY);
            if (graphRange.left() < defaultRect.left()) {
                graphRange.setLeft(defaultRect.left());
            }
            if (graphRange.right() > defaultRect.right()) {
                graphRange.setRight(defaultRect.right());
            }
        }
    }
}

void ICDataPaint::moveGraph(float x, float y)
{
    if (graphRange.width() < defaultRect.width()) {
        if ((graphRange.left()+graphRange.width() + graphRange.width()*x*0.01 >= defaultRect.width())) {
            graphRange.moveLeft(defaultRect.left()+defaultRect.width()-graphRange.width());
        }
        else {
            graphRange.moveLeft(graphRange.left() + graphRange.width()*x*0.01);
        }
    }
    graphRange.moveTop(graphRange.top() + graphRange.height()*y*0.01);
    if (graphRange.right() > defaultRect.right()) {
        graphRange.moveRight(defaultRect.right());
    }
    if (graphRange.left() < defaultRect.left()) {
        graphRange.moveLeft(defaultRect.left());
    }
    if (graphRange.width() > defaultRect.width()) {
        graphRange.setWidth(defaultRect.width());
    }
    if (graphRange.height() <= 0.0001) {
        graphRange.setHeight(0.0001);
    }
}

void ICDataPaint::resetRangeRect()
{
    graphRange = defaultRect;
}

void ICDataPaint::moveGraphXY(int x, int y)
{
    if (graphContainer.count()) {
        if (graphContainer.at(0)) {
            float ofsX, ofsY;
            ofsX = (float)x*(graphRange.right() - graphRange.left()) / (float)renderingRect.width();
            ofsY = (float)y*(graphRange.top() - graphRange.bottom()) / (float)renderingRect.height();
            if (graphRange.width() < defaultRect.width()) {
                if ((graphRange.left()+graphRange.width() + ofsX >= defaultRect.width())) {
                    graphRange.moveLeft(defaultRect.left()+defaultRect.width()-graphRange.width());
                }
                else {
                    graphRange.moveLeft(graphRange.left() + ofsX);
                }
            }
            graphRange.moveTop(graphRange.top() + ofsY);
            if (graphRange.left() < defaultRect.left()) {
                graphRange.moveLeft(defaultRect.left());
            }
            if (graphRange.width() > defaultRect.width()) {
                graphRange.setWidth(defaultRect.width());
            }
        }
    }
}

void ICDataPaint::setZoomWindow(QRect r)
{
    zoomRectShow = true;
    zoomRect = r;
}

void ICDataPaint::clearZoomWindow()
{
    zoomRectShow = false;
}

void ICDataPaint::applyZoomWindow()
{
    zoomGraph(zoomRect);
    clearZoomWindow();
}

QRect ICDataPaint::zoomWindow()
{
    return zoomRect;
}

void ICDataPaint::setVisible(int index, bool visible)
{
    if (index < graphContainer.count()) {
        graphContainer[index]->setVisible(visible);
    }
}

bool ICDataPaint::isVisible(int index)
{
    if (index < graphContainer.count()) {
        return graphContainer[index]->isVisible();
    }
    return false;
}

QRect ICDataPaint::renderRect()
{
    return renderingRect;
}

QRectF ICDataPaint::rangeRect()
{
    return graphRange;
}

QRectF ICDataPaint::defaulRangeRect()
{
    return defaultRect;
}

void ICDataPaint::setGraphNameTemplates(QStringList temp)
{
    graphNameTemp = temp;
}

void ICDataPaint::updateRangeRect()
{
    float minY = 0, maxY = 0;
    double minX = 0, maxX = 0;
    if (graphContainer.count()) {
        if (graphContainer.at(0)) {
            minY = graphContainer.at(0)->minValue();
            maxY = graphContainer.at(0)->maxValue();
            minX = graphContainer.at(0)->timePoint(0);
            maxX = graphContainer.at(0)->timePoint(graphContainer.at(0)->pointCount()-1);
        }
    }
    if (!fixedScale) {
        foreach(ICDataContainer *container, graphContainer) {
            if (container) {
                if (minY > container->minValue()) minY = container->minValue();
                if (maxY < container->maxValue()) maxY = container->maxValue();
                if (minX > container->timePoint(0)) minX = container->timePoint(0);
                if (maxX < container->timePoint(container->pointCount()-1)) maxX = container->timePoint(container->pointCount()-1);
            }
        }
        if (graphContainer.count()) {
            float ry = maxY-minY;
            if (ry == 0) {
                minY -= 0.1 + margin;
                maxY += 0.1 + margin;
            }
            else {
                minY -= ry*0.1 + margin;
                maxY += ry*0.1 + margin;
            }
            graphRange.setRect(minX,minY,maxX-minX,maxY-minY);
            defaultRect = graphRange;
        }
    }
}

void ICDataPaint::setPixelSize(int size)
{
    graphPixelSize = size;
}

int ICDataPaint::pixelSize()
{
    return graphPixelSize;
}

void ICDataPaint::setAxXSteps(int steps)
{
    graphAxXSteps = steps;
}

int ICDataPaint::axXSteps()
{
    return graphAxXSteps;
}

void ICDataPaint::setAxYSteps(int steps)
{
    graphAxYSteps = steps;
}

int ICDataPaint::axYSteps()
{
    return graphAxYSteps;
}

void ICDataPaint::setFixYStep(bool fix)
{
    graphFixYStep = fix;
}

bool ICDataPaint::fixYStep()
{
    return graphFixYStep;
}

void ICDataPaint::setYStep(double step)
{
    graphYStep = step;
}

double ICDataPaint::YStep()
{
    return graphYStep;
}

void ICDataPaint::setTimeFormat(QString format)
{
    tmFormat = format;
    if (tmFormat.isNull() || tmFormat.isEmpty() || (tmFormat == "")) {
        tmFormat = QString ("HH:mm:ss");
    }
}

QString ICDataPaint::timeFormat()
{
    return tmFormat;
}

void ICDataPaint::updateData()
{
    updateRangeRect();
}

