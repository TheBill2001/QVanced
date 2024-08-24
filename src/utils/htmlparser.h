#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <QString>
#include <libxml/HTMLparser.h>

class HtmlDocument;
class HtmlNode
{
protected:
    HtmlNode(HtmlDocument *parser);

public:
private:
    friend HtmlDocument;
    HtmlDocument *m_parser;
};

class HtmlDocument
{
public:
    explicit HtmlDocument(const QByteArray &data);
    ~HtmlDocument();

    QList<HtmlNode *> select();

private:
    static const char *const enconding;
    static const int options = HTML_PARSE_NOWARNING | HTML_PARSE_NOERROR | HTML_PARSE_RECOVER;

    htmlParserCtxtPtr m_context = nullptr;
    htmlDocPtr m_doc = nullptr;

    QString m_error;
};

#endif // HTMLPARSER_H
