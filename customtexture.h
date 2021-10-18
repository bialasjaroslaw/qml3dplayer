#pragma once

#include <Qt3DRender/QTexture>

#include "videoplayer.h"

class CustomTexture : public Qt3DRender::QSharedGLTexture
{
    Q_OBJECT
public:
    CustomTexture();

public slots:
    void setFrame(const VideoFrame& frame);

private:
    QVideoFrame _frame;
};
