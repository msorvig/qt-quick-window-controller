#ifndef QTWINDOWCONTROLLERITEM_H
#define QTWINDOWCONTROLLERITEM_H

#include <QtCore/QLoggingCategory>
#include <QtQuick/QQuickItem>

Q_DECLARE_LOGGING_CATEGORY(QT_QUICK_WINDOW_CONTROLLER);

class QtWindowControllerItem : public QQuickItem
{
    Q_OBJECT
public:
    Q_PROPERTY(QString windowClassName MEMBER m_windowClassName);

    explicit QtWindowControllerItem(QQuickItem *parent = 0);
    void setWindow(QWindow *window);
    void componentComplete() Q_DECL_OVERRIDE;
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) Q_DECL_OVERRIDE;

public slots:
    void onWindowChanged(QQuickWindow* window);
    void onVisibleChanged();

private:
    QString m_windowClassName;
    QWindow *m_controlledWindow;
    QRect m_geometry;
};

#endif // QTWINDOWCONTROLLERITEM_H
