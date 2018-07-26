import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1


Item
{
    id:foldeId


    ListView {
        id: list
        width: 300
        height: 500

        anchors.fill: parent

        model: learnWork.listFolder

        delegate: Item {
            width: 300

            anchors.left: parent.left
            anchors.right: parent.right
            height: 50

            Rectangle
            {
                id: modelAddWord
                height: 50

                anchors.margins: 5
                radius: height / 2
                anchors.fill: parent
                color: "#00aacc"


                Text
                {
                    id: nameFolder
                    y: 9
                    color: "#000000"
                    text: model.modelData.NameQML
                    anchors.right: siparater.left
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    Layout.fillHeight: false
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    font.bold: true
                    font.pointSize: 15
                    fontSizeMode: Text.VerticalFit
                    font.family: "Courier"

                }

                Rectangle {
                    id: siparater
                    x: 151
                    y: 20
                    color:  "#00ccff"
                    anchors.verticalCenter: parent.verticalCenter//"#21be2b"
                    Layout.fillHeight: false
                    Layout.fillWidth: false
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 35
                    rotation: 90
                }

                ColumnLayout
                {
                    y: 2
                    spacing: 5
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: siparater.right
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 17
                    Text {
                        id: countFolder
                        color: "#fbfbfb"
                        text: {
                            switch(model.modelData.countFolder())
                            {
                            case "1": model.modelData.countFolder() +" папка";break;
                            case "2": model.modelData.countFolder() +" папки";break;
                            case "3": model.modelData.countFolder() +" папки";break;
                            case "4": model.modelData.countFolder() +" папки";break;
                            default: model.modelData.countFolder() +" папок";break;
                            }
                        }
                        Layout.fillWidth: true
                        font.bold: false
                        font.pointSize: 10
                        fontSizeMode: Text.VerticalFit

                    }

                    Text {
                        id: countTerm
                        color: "#ffffff"
                        text:  {
                            switch(model.modelData.countWordTerm())
                            {
                            case "1": model.modelData.countWordTerm() +" термин";break;
                            case "2": model.modelData.countWordTerm() +" термина";break;
                            case "3": model.modelData.countWordTerm() +" термина";break;
                            case "4": model.modelData.countWordTerm() +" термина";break;
                            default: model.modelData.countWordTerm() +" терминов";break;
                            }
                        }
                        Layout.fillWidth: true
                        font.bold: false
                        font.pointSize: 10
                        fontSizeMode: Text.VerticalFit

                    }
                }
            }
        }



        ScrollBar.vertical: ScrollBar {  }

    }
}

