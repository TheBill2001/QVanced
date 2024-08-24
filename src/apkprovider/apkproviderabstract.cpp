#include "apkprovider/apkproviderabstract.h"

ApkProviderAbstract::ApkProviderAbstract(const QUrl &baseUrl, QObject *parent)
    : QObject{parent}
    , m_baseUrl{baseUrl}
{
}

void ApkProviderAbstract::setSearchError(const QString &error)
{
    if (error == m_searchError)
        return;

    m_searchError = error;
    Q_EMIT searchErrorOccurred(error);
}

void ApkProviderAbstract::setVersions(const QStringList &versions)
{
    if (versions == m_versions) {
        return;
    }

    m_versions = versions;
    Q_EMIT versionsChanged(versions);
}

QUrl ApkProviderAbstract::baseUrl() const
{
    return m_baseUrl;
}

QString ApkProviderAbstract::searchError() const
{
    return m_searchError;
}

QStringList ApkProviderAbstract::versions() const
{
    return m_versions;
}
