#ifndef NETWORK_H
#define NETWORK_H

#include <QNetworkAccessManager>

#include "qvancedglobal.h"
#include "version-qvanced.h"

#define QVANCED_USERAGENT_STR u"%1/%2 Qt/%3"_s.arg(QVANCED_APP_TITLE_STR, QStringLiteral(QVANCED_VERSION_STRING), QString::fromUtf8(qVersion()))

QNetworkAccessManager *globalNetworkManager();

inline void setNetworkReqestUserAgent(QNetworkRequest *request)
{
    request->setRawHeader("User-Agent", QVANCED_USERAGENT_STR.toUtf8());
}

#endif // NETWORK_H
