import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import QtMultimedia 5.5

Item {
    id: item1
    property alias textField1: textField1
    property alias button1: button1
    property alias button2: button

    property alias playArea1: playArea
    property alias playMusic1: playMusic
    property alias textLol: textLol

    property alias textField2: textField2
    property alias button3: button2
    property alias button4: button3

    property alias playArea2: playArea2
    property alias playMusic2: playMusic2
    property alias textLol2: textLol2

    RowLayout {
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        anchors.top: parent.top

        TextField {
            id: textField1
            Layout.fillWidth: true
            placeholderText: qsTr("Text Field")
        }

        Button {
            id: button1
            text: qsTr("Press Me")
        }

        Button {
            id: button
            text: qsTr("Button")
        }
    }

    Text {
        text: "Click Me!"
        id: textLol
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 24
        width: 150
        height: 50

        Audio {
            id: playMusic

            source: "storage/emulated/0/Download/zap.wav"
        }
        MouseArea {
            id: playArea
            anchors.fill: parent
            //onPressed:  { playMusic.play() }
        }
    }

    RowLayout {
        x: -5
        y: 7
        anchors.horizontalCenterOffset: 0
        anchors.topMargin: 74
        anchors.horizontalCenter: parent.horizontalCenter
        TextField {
            id: textField2
            placeholderText: qsTr("Text Field")
            Layout.fillWidth: true
        }

        Button {
            id: button2
            text: qsTr("Press Me")
        }

        Button {
            id: button3
            text: qsTr("Button")
        }
        anchors.top: parent.top
        anchors.leftMargin: 0
        anchors.left: parent.left
    }

    Text {
        text: "Click Me!"
        anchors.verticalCenterOffset: 83
        anchors.horizontalCenterOffset: 0
        id: textLol2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pointSize: 24
        width: 150
        height: 50

        Audio {
            id: playMusic2

            source: "storage/emulated/0/Download/zap.wav"
        }
        MouseArea {
            id: playArea2
            anchors.fill: parent
            //onPressed:  { playMusic.play() }
        }
    }
}
