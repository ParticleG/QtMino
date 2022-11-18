import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12
import ParticleG.QtMino.Display 1.0

Page {
    Rectangle {
        id:_background
        anchors.fill:parent
        color: "dimgrey"
    }

    FieldManager {
        id: solo_fieldManager
        anchors.centerIn: parent
        height: mainGameManager.height
        width: mainGameManager.width
        MinosManager {
            id: solo_minosManager
            anchors.fill: parent
        }
    }

    Button {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20
        text: qsTr("Get next mino")
        onClicked: {
            solo_minosManager._getNextMino()
        }
    }

    Component.onCompleted: {
        mainGameManager.gameStart.connect(solo_fieldManager.onGameStart)
        mainGameManager.gameStart.connect(solo_minosManager.onGameStart)
    }
    Keys.onPressed: (event) => {
        console.log(event.key);
        switch(event.key){
                            case Qt.Key_W:
                                solo_minosManager._moveNowMino(0, 1);
                                break;
                            case Qt.Key_D:
                                solo_minosManager._moveNowMino(1, 1);
                                break;
                            case Qt.Key_S:
                                solo_minosManager._moveNowMino(2, 1);
                                break;
                            case Qt.Key_A:
                                solo_minosManager._moveNowMino(3, 1);
                                break;
                        }
    }
}
