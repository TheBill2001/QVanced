#ifndef QVANCEDAPP_H
#define QVANCEDAPP_H

#include <QQmlEngine>
#include <QQuickWindow>

class QVancedApp : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
public:
    explicit QVancedApp(QObject *parent = nullptr);
    ~QVancedApp();

    Q_INVOKABLE void restoreWindowGeometry(QQuickWindow *window, const QString &group = QStringLiteral("main")) const;
    Q_INVOKABLE void saveWindowGeometry(QQuickWindow *window, const QString &group = QStringLiteral("main")) const;
};

#endif // QVANCEDAPP_H
