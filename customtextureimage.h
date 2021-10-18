#pragma once

#include <QAbstractTextureImage>
#include <Qt3DRender/QTexture>
#include "videoplayer.h"

class CustomTextureImage : public Qt3DRender::QAbstractTextureImage
{
    Q_OBJECT
public:
    CustomTextureImage();

    Q_INVOKABLE void setFrame(VideoFrame frame);
    Q_INVOKABLE void setImage(const QImage& frame);

private:
    Qt3DRender::QTextureImageDataGeneratorPtr dataGenerator() const override;

    Qt3DRender::QTextureImageDataGeneratorPtr _gen;
    QImage _image;
    QVideoFrame _frame;
};
