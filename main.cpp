#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "customtextureimage.h"
#include "customtexture.h"
#include "videoplayer.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QGuiApplication app(argc, argv);

    VideoPlayer player;
    player.open(QUrl("qrc:/sample_short.mp4"));

    qmlRegisterSingletonType<VideoPlayer>("Application.Video", 1, 0, "Player", [&](QQmlEngine*, QJSEngine*){
        return &player;
    });
    qmlRegisterType<CustomTextureImage>("CustomTextureImage", 1, 0, "CustomTextureImage");
    qmlRegisterType<CustomTexture>("CustomTexture", 1, 0, "CustomTexture");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &player, &VideoPlayer::play);
    QObject::connect(&engine, &QQmlApplicationEngine::quit, qApp, &QGuiApplication::quit);
    engine.load(url);

    return app.exec();
}
