#ifndef RASTERWINDOW_H
#define RASTERWINDOW_H

#include <QtGui>

Q_DECLARE_LOGGING_CATEGORY(RASTERWINDOW);

class RasterWindow : public QRasterWindow
{
Q_OBJECT
public:
     Q_INVOKABLE RasterWindow();

    virtual void paintEvent(QPaintEvent * event);

    virtual void exposeEvent(QExposeEvent * ev);
    virtual void focusInEvent(QFocusEvent * ev);
    virtual void focusOutEvent(QFocusEvent * ev);
    virtual void hideEvent(QHideEvent * ev);
    virtual void keyPressEvent(QKeyEvent * ev);
    virtual void keyReleaseEvent(QKeyEvent * ev);
    virtual void mouseDoubleClickEvent(QMouseEvent * ev);
    virtual void mouseMoveEvent(QMouseEvent * ev);
    virtual void mousePressEvent(QMouseEvent * ev);
    virtual void mouseReleaseEvent(QMouseEvent * ev);
    virtual void moveEvent(QMoveEvent * ev);
//    virtual bool nativeEvent(const QByteArray & eventType, void * message, long * result);
    virtual void resizeEvent(QResizeEvent * ev);
    virtual void showEvent(QShowEvent * ev);
    virtual void tabletEvent(QTabletEvent * ev);
    virtual void touchEvent(QTouchEvent * ev);
    virtual void wheelEvent(QWheelEvent * ev);
private:
    void incrementEventCount();
    int m_eventCount;
    QPoint m_offset;
    QPoint m_lastPos;
    bool m_pressed;
};

// Q_DECLARE_METATYPE(RasterWindow)

#endif // RASTERWINDOW_H
