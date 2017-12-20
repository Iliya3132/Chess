import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.0

Window {
    id: screen_2
    signal signalPause;
    signal signalStart;
    signal signalSave;

    width: 1000
    height: 600
    color: "#eee"

    property int squareSize: 70
    property var images: [
      {'imgPath' : "/images/white_pawn.svg"},
      {'imgPath' : "/images/white_rook.svg"},
      {'imgPath' : "/images/white_knight.svg"},
      {'imgPath' : "/images/white_bishop.svg"},
      {'imgPath' : "/images/white_king.svg"},
      {'imgPath' : "/images/white_queen.svg"},
      {'imgPath' : "/images/black_pawn.svg"},
      {'imgPath' : "/images/black_rook.svg"},
      {'imgPath' : "/images/black_knight.svg"},
      {'imgPath' : "/images/black_bishop.svg"},
      {'imgPath' : "/images/black_queen.svg"},
      {'imgPath' : "/images/black_king.svg"},
    ]
    Item {
      id: gameBoard_2
      width : logic.boardSize * squareSize
      height: logic.boardSize * squareSize
      anchors.centerIn: parent;
      rotation: logic.rotat();
      Image {
        source: "/images/chess_board.jpg"
        height: gameBoard_2.height
        width: gameBoard_2.width
      }

      Repeater {
        model: logic

        Image{

          height: squareSize
          width : squareSize

          x: squareSize * positionX
          y: squareSize * positionY
          rotation: 180 + rotat
          source: images[type].imgPath

          MouseArea {
            anchors.fill: parent
            drag.target: parent

            property int startX: 0
            property int startY: 0
            property var board : gameBoard_2
            onPressed: {
              startX = parent.x;
              startY = parent.y;
            }

            onReleased: {
              var fromX = startX / squareSize;
              var fromY = startY / squareSize;
              var toX   = ((parent.x + mouseX) / squareSize);
              var toY   = (parent.y + mouseY) / squareSize;

              if (logic.move(fromX, fromY, toX, toY)) {
                gameBoard_2.rotation == 180 ?gameBoard_2.rotation = 0 : gameBoard_2.rotation == 0 ?gameBoard_2.rotation = 180 : 0
              }else{
                  parent.x = startX;
                  parent.y = startY;
              }


            }

          }


        }

      }

    }

    onSignalStart:{
    gameBoard_2.rotation = logic.rotat();
    }
    Button {

      id: pauseButton

      anchors.left: gameBoard_2.right
      anchors.right: parent.right
      anchors.leftMargin: 10
      anchors.rightMargin: 10
      anchors.top : gameBoard_2.top
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

      Text {
             id: buttonText2
             text: "Pause"
             anchors.centerIn: parent
             font.pixelSize: 50
             style: Text.Sunken
             color: "white"
             styleColor: "black"
         }

      onClicked: {
        screen_2.signalPause();

      }
    }

    Button {
        id: saveButton
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

        anchors.left: gameBoard_2.right;
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: pauseButton.bottom
        anchors.topMargin: 5
        Text {
            text: "Save"
            anchors.centerIn: parent
            font.pixelSize: 50
            style: Text.Sunken
            color: "white"
            styleColor: "black"
        }
        onClicked: {            
            screen_2.signalSave();
        }
    }




}
