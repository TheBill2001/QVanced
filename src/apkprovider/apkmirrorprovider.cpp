#include "apkprovider/apkmirrorprovider.h"

#include <QNetworkReply>
#include <QUrlQuery>

#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

#include "utils/network.h"

using namespace Qt::Literals::StringLiterals;

ApkMirrorProvider::ApkMirrorProvider(QObject *parent)
    : ApkProviderAbstract{QUrl(u"https://www.apkmirror.com/"_s), parent}
{
}

void ApkMirrorProvider::listVersions(const QString &search)
{
    QUrlQuery query;
    query.addQueryItem(u"post_type"_s, u"app_release"_s);
    query.addQueryItem(u"searchtype"_s, u"apk"_s);
    query.addQueryItem(u"sortby"_s, u"date"_s);
    query.addQueryItem(u"sort"_s, u"desc"_s);
    query.addQueryItem(u"bundles[]"_s, u"apk_files"_s);
    query.addQueryItem(u"s"_s, search);

    auto url = baseUrl();
    url.setQuery(query);

    QNetworkRequest request(url);
    setNetworkReqestUserAgent(&request);

    QNetworkReply *reply = globalNetworkManager()->get(request);
    connect(reply, &QNetworkReply::errorOccurred, this, [=]() {
        setSearchError(reply->errorString());
    });
    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << reply->readAll();
        } else {
            parseSearch(reply->readAll());
        }
        reply->deleteLater();
    });
}

void ApkMirrorProvider::parseSearch(const QByteArray &data)
{
    htmlParserCtxtPtr context = htmlNewParserCtxt();
    if (!context) {
        setSearchError(u"Error parsing HTML document: %1."_s.arg(u"Cannot create parser context"_s));
    } else {
        const char *url = "";
        static const char *const enconding = "UTF-8";
        static const int options = HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR | HTML_PARSE_RECOVER;
        htmlDocPtr doc = htmlCtxtReadMemory(context, data.constData(), data.size(), url, enconding, options);

        if (!doc) {
            setSearchError(u"Error parsing HTML document: %1."_s.arg(QString::fromUtf8(url)));
        } else {
            xmlXPathContextPtr xpathContext = xmlXPathNewContext(doc);

            if (!xpathContext) {
                setSearchError(u"Error parsing HTML document: Cannot construct XPath context."_s);
            } else {
                static const xmlChar *const xpath = (xmlChar *)"//div[@id='content']//div[contains(@class, 'appRow')]//h5/a";
                xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, xpathContext);

                if (!result) {
                    setSearchError(u"Error parsing HTML document: Cannot find elements from XPath."_s);
                } else {
                    if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
                        setVersions({});
                    } else {
                        xmlNodeSetPtr nodeset = result->nodesetval;
                        QStringList versions;

                        for (auto i = 0; i < nodeset->nodeNr; ++i) {
                            auto name = QString::fromUtf8((char *)nodeset->nodeTab[i]->children[0].content);
                            versions.append(name);
                        }

                        setVersions(versions);
                    }

                    xmlXPathFreeObject(result);
                }

                xmlXPathFreeContext(xpathContext);
            }

            xmlFreeDoc(doc);
        }

        xmlFreeParserCtxt(context);
    }
}
