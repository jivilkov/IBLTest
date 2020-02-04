#ifndef ICGRAPHFRAME_H
#define ICGRAPHFRAME_H

#include "icmvisual_global.h"

#include <QFrame>
#include "icdatapaint.h"

class ICMVISUALSHARED_EXPORT ICGraphFrame : public QFrame
{
    Q_OBJECT
public:
    explicit ICGraphFrame(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ICGraphFrame();
    void contextMenuEvent(QContextMenuEvent *event);
    ICDataPaint *graphDataPaint();
    void setGraphTitle(QString title);
    QString graphTitle();
    void setGraphAxX(QString title);
    QString graphAxX();
    void setGraphAxY(QString title);
    QString graphAxY();
    void setGraphLabels(QStringList labels);
    QStringList graphLabels();
    void setLabelsOverride(bool override);
    bool labelsOverride();
    void setGraphPixelSize (int size);
    int graphPixelSize();
    void setGraphAxXSteps(int steps);
    int graphAxXSteps();
    void setGraphAxYSteps(int steps);
    int graphAxYSteps();
    void setGraphFixYStep (bool fix);
    bool graphFixYStep();
    void setGraphYStep (double step);
    double graphYStep();
    void setTimeFormat (QString format);
    QString timeFormat();
    void setXYScroll(bool allow);
    bool isXYScroll();

    Q_PROPERTY(QString graphTitle READ graphTitle WRITE setGraphTitle)
    Q_PROPERTY(QString graphAxX READ graphAxX WRITE setGraphAxX)
    Q_PROPERTY(QString graphAxY READ graphAxY WRITE setGraphAxY)
    Q_PROPERTY(QStringList graphLabels READ graphLabels WRITE setGraphLabels)
    Q_PROPERTY(bool labelsOverride READ labelsOverride WRITE setLabelsOverride)
    Q_PROPERTY(int graphPixelSize READ graphPixelSize WRITE setGraphPixelSize)
    Q_PROPERTY(int graphAxXSteps READ graphAxXSteps WRITE setGraphAxXSteps)
    Q_PROPERTY(int graphAxYSteps READ graphAxYSteps WRITE setGraphAxYSteps)
    Q_PROPERTY(bool graphFixYStep READ graphFixYStep WRITE setGraphFixYStep)
    Q_PROPERTY(double graphYStep READ graphYStep WRITE setGraphYStep)
    Q_PROPERTY(QString timeFormat READ timeFormat WRITE setTimeFormat)
    Q_PROPERTY(bool allowXYscroll READ isXYScroll WRITE setXYScroll)


protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

    ICDataPaint *dataPaint;
    QPainter dataPainter;
    QPoint mousePressPos;
    QPoint mouseZoomPos;
    bool mouseDraging;
    bool mouseZooming;
    QStringList graphTempLabels;
    bool labelOverride;
    bool XYScroll;

    virtual void paintEvent(QPaintEvent *event);
};

#endif // ICGRAPHFRAME_H
