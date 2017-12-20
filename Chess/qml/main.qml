import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.0

ApplicationWindow {

    title: qsTr("Chess")
    id: main_window
    visible: true
    width: 1000
    height: 600


    property int squareSize: 70
    Item {
        id: gameBoard
        width : logic.boardSize * squareSize
        height: logic.boardSize * squareSize
        //x: (parent.width - this.width) /2
        anchors.centerIn: parent
        rotation: 180
        Image {
            source: "/images/chess_board.jpg"
            height: gameBoard.height
            width: gameBoard.width
        }
    }

    Button {
        id: startButton
        style: ButtonStyle {
            background: Rectangle {
                implicitHeight: 100
                border.width: control.Focus ? 2 : 1
                border.color: "#888"
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                }
            }
        }

        anchors.left: gameBoard.right;
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: gameBoard.top
        Text {
            id: buttonText
            text: "Start new"
            anchors.centerIn: parent
            font.pixelSize: 45
            style: Text.Sunken
            color: "white"
            styleColor: "black"
        }
        onClicked: {
            main_window.close();
            logic.close();
            logic.createNew();
            screen2.signalStart();
            screen2.show();
            continueButton.visible = true;


        }
    }
    Button {
        id: loadButton
        style: ButtonStyle {
            background: Rectangle {
                implicitHeight: 100
                border.width: control.Focus ? 2 : 1
                border.color: "#888"
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                }
            }
        }

        anchors.left: gameBoard.right;
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: startButton.bottom
        anchors.topMargin: 5
        Text {
            text: "Load"
            anchors.centerIn: parent
            font.pixelSize: 50
            style: Text.Sunken
            color: "white"
            styleColor: "black"
        }
        onClicked: {            
            main_window.close();
            logic.close();
            screen3.show();
            logic.loadGame();
            screen3.close();
            screen3.show();
        }


    }
    Button {
        id: continueButton

        style: ButtonStyle {
            background: Rectangle {
                implicitHeight: 100
                border.width: control.Focus ? 2 : 1
                border.color: "#888"
                radius: 4
                gradient: Gradient {
                    GradientStop { position: 0 ; color: control.pressed ? "#ccc" : "#eee" }
                    GradientStop { position: 1 ; color: control.pressed ? "#aaa" : "#ccc" }
                }
            }
        }
        visible: false
        anchors.left: gameBoard.right;
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: loadButton.bottom
        anchors.topMargin: 5
        Text {
            text: "Continue"
            anchors.centerIn: parent
            font.pixelSize: 45
            style: Text.Sunken
            color: "white"
            styleColor: "black"
        }
        onClicked: {
            main_window.close();
            screen2.show();
        }


    }



    Screen_2{
        id: screen2;

        onSignalPause:{
            screen2.close();
            main_window.show();
        }
        onSignalSave:{
            logic.saveGame();
            screen2.close();
            screen2.show();
        }

    }

    Screen_3{

        id: screen3;
        onSignalStart:{
            screen3.close();
            logic.close();
            logic.createNew();
            screen2.signalStart();
            screen2.show();
            continueButton.visible = true;
        }
        onSignalLoad: {
            logic.loadGame();
            screen3.close();
            screen3.show();
        }

    }



}
