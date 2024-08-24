#include "htmlparser.h"

using namespace Qt::Literals::StringLiterals;

const char *const HtmlDocument::enconding = "UTF-8";

HtmlDocument::HtmlDocument(const QByteArray &data)
{
    m_context = htmlNewParserCtxt();
    if (!m_context) {
        m_error = u"Error parsing HTML document: %1"_s.arg(u"Cannot create parser context."_s);
        return;
    }

    const char *url = "";
    m_doc = htmlCtxtReadMemory(m_context, data.constData(), data.size(), url, enconding, options);

    if (!m_doc) {
        m_error = u"Error parsing HTML document: %1"_s.arg(QString::fromUtf8(url));
        return;
    }
}

HtmlDocument::~HtmlDocument()
{
    if (m_doc) {
        xmlFreeDoc(m_doc);
    }

    if (m_context) {
        xmlFreeParserCtxt(m_context);
    }
}
