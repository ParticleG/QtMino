import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.15

import ParticleG.QtMino.Core 1.0

ApplicationWindow {
    property alias mainStackView: main_stackView
    property alias mainGameManager: main_gameManager
    id: main_applicationWindow
    visible: true
    width: (Qt.platform.os === "windows" || Qt.platform.os === "linux" || Qt.platform.os === "osx") ? 1280 : 720
    height: (Qt.platform.os === "windows" || Qt.platform.os === "linux" || Qt.platform.os === "osx") ? 720 : 1280
    title: qsTr("QtMino")
    flags: Qt.Window | Qt.MaximizeUsingFullscreenGeometryHint

    GameManager {
        id: main_gameManager
        anchors.fill: parent
    }

    StackView {
        id: main_stackView
        initialItem: "TitleStackView.qml"
        anchors.fill: parent
    }

    Component.onCompleted: {
        main_gameManager.loadSettings()
    }
}
