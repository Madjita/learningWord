import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import QtQuick.Controls.Material 2.1
import QtQuick.Controls.Universal 2.1

import Qt.labs.settings 1.0

ApplicationWindow {
    id:window
    visible: true
    width: 400
    height: 600
    title: qsTr("Hello World")

    Settings {
        id: settings
        property string style: "Material"
    }

    Drawer
    {
        id: drawerFolder
        width: Math.min(window.width, window.height) / 3 * 2
        height: window.height


        Folder
        {
            anchors.fill: parent
        }
    }



    header: ToolBar {
        Material.foreground: "white"

        RowLayout {
            spacing: 0
            anchors.fill: parent

            ToolButton {


                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "image/folder_icon.png" //"image/imagesSys/drawer.png"
                }
                onClicked: {
                        drawerFolder.open()
                }
            }

            Label {
                id: titleLabel
                text: listView.currentItem ? listView.currentItem.text : "Gallery"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }


            ToolButton {
                id:editWord
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "image/pen.png"
                }
               // onClicked: optionsMenu.open()
            }


            ToolButton {
                contentItem: Image {
                    id: seitingMenu
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "image/imagesSys/menu.png"
                }
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Настройки"
                        onTriggered: settingsDialog.open()
                    }
                    MenuItem {
                        text: "О программе"
                        onTriggered: aboutDialog.open()
                    }
                }
            }
        }
    }


    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        onCurrentIndexChanged:
        {

            switch(swipeView.currentIndex)
            {
                case 0: editWord.visible = true;break;
                case 1: editWord.visible = false;break;
            }
        }

        Word
        {

        }

        Learn {

        }


        Page1 {
        }
    }


    Dialog {
        id: settingsDialog
        x: Math.round((window.width - width) / 2)
        y: Math.round(window.height / 6)
        width: Math.round(Math.min(window.width, window.height) / 3 * 2)
        modal: true
        focus: true
        title: "Настройки"

        standardButtons: Dialog.Ok | Dialog.Cancel
        onAccepted: {
            settings.style = styleBox.displayText
            settingsDialog.close()
        }
        onRejected: {
            styleBox.currentIndex = styleBox.styleIndex
            settingsDialog.close()
        }

        contentItem: ColumnLayout {
            id: settingsColumn
            spacing: 20

            RowLayout {
                spacing: 10

                Label {
                    text: "Style:"
                }

                ComboBox {
                    id: styleBox
                    property int styleIndex: -1
                    model: ["Default", "Material", "Universal"]
                    Component.onCompleted: {
                        styleIndex = find(settings.style, Qt.MatchFixedString)
                        if (styleIndex !== -1)
                            currentIndex = styleIndex
                    }
                    Layout.fillWidth: true
                }
            }

            Label {
                text: "Restart required"
                color: "#e41e25"
                opacity: styleBox.currentIndex !== styleBox.styleIndex ? 1.0 : 0.0
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }

    Dialog {
        id: aboutDialog
        modal: true
        focus: true
        title: "О программе:\nLearningWord"

        x: (window.width - width) / 2
        y: window.height / 6
        width: Math.min(window.width, window.height) / 3 * 2
        contentHeight: aboutColumn.height




        Column {
            id: aboutColumn
            spacing: 20

            Label {
                width: aboutDialog.availableWidth
                text: "Приложение предназначенно для изучения иностранных языков."
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }

            Label {
                width: aboutDialog.availableWidth
                text: "Разработчик:  Смоглюк Сергей Юрьевичь"
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }
        }
    }


    footer:  TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("Слова")
        }
        TabButton {
            text: qsTr("Учить")
        }
        TabButton {
            text: qsTr("Добавить")
        }
    }

}
