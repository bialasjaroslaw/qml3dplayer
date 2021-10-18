#pragma once
#include <QMediaPlayer>
#include "playervideosurface.h"

#include <QObject>
#include <QVideoProbe>

class VideoFrame : public QVideoFrame
{
public:
    VideoFrame();
    VideoFrame(const VideoFrame&);
    VideoFrame(const QVideoFrame& f);
    virtual ~VideoFrame();
};

Q_DECLARE_METATYPE(VideoFrame)
namespace {
int typeId = qRegisterMetaType<VideoFrame>();
}

class VideoPlayer : public QObject
{
    Q_OBJECT
public:
    VideoPlayer(QObject* parent = nullptr);

    Q_PROPERTY(bool useFrames READ useFrames WRITE setUseFrames NOTIFY useFramesChanged)

    bool open(const QUrl &path);
    void pause();
    void play();
    void stop();
    bool isPlaying() const;

    bool useFrames() const;
    void setUseFrames(bool enable);

private slots:
    void onVideoAvailableChanged(bool available);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onError(QMediaPlayer::Error error);
    void onNextFrame(const VideoFrame& frame);
    void onNextImage(const QImage &image);

private:
    QMediaPlayer* _player = nullptr;
    QVideoProbe* _probe = nullptr;
    PlayerVideoSurface* _surface = nullptr;
    bool _useFrames = false;

signals:
    void nextFrame(const VideoFrame& nextFrame);
    void nextImage(const QImage& image);
    void isVideoPlayingChanged();
    void mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void useFramesChanged();
};
