import QtQuick
import QtQuick.Controls as QQC2
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

import io.github.thebill2001.qvanced

Kirigami.ApplicationWindow {
    id: root

    title: i18n("QVanced")

    minimumWidth: Kirigami.Units.gridUnit * 20
    minimumHeight: Kirigami.Units.gridUnit * 20

    onClosing: QVancedApp.saveWindowGeometry(root)

    onWidthChanged: saveWindowGeometryTimer.restart()
    onHeightChanged: saveWindowGeometryTimer.restart()
    onXChanged: saveWindowGeometryTimer.restart()
    onYChanged: saveWindowGeometryTimer.restart()

    Component.onCompleted: QVancedApp.restoreWindowGeometry(root)

    Timer {
        id: saveWindowGeometryTimer
        interval: 1000
        onTriggered: QVancedApp.saveWindowGeometry(root)
    }

    globalDrawer: Kirigami.GlobalDrawer {
        isMenu: !Kirigami.Settings.isMobile
        actions: [
            Kirigami.Action {
                text: i18n("About QVanced")
                icon.name: "help-about"
                onTriggered: root.pageStack.pushDialogLayer(aboutPageComponent)
            },
            Kirigami.Action {
                text: i18n("Quit")
                icon.name: "application-exit"
                onTriggered: Qt.quit()
            }
        ]
    }

    Component {
        id: aboutPageComponent
        About {}
    }
}
