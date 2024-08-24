#include "qvancedapp.h"

#include <KSharedConfig>
#include <KWindowConfig>

#include "utils/network.h"

static QNetworkAccessManager *globalnetworkManager = nullptr;

QNetworkAccessManager *globalNetworkManager()
{
    Q_ASSERT_X(globalnetworkManager != nullptr, Q_FUNC_INFO, "Global network manager pointer is null.");
    return globalnetworkManager;
}

QVancedApp::QVancedApp(QObject *parent)
    : QObject{parent}
{
    globalnetworkManager = new QNetworkAccessManager(this);
}

QVancedApp::~QVancedApp()
{
}

void QVancedApp::restoreWindowGeometry(QQuickWindow *window, const QString &group) const
{
    KConfig dataResource(QStringLiteral("data"), KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    KConfigGroup windowGroup(&dataResource, QStringLiteral("Window-") + group);
    KWindowConfig::restoreWindowSize(window, windowGroup);
    KWindowConfig::restoreWindowPosition(window, windowGroup);
}

void QVancedApp::saveWindowGeometry(QQuickWindow *window, const QString &group) const
{
    KConfig dataResource(QStringLiteral("data"), KConfig::SimpleConfig, QStandardPaths::AppDataLocation);
    KConfigGroup windowGroup(&dataResource, QStringLiteral("Window-") + group);
    KWindowConfig::saveWindowPosition(window, windowGroup);
    KWindowConfig::saveWindowSize(window, windowGroup);
    dataResource.sync();
}
