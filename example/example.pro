include (../qtwindowcontrolleritem.pri)

CONFIG -= app_bundle

OBJECTS_DIR = .obj
MOC_DIR = .moc

HEADERS += \
    rasterwindow.h

SOURCES += \
    rasterwindow.cpp \
    main.cpp

OTHER_FILES += main.qml
