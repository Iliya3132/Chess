import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Window 2.1
import QtQuick.Controls.Styles 1.0

Window {
    id: screen_3
    signal signalStart;
    signal signalLoad;
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
      id: gameBoard_3
      width : logic.boardSize * squareSize
      height: logic.boardSize * squareSize
      anchors.centerIn: parent;
      rotation: 180
      Image {
        source: "/images/chess_board.jpg"
        height: gameBoard_3.height
        width: gameBoard_3.width
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
        }
      }
    }

    Button {

      id: startButton_3

      anchors.left: gameBoard_3.right
      anchors.right: parent.right
      anchors.leftMargin: 10
      anchors.rightMargin: 10
      anchors.top : gameBoard_3.top
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
             id: buttonText_3
             text: "Strat new"
             anchors.centerIn: parent
             font.pixelSize: 45
             style: Text.Sunken
             color: "white"
             styleColor: "black"
         }

      onClicked: {
        screen_3.signalStart();
      }
    }
    Button {
        id: loadButton_3
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

        anchors.left: gameBoard_3.right;
        anchors.right: parent.right
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        anchors.top: startButton_3.bottom
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

            screen_3.signalLoad();
        }
    }
    Button {

      id: nextButton_3

      anchors.left: parent.left
      anchors.right: gameBoard_3.left
      anchors.leftMargin: 10
      anchors.rightMargin: 10      
      anchors.bottom : prewButton_3.top
      anchors.bottomMargin: 5
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
             id: nextButtonText_3
             text: "Next"
             anchors.centerIn: parent
             font.pixelSize: 50
             style: Text.Sunken
             color: "white"
             styleColor: "black"
         }

      onClicked: {
        logic.stepNext();
      }
    }
    Button {

      id: prewButton_3

      anchors.left: parent.left
      anchors.right: gameBoard_3.left
      anchors.leftMargin: 10
      anchors.rightMargin: 10
      anchors.bottom : gameBoard_3.bottom
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
             id: prewButtonText_3
             text: "Prew"
             anchors.centerIn: parent
             font.pixelSize: 50
             style: Text.Sunken
             color: "white"
             styleColor: "black"
         }

      onClicked: {
        logic.stepPrew();
      }
    }


}
