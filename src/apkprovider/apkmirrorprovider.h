#ifndef APKMIRRORPROVIDER_H
#define APKMIRRORPROVIDER_H

#include "apkprovider/apkproviderabstract.h"

class ApkMirrorProvider : public ApkProviderAbstract
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("")
public:
    explicit ApkMirrorProvider(QObject *parent = nullptr);

    void listVersions(const QString &search) override;

private:
    void parseSearch(const QByteArray &data);
};

#endif // APKMIRRORPROVIDER_H
