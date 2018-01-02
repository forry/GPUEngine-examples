//
// Created by forry on 24.11.2017.
//

#include <OpenGLWindow.h>

#include <QtGui/QOpenGLContext>
#include <geGL/geGL.h>
#include <geCore/Text.h>

#include <iostream>

//![fragment]

const std::string ge::examples::OpenGLWindow::fragmentShaderSrc =
      "#version 430\n"
            "\n"
            "out vec4 fragColor;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   fragColor = vec4(0.8, 0, 0, 1);\n"
            "}";

std::vector<float> ge::examples::OpenGLWindow::trianglePos = {-1.0f, -1.0f, 0.0f,
                                                   1.0f, -1.0f, 0.0f,
                                                   0.0f, 1.0f, 0.0f,};

//![fragment]

//! [ctor]
ge::examples::OpenGLWindow::OpenGLWindow(QWindow *parent)
      : QWindow(parent)
      , initialized(false)
      , context(nullptr)
{
   setSurfaceType(QWindow::OpenGLSurface); //this needs to be set otherwise makeCurrent and other gl context related functions will fail
   surfaceFormat.setVersion(4, 5);
   surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
}
//! [ctor]

ge::examples::OpenGLWindow::~OpenGLWindow()
{
}

/**
 * Create OpenGL context with Qt with appropriate surface format.
 * Then initialize geGL and creating geGL context wrapper with OpenGL
 * functions entry points. Also prints out the GL_VERSION string.
 */
void ge::examples::OpenGLWindow::initialize()
{
   if (initialized) return;
   //! [qt_context]
   if (!context)
   {
      context = new QOpenGLContext(this);
      context->setFormat(surfaceFormat);
      bool success = context->create();
      if (!success)
      {
         //fail gracefully
      }
   }
   //! [qt_context]

   //! [makeCurrent]
   //let's say to the OS that we want to work with this context
   context->makeCurrent(this);
   //! [makeCurrent]

   //! [geGL_init]
   /*GPUEngine Init*/
   ge::gl::init();
   gl = std::make_shared<ge::gl::Context>();
   //! [geGL_init]
   std::for_each(trianglePos.begin(), trianglePos.end(),[](auto & val){std::cout<< val <<" ";});
   std::cout << std::endl;

   ge::gl::Buffer buffer1(trianglePos.size() * sizeof(float), trianglePos.data()/*, GL_STATIC_DRAW */);
   ge::gl::Buffer buffer2(trianglePos.size() * sizeof(float));

   buffer2.copy(buffer1);
   std::vector<float> readBuffer(9);

   buffer2.getData(readBuffer.data());

   std::for_each(readBuffer.begin(), readBuffer.end(),[](auto & val){std::cout<< val <<" ";});
   std::cout << std::endl;

   initialized = true;
}

//! [render]
void ge::examples::OpenGLWindow::render()
{
   const qreal retinaScale = devicePixelRatio();
   gl->glViewport(0, 0, width() * retinaScale, height() * retinaScale);
   gl->glClearColor(.392, .584, 0.929, 1.0);
   gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


   context->swapBuffers(this);
}
//! [render]

//! [renderNow]
void ge::examples::OpenGLWindow::renderNow()
{
   if (!isExposed()) return;
   if (!initialized) initialize();

   //context->makeCurrent(this);
   //context never got released so no need to make it current again

   render(); //do the simple rendering

   //release context only if necessary
}
//! [renderNow]

//! [eventFilter]
bool ge::examples::OpenGLWindow::event(QEvent *event)
{
   switch (event->type())
   {
      case QEvent::UpdateRequest:
         renderNow();
         return true;
      default:
         return QWindow::event(event);
   }
}
//! [eventFilter]

//! [expose]
void ge::examples::OpenGLWindow::exposeEvent(QExposeEvent *event)
{
   if (isExposed())
   {
      renderNow();
   }
}
//! [expose]