#ifndef PLAYERVIDEOSURFACE_H
#define PLAYERVIDEOSURFACE_H

#include <QAbstractVideoSurface>
#include <QObject>

class PlayerVideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT

public:
    PlayerVideoSurface(QObject* parent = nullptr)
        : QAbstractVideoSurface(parent)
    {}

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const override;
    bool present(const QVideoFrame& frame) override;

    bool useFrames() const;
    void setUseFrames(bool value);

signals:
    void nextFrame(const QVideoFrame& nextFrame);
    void nextImage(const QImage& nextImage);
private:
    QImage imageFromVideoFrame(const QVideoFrame &buffer) const;
    bool _useFrames = false;
};

#endif // PLAYERVIDEOSURFACE_H
