#include "videowidgetsurface.h"

#include <QtWidgets>
#include <qabstractvideosurface.h>
#include <qvideosurfaceformat.h>

myQAbstractVideoSurface::myQAbstractVideoSurface(QObject *parent)
    : QAbstractVideoSurface(parent)
    , imageFormat(QImage::Format_Invalid)
{
}

QList<QVideoFrame::PixelFormat> myQAbstractVideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555;
    } else {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool myQAbstractVideoSurface::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid
            && !size.isEmpty()
            && format.handleType() == QAbstractVideoBuffer::NoHandle;
}

bool myQAbstractVideoSurface::start(const QVideoSurfaceFormat &format)
{
    const QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    const QSize size = format.frameSize();

    if (imageFormat != QImage::Format_Invalid && !size.isEmpty()) {
        this->imageFormat = imageFormat;
        QAbstractVideoSurface::start(format);
        return true;
    } else {
        return false;
    }
}

void myQAbstractVideoSurface::stop()
{
    QAbstractVideoSurface::stop();
}

void myQAbstractVideoSurface::fnClearPixmap()
{
    imageCaptured = QPixmap();
}

bool myQAbstractVideoSurface::present(const QVideoFrame &frame)
{
    if (surfaceFormat().pixelFormat() != frame.pixelFormat()
            || surfaceFormat().frameSize() != frame.size()) {
        setError(IncorrectFormatError);
        stop();

        return false;
    } else {
        if(!imageCaptured.isNull()){
            emit fnSurfaceStopped(imageCaptured);
        }

        currentFrame = frame;
        if (currentFrame.map(QAbstractVideoBuffer::ReadOnly)) {

            QImage image(
                    currentFrame.bits(),
                    currentFrame.width(),
                    currentFrame.height(),
                    currentFrame.bytesPerLine(),
                    imageFormat);
            if(imageCaptured.isNull()){
                imageCaptured = QPixmap::fromImage(image.copy(image.rect()));
            }
            currentFrame.unmap();
        }
        return true;
    }
}
