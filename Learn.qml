import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import QtMultimedia 5.5

Item {
    id: item1

    Connections
    {
        target: ya

        onStartQML:
        {

            imagePicrute.source = "";

            imagePicrute.source = file;


        }
    }


    Connections
    {
        target: learnWork

        onSignal_Next:
        {
            playMusicEnglish.source = "";
            playMusicEnglish.source =  fileSound;

            playMusicRussian.source = "";
            playMusicRussian.source = fileSoundTranslate;

            imagePicrute.source = "";
            imagePicrute.source = fileImage;


            playMusicEnglish.play();
        }
    }





    Audio {
        id: playMusicEnglish

        onStopped:
        {
            console.log("STOP PLAY English");
            playMusicRussian.play();
        }
    }

    Audio {
        id: playMusicRussian

        onStopped:
        {
            console.log("STOP PLAY Russian");


            if(learnWork.slot_countReplay() === 0)
            {
                learnWork.startNext();
            }
            else
            {
                playMusicEnglish.play();
            }
        }
    }

    Image {
        id: imagePicrute
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.bottomMargin: 50
        anchors.topMargin: 5
        anchors.fill: parent
        source: "image/carejpg.jpg"
    }

    Button{
        id: buttonStart
        height: 50
        text: qsTr("Начать")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: imagePicrute.bottom
        anchors.topMargin: 0

        onClicked:
        {
            learnWork.startWork();

            playMusicEnglish.play();
        }

    }

    Column {
        id: column
        width: 95
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: imagePicrute.bottom
        anchors.topMargin: 0
        spacing: 0

        Label {
            text: qsTr("Количество повторений:")
            visible: true
            anchors.bottom: control.top
            anchors.bottomMargin: 5
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.pointSize: 6
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
        }

        Tumbler {
            id: control
            width: 100
            height: 50
            visible: true
            clip: false
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            currentIndex: 3
            model: 15
            visibleItemCount: 1
            rotation: -90 // <---- Rotate there


            // @disable-check M16
            onCurrentIndexChanged:
            {

                learnWork.slot_setReplay(control.currentIndex + 1);
            }

//             background: Item {
//                 Rectangle {
//                     opacity: control.enabled ? 0.2 : 0.1
//                     border.color: "#FFFFFF"
//                     width: parent.width
//                     height: 1
//                     anchors.top: parent.top
//                 }

//                 Rectangle {
//                     opacity: control.enabled ? 0.2 : 0.1
//                     border.color: "#FFFFFF"
//                     width: parent.width
//                     height: 1
//                     anchors.bottom: parent.bottom
//                 }
//             }

             delegate: Text {

                 rotation: 90
                 text: qsTr("%1").arg(modelData + 1)
                 font: control.font
                 horizontalAlignment: Text.AlignHCenter
                 verticalAlignment: Text.AlignVCenter
                 opacity: 1.0 - Math.abs(Tumbler.displacement) / (visibleItemCount / 2)


             }

             Rectangle {
                 x: 22
                 anchors.horizontalCenter: control.horizontalCenter
                 y: control.height * 0.4
                 width: 30
                 height: 1
                 color: "#21be2b"
                 anchors.verticalCenterOffset: -15
                 anchors.verticalCenter: parent.verticalCenter
                 anchors.horizontalCenterOffset: 0
             }

             Rectangle {
                 anchors.horizontalCenter: control.horizontalCenter
                 y: control.height * 0.6
                 width: 30
                 height: 1
                 color: "#21be2b"
                 anchors.verticalCenterOffset: 15
                 anchors.verticalCenter: parent.verticalCenter
             }
        }
    }

    CheckBox {
        id: checkBoxAuto
        x: 527
        width: 105
        text: qsTr("Повтор")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 7
        anchors.top: imagePicrute.bottom
        anchors.topMargin: 7
        anchors.right: parent.right
        anchors.rightMargin: 5

        onCheckStateChanged:
        {
            learnWork.slot_setFlagReplay(checkBoxAuto.checked)
        }
    }

}
