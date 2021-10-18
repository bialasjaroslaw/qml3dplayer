#include "customtextureimage.h"

#include <QTimer>

#include "framedatagenerator.h"


CustomTextureImage::CustomTextureImage()
{
    _gen = QSharedPointer<TextureImageDataGenerator>::create(_image);
}

void CustomTextureImage::setFrame(VideoFrame frame)
{
    qDebug() << "setFrame start";
    _frame = frame;
    _image = frame.image();
    _gen = QSharedPointer<TextureImageDataGenerator>::create(_image);
    notifyDataGeneratorChanged();
    qDebug() << "setFrame end";
}

void CustomTextureImage::setImage(const QImage& image)
{
    _image = image;
    _gen = QSharedPointer<TextureImageDataGenerator>::create(_image);
    notifyDataGeneratorChanged();
}

Qt3DRender::QTextureImageDataGeneratorPtr CustomTextureImage::dataGenerator() const
{
    return _gen;
}
