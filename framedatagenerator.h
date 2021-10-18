#pragma once

#include <Qt3DRender/QTexture>

class TextureImageDataGenerator : public Qt3DRender::QTextureImageDataGenerator
{
public:
    TextureImageDataGenerator(const QImage& texturedImage);

    Qt3DRender::QTextureImageDataPtr operator()() override;
    bool operator==(const Qt3DRender::QTextureImageDataGenerator& other) const override;

    QT3D_FUNCTOR(TextureImageDataGenerator)

private:
    QImage image;
};
