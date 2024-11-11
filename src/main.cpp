/*
    SPDX-License-Identifier: GPL-3.0-only
    SPDX-FileCopyrightText: 2024 Trần Nam Tuấn <tuantran1632001@gmail.com>
*/

#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QUrl>

#include "app.h"
#include "version-qvanced.h"

#include <KAboutData>
#include <KIconTheme>
#include <KLocalizedContext>
#include <KLocalizedString>

#ifdef Q_OS_WINDOWS
#include <windows.h>
#endif

#include "qvancedconfig.h"

using namespace Qt::Literals::StringLiterals;

int main(int argc, char *argv[])
{
    KIconTheme::initTheme();

    QApplication app(argc, argv);

    QApplication::setStyle(QStringLiteral("breeze"));
    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(u"org.kde.desktop"_s);
    }

#ifdef Q_OS_WINDOWS
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }

    auto font = app.font();
    font.setPointSize(10);
    app.setFont(font);
#endif

    KLocalizedString::setApplicationDomain("qvanced");
    QCoreApplication::setOrganizationName(u"TheBill2001"_s);

    KAboutData aboutData(u"qvanced"_s,
                         i18nc("@title", "QVanced"),
                         QStringLiteral(QVANCED_VERSION_STRING),
                         i18n("Modifying Android APKs with Revanced patches."),
                         KAboutLicense::GPL_V3,
                         i18n("(c) 2024"),
                         {},
                         u"https://github.com/TheBill2001/QVanced"_s,
                         u"https://github.com/TheBill2001/QVanced/issues"_s);
    aboutData.addAuthor(i18nc("@info:credit", "Trần Nam Tuấn"),
                        i18nc("@info:credit", "Maintainer"),
                        u"tuantran1632001@gmail.com"_s,
                        u"https://github.com/TheBill2001"_s);
    KAboutData::setApplicationData(aboutData);
    QGuiApplication::setWindowIcon(QIcon::fromTheme(u"qvanced"_s));

    QQmlApplicationEngine engine;

    auto config = QVancedConfig::self();

    qmlRegisterSingletonInstance("io.github.thebill2001.qvanced.private", 1, 0, "Config", config);

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.loadFromModule("io.github.thebill2001.qvanced", u"Main");

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
