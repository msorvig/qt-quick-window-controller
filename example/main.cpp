#include <QtGui>
#include <QtQuick>

#include "qtwindowcontrolleritem.h"
#include "rasterwindow.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    // in lieu of qpm module registration support, register here
    qmlRegisterType<QtWindowControllerItem>("QtQuickWindowControl", 0, 1, "WindowController");

    qRegisterMetaType<RasterWindow*>("RasterWindow");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.setSource(QUrl("qrc:///main.qml"));
    view.setSource(QUrl("main.qml"));
    view.show();

    return app.exec();
}
