import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import QtQuickWindowControl 0.1

Rectangle {
    width : 640
    height: 580

    WindowController {
        windowClassName: "RasterWindow"

        anchors.centerIn: parent
        width : 320
        height: 200
    }
}

