#include "fieldmanager.h"
#include "minosmanager.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
        qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
        qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));
    }

    QGuiApplication app(argc, argv);

    qmlRegisterType<GameManager>("ParticleG.QtMino.Core", 1, 0, "GameManager");
    qmlRegisterType<FieldManager>("ParticleG.QtMino.Display", 1, 0, "FieldManager");
    qmlRegisterType<MinosManager>("ParticleG.QtMino.Display", 1, 0, "MinosManager");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
