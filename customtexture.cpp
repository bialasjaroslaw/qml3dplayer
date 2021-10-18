#include "customtexture.h"

#include <QTimer>

#include "framedatagenerator.h"

#include <QOpenGLTexture>
#include <QOpenGLContext>
#include <QOffscreenSurface>

QOpenGLContext* m_context = nullptr;
QOffscreenSurface* m_surface = nullptr;
QOpenGLTexture* m_texture = nullptr;

CustomTexture::CustomTexture()
{
}

void CustomTexture::setFrame(const VideoFrame& frame)
{
    int textureId = -1;
    qDebug() << "HandleType is" << frame.handleType();
    if(frame.handleType() == QAbstractVideoBuffer::HandleType::NoHandle)
    {
        QSurfaceFormat format;
        format.setMajorVersion(2);
        format.setMinorVersion(0);

        if(m_context == nullptr)
        {
            m_context = new QOpenGLContext(this);
            m_surface = new QOffscreenSurface;

            m_context->setFormat(format);
            m_surface->setFormat(format);

            if (!m_context->create())
                qDebug() << "Context is not created";
            if (!m_context->isValid())
                qDebug() << "Context is not valid";
            m_surface->create();
            if(!m_surface->isValid())
                qDebug() << "Surface is not valid";
            m_context->makeCurrent(m_surface);
            m_texture = new QOpenGLTexture(QOpenGLTexture::Target::Target2D);
            m_texture->setFormat(QOpenGLTexture::TextureFormat::RGBAFormat);
            m_texture->setSize(frame.width(), frame.height());
            m_texture->setData(frame.image());
            m_context->doneCurrent();
        }
        textureId = m_texture->textureId();
    }
    else
        textureId = frame.handle().toInt();

    _frame = frame;
    setTextureId(textureId);
}
