import QtQuick 2.0
import QtQuick.VirtualKeyboard 2.15
Item {
    anchors.fill: parent
    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: parent.height
        width: parent.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
