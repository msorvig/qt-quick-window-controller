Qt Quick Window Controller
==========================

WindowController is a Qt Quick item that controls QWindow instances:

    Rectangle {
        width : 640
        height: 480
        
        WindowController {
            windowClassName : "MyCustomWindow"
            anchors.centerIn: parent
            width : 320
            height : 200
        }
    }

The WindowController is a part of the QML hierarchy, but the corresponding
Qt Quick item is not; the QWindow is instead layered on top of the Qt Quick
scene. This layering uses the native window layering from the Qt platform
plugin. 

OS X note: On current versions of Qt you probably want to enable Core Animation
layers, and disable multithreaded Qt Quick rendering:

    QT_MAC_WANTS_LAYER=1 QSG_RENDER_LOOP=basic ./example

OS X Window creation fix: https://codereview.qt-project.org/145969

The actual QWindow subclass is set by specifying the class name. As a requirement
for this the QWindow type needs to be registered with the Qt meta-type system
[do this somewhere in main()]:

    qRegisterMetaType<CustomWindow*>("CustomWindow");

On the C++ side there is an alternative API where you can set the QWindow
instance directly on the controller object.
    
    QtQuickWindowController *controller = new QtQuickWindowController();
    controller.setWindow(new ApplicationWindow);

Logging can be enabled via the "qt.quick.window.controller" category:

    QT_LOGGING_RULES=qt.quick.window.controller.debug=true

