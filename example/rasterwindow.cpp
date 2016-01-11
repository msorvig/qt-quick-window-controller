#include "rasterwindow.h"

Q_LOGGING_CATEGORY(RASTERWINDOW, "qt.rasterwindow"); // "qt" prefix to get off-by-default behavior.

RasterWindow::RasterWindow()
:m_eventCount(0)
,m_pressed(false)
{

}

void RasterWindow::paintEvent(QPaintEvent * event)
{
    QRect r = event->rect();
    QPainter p(this);

    QColor fillColor(0, 102, 153);
    QColor fillColor2(0, 85, 123);

    int tileSize = 40;
    for (int i = -tileSize * 2; i < r.width() + tileSize * 2; i += tileSize) {
        for (int j = -tileSize * 2; j < r.height() + tileSize * 2; j += tileSize) {
            QRect rect(i + (m_offset.x() % tileSize * 2), j + (m_offset.y() % tileSize * 2), tileSize, tileSize);
            int colorIndex = abs((i/tileSize - j/tileSize) % 2);
            p.fillRect(rect, colorIndex == 0 ? fillColor : fillColor2);
        }
    }

    QRect g = geometry();
    QRect sg = this->screen()->geometry();
    QString text;
    text += QString("Window Geometry: %1 %2 %3 %4\n").arg(g.x()).arg(g.y()).arg(g.width()).arg(g.height());
    text += QString("Window devicePixelRatio: %1\n").arg(devicePixelRatio());
    text += QString("Screen Geometry: %1 %2 %3 %4\n").arg(sg.x()).arg(sg.y()).arg(sg.width()).arg(sg.height());
    text += QString("Received Event Count: %1\n").arg(m_eventCount);

    p.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, text);
}
void RasterWindow::exposeEvent(QExposeEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::exposeEvent(ev);
    incrementEventCount();
}

void RasterWindow::focusInEvent(QFocusEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::focusInEvent(ev);
    incrementEventCount();
}

void RasterWindow::focusOutEvent(QFocusEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::focusOutEvent(ev);
    incrementEventCount();
}

void RasterWindow::hideEvent(QHideEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::hideEvent(ev);
    incrementEventCount();
}

void RasterWindow::keyPressEvent(QKeyEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::keyPressEvent(ev);
    incrementEventCount();
}

void RasterWindow::keyReleaseEvent(QKeyEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::keyReleaseEvent(ev);
    incrementEventCount();
}

void RasterWindow::mouseDoubleClickEvent(QMouseEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::mouseDoubleClickEvent(ev);
    incrementEventCount();
}

void RasterWindow::mouseMoveEvent(QMouseEvent * ev)
{
//     qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::mouseMoveEvent(ev);
    incrementEventCount();

    if (m_pressed)
        m_offset += ev->localPos().toPoint() - m_lastPos;
    m_lastPos = ev->localPos().toPoint();
}

void RasterWindow::mousePressEvent(QMouseEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::mousePressEvent(ev);
    incrementEventCount();
    m_pressed = true;
}

void RasterWindow::mouseReleaseEvent(QMouseEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::mouseReleaseEvent(ev);
    incrementEventCount();
    m_pressed = false;
}

void RasterWindow::moveEvent(QMoveEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__ << ev->pos();
    QRasterWindow::moveEvent(ev);
    incrementEventCount();
}

void RasterWindow::resizeEvent(QResizeEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__ << ev->size();
    QRasterWindow::resizeEvent(ev);
    incrementEventCount();
}

void RasterWindow::showEvent(QShowEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::showEvent(ev);
    incrementEventCount();
}

void RasterWindow::tabletEvent(QTabletEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::tabletEvent(ev);
    incrementEventCount();
}

void RasterWindow::touchEvent(QTouchEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::touchEvent(ev);
    incrementEventCount();
}

void RasterWindow::wheelEvent(QWheelEvent * ev)
{
    qCDebug(RASTERWINDOW) << __PRETTY_FUNCTION__;
    QRasterWindow::wheelEvent(ev);
    incrementEventCount();
}

void RasterWindow::incrementEventCount()
{
    ++m_eventCount;
    update();
}
