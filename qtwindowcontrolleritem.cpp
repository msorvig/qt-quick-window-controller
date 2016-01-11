#include "qtwindowcontrolleritem.h"

#include <QtGui/QWindow>
#include <QtQuick/QQuickWindow>

Q_LOGGING_CATEGORY(QT_QUICK_WINDOW_CONTROLLER, "qt.quick.window.controller");

QtWindowControllerItem::QtWindowControllerItem(QQuickItem *parent)
    : QQuickItem(parent)
    , m_controlledWindow(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(onWindowChanged(QQuickWindow*)));
    connect(this, SIGNAL(visibleChanged()), this, SLOT(onVisibleChanged()));
}

void QtWindowControllerItem::setWindow(QWindow *window)
{
    qCDebug(QT_QUICK_WINDOW_CONTROLLER) << "QtWindowControllerItem::setWindow" << window;
    m_controlledWindow = window;
}

void QtWindowControllerItem::componentComplete()
{
    qCDebug(QT_QUICK_WINDOW_CONTROLLER) << "QtWindowControllerItem::componentComplete";

    QQuickItem::componentComplete();

    qCDebug(QT_QUICK_WINDOW_CONTROLLER) << "instantiating QWindow with class name" << m_windowClassName;

    // Create a window instance from the class name via the
    // Qt meta type and meta object system.
    int id = QMetaType::type(m_windowClassName.toLatin1());
    if (id  == QMetaType::UnknownType) {
        qWarning() << "QtWindowControllerItem: QMetaType for m_windowClassName not found."
                   << "Register with qRegisterMetaType<" + m_windowClassName + "*>(" + m_windowClassName + ");.";
        return;
    }
    QMetaType info(id);
    const QMetaObject *mo = info.metaObject();
    QObject *obj = mo->newInstance();

    m_controlledWindow = static_cast<QWindow *>(obj);
    m_controlledWindow->setGeometry(m_geometry);
}

void QtWindowControllerItem::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickItem::geometryChanged(newGeometry, oldGeometry);
    qCDebug(QT_QUICK_WINDOW_CONTROLLER) << "QtWindowControllerItem::geometryChanged" << newGeometry << oldGeometry;
    m_geometry = newGeometry.toRect();

    if (!m_controlledWindow)
        return;
    m_controlledWindow->setGeometry(m_geometry);
}

void QtWindowControllerItem::onWindowChanged(QQuickWindow* window)
{
    qCDebug(QT_QUICK_WINDOW_CONTROLLER) << "QtWindowControllerItem::onWindowChanged" << window;

    if (!m_controlledWindow)
        return;
    

    if (!window) {
        m_controlledWindow->setVisible(false);
    }

    m_controlledWindow->setParent(window);

    if (window) {
        // ### Do child windows need a setVisible call?  At least on OS X they do, along with
        // this bugfix: codereview.qt-project.org/#/c/145969/
        m_controlledWindow->setVisible(isVisible());
    }
}

void QtWindowControllerItem::onVisibleChanged()
{
    qCDebug(QT_QUICK_WINDOW_CONTROLLER) << "QtWindowControllerItem::onVisibleChanged" << isVisible();
    if (!m_controlledWindow)
        return;

    m_controlledWindow->setVisible(isVisible());
}
