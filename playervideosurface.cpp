#include "playervideosurface.h"

#include <QDebug>

bool PlayerVideoSurface::present(const QVideoFrame& frame)
{
    if (!frame.isValid())
        return false;

    qDebug() << "Format" << frame.pixelFormat() << "useFrames" << _useFrames;

    if(_useFrames)
        emit nextFrame(frame);
    else
        emit nextImage(imageFromVideoFrame(frame));
    return true;
}

QList<QVideoFrame::PixelFormat> PlayerVideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
    Q_UNUSED(type);
    return QList<QVideoFrame::PixelFormat>()
           << QVideoFrame::Format_ARGB32 << QVideoFrame::Format_ARGB32_Premultiplied << QVideoFrame::Format_RGB32
           << QVideoFrame::Format_RGB24 << QVideoFrame::Format_RGB565 << QVideoFrame::Format_RGB555
           << QVideoFrame::Format_ARGB8565_Premultiplied << QVideoFrame::Format_BGRA32
           << QVideoFrame::Format_BGRA32_Premultiplied << QVideoFrame::Format_BGR32 << QVideoFrame::Format_BGR24
           << QVideoFrame::Format_BGR565 << QVideoFrame::Format_BGR555 << QVideoFrame::Format_BGRA5658_Premultiplied
           << QVideoFrame::Format_AYUV444 << QVideoFrame::Format_AYUV444_Premultiplied << QVideoFrame::Format_YUV444
           << QVideoFrame::Format_YUV420P << QVideoFrame::Format_YV12 << QVideoFrame::Format_UYVY
           << QVideoFrame::Format_YUYV << QVideoFrame::Format_NV12 << QVideoFrame::Format_NV21
           << QVideoFrame::Format_IMC1 << QVideoFrame::Format_IMC2 << QVideoFrame::Format_IMC3
           << QVideoFrame::Format_IMC4 << QVideoFrame::Format_Y8 << QVideoFrame::Format_Y16
           << QVideoFrame::Format_Jpeg << QVideoFrame::Format_CameraRaw << QVideoFrame::Format_AdobeDng;
}

QImage PlayerVideoSurface::imageFromVideoFrame(const QVideoFrame& buffer) const
{
    if (buffer.pixelFormat() != QVideoFrame::PixelFormat::Format_ABGR32)
        return buffer.image();

    auto castData = [](unsigned char* ptr){
        return static_cast<uint32_t*>(static_cast<void*>(ptr));
    };

    QVideoFrame frame = buffer;
    frame.map(QAbstractVideoBuffer::ReadOnly);
    const auto size = frame.mappedBytes();
    auto* streamStart = castData(frame.bits());
    auto* streamEnd = castData(frame.bits() + size);

    std::for_each(streamStart, streamEnd, [](uint32_t& elem){
        if constexpr (Q_BYTE_ORDER == Q_LITTLE_ENDIAN)
            elem = (elem & 0xFF00FF00) | ((elem & 0x00FF0000) >> 16) | ((elem & 0x000000FF) << 16);
        else
            elem = (elem & 0x00FF00FF) | ((elem & 0xFF000000) >> 16) | ((elem & 0x0000FF00) << 16);
    });
    return QImage(frame.bits(), frame.width(), frame.height(), frame.bytesPerLine(), QImage::Format_ARGB32).copy();
}

bool PlayerVideoSurface::useFrames() const
{
    return _useFrames;
}

void PlayerVideoSurface::setUseFrames(bool value)
{
    _useFrames = value;
}
