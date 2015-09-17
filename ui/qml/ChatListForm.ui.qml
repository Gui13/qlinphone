import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import QLChatRoom 1.0

ScrollView {
    verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn
    style: ScrollViewStyle {
        transientScrollBars: false
    }

    ListView {
        id: chatList
        width: 400
        height: 400

        delegate: Item {
            width: chatList.width; height: column.height
            Column {
                id: column
                width: chatList.width
                TextEdit {
                    selectByMouse: true
                    readOnly: true
                    width: parent.width
                    text:chatMessage
                    wrapMode: Text.WordWrap
                }
                Row {
                    height: 15
                    width: parent.width

                    Rectangle { width: parent.width - (date.width + 15 ); height: 1 }

                    Text {
                        id:date
                        text: formattedDate;
                        horizontalAlignment: Text.AlignRight
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.WordWrap
                    }
                    Rectangle {
                        width: 15; height: 15; radius: 5
                        color: statusColor
                    }
                }
                Rectangle {
                    width:parent.width
                    color: "black"
                    height: 1
                }
            }
        }
        model: myModel
        onModelChanged: newItem()
        focus: true
        function newItem() {
            chatList.positionViewAtEnd();
            console.log("New Item!!");
        }
    }
}
