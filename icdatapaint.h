#ifndef ICDATAPAINT_H
#define ICDATAPAINT_H

#include "icmvisual_global.h"

#include <QPainter>
#include "../ICAlgorithm/icdatacontainer.h"

class ICMVISUALSHARED_EXPORT ICDataPaint : public QObject
{
    Q_OBJECT
public:
    static const int   WIDGET_MODE = 1001;
    static const int   PRINTER_MODE = 1002;

    ICDataPaint();
    void setRenderMode(int m);
    void setDataContainer(QList<ICDataContainer*> container);
    void setDataContainer(ICDataContainer *container);
    void addDataContainer(ICDataContainer *container);
    void clearContainers();
    ICDataContainer *dataContainer(int index);
    int dataContainerCount();
    void setPainter(QPainter *painter);
    void setRenderRect(QRect r);
    void setRangeRect(QRectF r);
    void setGraphTitle(QString title);
    void setAxXTitle(QString title);
    void setAxYTitle(QString title);
    QString getGraphTitle();
    QString getAxXTitle();
    QString getAxYTitle();
    void renderGraph(QPainter *painter = NULL, QRect render = QRect(), QRectF range = QRectF(), int mode = 0);
    void zoomGraph(float zoomX, float zoomY);
    void zoomGraph(QRect r);
    void moveGraph(float x, float y);
    void resetRangeRect();
    void moveGraphXY(int x, int y);
    void setZoomWindow(QRect r);
    void clearZoomWindow();
    void applyZoomWindow();
    QRect zoomWindow();
    void setVisible(int index, bool visible);
    bool isVisible(int index);
    QRect renderRect();
    QRectF rangeRect();
    QRectF defaulRangeRect();
    void setGraphNameTemplates (QStringList temp);
    void updateRangeRect();    
    void setPixelSize(int size);
    int pixelSize();
    void setAxXSteps(int steps);
    int axXSteps();
    void setAxYSteps(int steps);
    int axYSteps();
    void setFixYStep (bool fix);
    bool fixYStep();
    void setYStep (double step);
    double YStep();
    void setTimeFormat(QString format);
    QString timeFormat();
    void setMargin(float m) { margin = m; }

public slots:
    void updateData();

protected:
    QList<ICDataContainer*> graphContainer;
    int renderMode;
    int ignore_delay;
    float margin;
    QPainter *graphPainter;
    QRect renderingRect, zoomRect;
    QRectF graphRange;
    QRectF defaultRect;
    QString graphTitle;
    QString axXTitle;
    QString axYTitle;
    QString tmFormat;
    bool fixedScale;
    bool zoomRectShow;
    QStringList graphNameTemp;
    int graphPixelSize;
    int graphAxXSteps;
    int graphAxYSteps;
    bool graphFixYStep;
    double graphYStep;

};

#endif // ICDATAPAINT_H
