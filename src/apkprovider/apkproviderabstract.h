#ifndef APKPROVIDERABSTRACT_H
#define APKPROVIDERABSTRACT_H

#include <QQmlEngine>
#include <QUrl>

// class ApkInfo
// {
//     Q_GADGET
//     QML_VALUE_TYPE(apkInfo)
// public:

// };

class ApkProviderAbstract : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(ApkProvider)
    QML_UNCREATABLE("ApkProvider is an abstract class.")

    Q_PROPERTY(QUrl baseUrl READ baseUrl CONSTANT FINAL)
    Q_PROPERTY(QString searchError READ searchError NOTIFY searchErrorOccurred FINAL)
    Q_PROPERTY(QStringList versions READ versions NOTIFY versionsChanged FINAL)
protected:
    explicit ApkProviderAbstract(const QUrl &baseUrl, QObject *parent = nullptr);

    void setSearchError(const QString &error);
    void setVersions(const QStringList &versions);

public:
    QUrl baseUrl() const;
    QString searchError() const;

    Q_INVOKABLE virtual void listVersions(const QString &search) = 0;

    QStringList versions() const;

Q_SIGNALS:
    void searchErrorOccurred(const QString &error);
    void versionsChanged(const QStringList &versions);

private:
    QUrl m_baseUrl;
    QString m_searchError;

    QStringList m_versions;
};

#endif // APKPROVIDERABSTRACT_H
