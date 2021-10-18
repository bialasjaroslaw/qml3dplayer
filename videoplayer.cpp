#include "videoplayer.h"

#include <QIODevice>
#include <QDebug>
#include <QMediaPlaylist>

VideoPlayer::VideoPlayer(QObject* parent)
    : _player(new QMediaPlayer(this))
    , _probe(new QVideoProbe(this))
    , _surface(new PlayerVideoSurface(parent))
{
    connect(_player, &QMediaPlayer::stateChanged, this, &VideoPlayer::isVideoPlayingChanged);
    connect(_surface, &PlayerVideoSurface::nextFrame, this, &VideoPlayer::onNextFrame);
    connect(_surface, &PlayerVideoSurface::nextImage, this, &VideoPlayer::onNextImage);
    connect(_player, &QMediaPlayer::videoAvailableChanged, this, &VideoPlayer::onVideoAvailableChanged);
    connect(_player, &QMediaPlayer::mediaStatusChanged, this, &VideoPlayer::onMediaStatusChanged);
    connect(_player, qOverload<QMediaPlayer::Error>(&QMediaPlayer::error), this, &VideoPlayer::onError);
    _player->setVideoOutput(_surface);
}

void VideoPlayer::onVideoAvailableChanged(bool available)
{
    qDebug() << "Video available changed " << available;
}

void VideoPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() << "Video media status changed " << status;
    emit mediaStatusChanged(status);
}

void VideoPlayer::onError(QMediaPlayer::Error error)
{
    qDebug() << "Video error (" << error << "): " + _player->errorString();
}

void VideoPlayer::onNextFrame(const VideoFrame& frame)
{
    qDebug() << "Next frame ready";
    emit nextFrame(frame);
}

void VideoPlayer::onNextImage(const QImage& image)
{
    emit nextImage(image);
}

bool VideoPlayer::open(const QUrl& path)
{
    auto pls = new QMediaPlaylist;
    pls->addMedia(QMediaContent(path));
    pls->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    _player->setPlaylist(pls);
    return true;
}

void VideoPlayer::stop()
{
    _player->stop();
}

void VideoPlayer::pause()
{
    _player->pause();
}

void VideoPlayer::play()
{
    _player->play();
}

bool VideoPlayer::isPlaying() const
{
    return _player->state() == QMediaPlayer::PlayingState;
}

bool VideoPlayer::useFrames() const
{
    return _useFrames;
}

void VideoPlayer::setUseFrames(bool enable)
{
    _useFrames = enable;
    _surface->setUseFrames(_useFrames);
    emit useFramesChanged();
}

VideoFrame::VideoFrame(const QVideoFrame &f) : QVideoFrame(f)
{
    qDebug() << "VideoFrame(const QVideoFrame&)";
}

VideoFrame::VideoFrame()
{
    qDebug() << "VideoFrame()";
}

VideoFrame::VideoFrame(const VideoFrame& other) : QVideoFrame(other)
{
    qDebug() << "VideoFrame(const VideoFrame &)";
}

VideoFrame::~VideoFrame()
{
    qDebug() << "~VideoFrame()";
}
