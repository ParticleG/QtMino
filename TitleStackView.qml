import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

Page {
    Button {
        anchors.centerIn: parent
        text: "Start Game"
        onClicked: {
            mainStackView.push("SoloGameStackView.qml")
            mainGameManager.exportSettings()
        }
    }
}
