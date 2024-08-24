#include <QtGlobal>

#include <QApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>

#include <KAboutData>
#include <KIconTheme>
#include <KLocalizedContext>
#include <KLocalizedString>

#include "apkprovider/apkmirrorprovider.h"
#include "qvancedglobal.h"
#include "version-qvanced.h"

void doTest(QCoreApplication *app)
{
    ApkMirrorProvider *provider = new ApkMirrorProvider(app);
    provider->listVersions(u"twitter"_s);
}

int main(int argc, char *argv[])
{
    KIconTheme::initTheme();

    QApplication app(argc, argv);

    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(u"org.kde.desktop"_s);
    }

#ifdef Q_OS_WINDOWS
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }

    QApplication::setStyle(QStringLiteral("breeze"));
    auto font = app.font();
    font.setPointSize(10);
    app.setFont(font);
#endif

    KLocalizedString::setApplicationDomain("qvanced");
    // QCoreApplication::setOrganizationName(u"KDE"_s);

    KAboutData aboutData(u"qvanced"_s,
                         i18nc("@title", QVANCED_APP_TITLE),
                         QStringLiteral(QVANCED_VERSION_STRING),
                         i18n("Patching Android applications using Revanced"),
                         KAboutLicense::GPL_V3,
                         i18n("(c) 2024"));
    aboutData.addAuthor(i18nc("@info:credit", "Trần Nam Tuấn"),
                        i18nc("@info:credit", "Maintainer"),
                        u"tuantran1632001@gmail.com"_s,
                        u"https://github.com/TheBill2001/QVanced"_s);
    // aboutData.setTranslator(i18nc("NAME OF TRANSLATORS", "Your names"), i18nc("EMAIL OF TRANSLATORS", "Your emails"));
    KAboutData::setApplicationData(aboutData);
    QGuiApplication::setWindowIcon(QIcon::fromTheme(u"io.github.thebill2001.qvanced"_s));

    QQmlApplicationEngine engine;

    // qmlRegisterSingletonInstance("io.github.thebill2001.qvanced.private", 1, 0, "Config", QVancedConfig::self());

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));

    engine.loadFromModule("io.github.thebill2001.qvanced", "Main");

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    // doTest(&app);

    return app.exec();
}
