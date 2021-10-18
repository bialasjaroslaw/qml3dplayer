#include "framedatagenerator.h"

#include <QPainter> // remove before PR

TextureImageDataGenerator::TextureImageDataGenerator(const QImage& texturedImage)
    : image(texturedImage)
{}

Qt3DRender::QTextureImageDataPtr TextureImageDataGenerator::operator()()
{
    Qt3DRender::QTextureImageDataPtr textureData = Qt3DRender::QTextureImageDataPtr::create();
    textureData->setImage(image);
    return textureData;
}

bool TextureImageDataGenerator::operator==(const Qt3DRender::QTextureImageDataGenerator& other) const
{
    const auto* otherFunctor = functor_cast<TextureImageDataGenerator>(&other);
    return otherFunctor && otherFunctor->image == image;
}
