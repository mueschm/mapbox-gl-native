#include "qmapboxgl_renderer_backend.hpp"

#include <QtGlobal>

#if QT_VERSION >= 0x050000
#include <QOpenGLContext>
#else
#include <QGLContext>
#endif

void QMapboxGLRendererBackend::updateAssumedState()
{
    assumeFramebufferBinding(ImplicitFramebufferBinding);
    assumeViewport(0, 0, { 800, 600 });
}

mbgl::Size QMapboxGLRendererBackend::getFramebufferSize() const
{
    return m_size;
}

void QMapboxGLRendererBackend::setFramebufferSize(const mbgl::Size &size)
{
    m_size = size;
}

/*!
    Initializes an OpenGL extension function such as Vertex Array Objects (VAOs),
    required by Mapbox GL Native engine.
*/
mbgl::gl::ProcAddress QMapboxGLRendererBackend::getExtensionFunctionPointer(const char* name)
{
#if QT_VERSION >= 0x050000
    QOpenGLContext* thisContext = QOpenGLContext::currentContext();
    return thisContext->getProcAddress(name);
#else
    const QGLContext* thisContext = QGLContext::currentContext();
    return reinterpret_cast<mbgl::gl::ProcAddress>(thisContext->getProcAddress(name));
#endif
}
