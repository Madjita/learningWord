import QtQuick 2.5
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

import QtQml.Models 2.2

import QtMultimedia 5.5

Item
{
    id:item2



    RoundButton {
        z: 1
        text: qsTr("+")
        highlighted: true
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom

    }
    //    ListView
    //    {
    //        id: listViewFolder
    //        height: 150
    //        anchors.right: parent.right
    //        anchors.rightMargin: 0
    //        anchors.left: parent.left
    //        anchors.leftMargin: 0
    //        anchors.top: parent.top
    //        anchors.topMargin: 0

    //        model: learnWork.listProverka

    //        delegate:  Item {
    //            anchors.left: parent.left
    //            anchors.right: parent.right
    //            height: 50

    //            Rectangle
    //            {

    //                color: "#00aaff"

    //                height: 50
    //                anchors.margins: 5
    //                radius: height / 2
    //                anchors.fill: parent
    //            }

    //        }

    //    }


    ListView
    {
        id: listViewWord
        anchors.fill: parent
        //listViewFolder.bottom
        // anchors.topMargin: 30




        model: learnWork.listProverka


        delegate:  Item {

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
                //                anchors.top: parent.top
                //                anchors.topMargin: 10
                //                anchors.left: parent.left
                //                anchors.leftMargin: 5
                //                anchors.right: parent.right
                //                anchors.rightMargin: 5


                RowLayout {
                    anchors.left: siparater.right
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    anchors.bottomMargin: 5
                    anchors.rightMargin: 5
                    anchors.leftMargin: 0
                    spacing: 5

                    Text {
                        id: translate
                        text: model.modelData.TranslationQML;
                        Layout.fillWidth: true
                        font.family: "Arial"
                        font.pixelSize: 15
                    }

                    Audio {
                        id: playMusicEnglish

                        onPlaying:
                        {
                            english.color = "#00ccff"; //"#fafa3c";
                        }
                        onStopped:
                        {
                            english.color = "#000000";

                            console.log("STOP PLAY English");

                            text1.cl();

                            playMusicRussian.play();

                        }
                    }

                    Audio {
                        id: playMusicRussian


                        onPlaying:
                        {
                            translate.color = "#00ccff"; //"#fafa3c";

                            text1.cl();
                        }

                        onStopped:
                        {
                            translate.color = "#000000";

                            console.log("STOP PLAY Russian");


                            text1.source = "image/audios.jpg"
                        }
                    }

                    Image {
                        id: text1
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.fillWidth: false
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 24
                        fillMode: Image.PreserveAspectCrop
                        source:  "image/audios.jpg"

                        function cl()
                        {
                            if(text1.source == "qrc:/image/audios.jpg")
                            {
                                text1.source = "image/audios_true.jpg"

                            }
                            else
                            {
                                text1.source = "image/audios.jpg"
                            }
                        }


                        MouseArea
                        {
                            id:text1Mouse
                            anchors.fill: parent

                            onClicked:
                            {
                                //убрать статические пути сделать относительно папки
                                playMusicEnglish.source = "file:///storage/emulated/0/LearningWord/Default/"+english.text+".wav"
                                playMusicRussian.source = "file:///storage/emulated/0/LearningWord/Default/"+english.text+"Translate.wav"

                                playMusicEnglish.play();
                                text1.cl();

                            }
                        }

                    }

                    Image {
                        id: dawText
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

                        enabled: true
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: 24
                        opacity: 0.1
                        fillMode: Image.PreserveAspectCrop
                        source:  "image/daw.jpeg"


                        MouseArea
                        {
                            anchors.fill: parent

                            onClicked:
                            {
                                if(dawText.opacity < 0.4)
                                {
                                    dawText.opacity = 1.0;
                                }
                                else
                                {
                                    dawText.opacity = 0.1;
                                }
                            }
                        }
                    }
                }

                Rectangle {
                    id: siparater
                    x: 110
                    y: 20
                    width: 35
                    height: 1
                    color:  "#00ccff"//"#21be2b"
                    Layout.fillHeight: false
                    Layout.fillWidth: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.preferredHeight: 1
                    Layout.preferredWidth: 39
                    rotation: 90
                }

                Text
                {
                    id: english
                    y: 9
                    text: model.modelData.WordQML;
                    anchors.right: siparater.left
                    anchors.rightMargin: 5
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    Layout.fillWidth: true
                    fontSizeMode: Text.VerticalFit
                    Layout.preferredHeight: 22
                    Layout.preferredWidth: 86
                    font.pointSize: 15
                    font.bold: false
                    font.family: "Courier"
                }



            }
        }


        ScrollBar.vertical: ScrollBar { size: 0.5 }
    }


}

