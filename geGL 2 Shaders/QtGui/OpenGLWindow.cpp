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

   std::cout<< "vertex shader: " << VERTEX_SHADER << std::endl;

   //! [shader]

   std::shared_ptr<ge::gl::Shader> vertexShader = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::core::loadTextFile(VERTEX_SHADER));
   std::shared_ptr<ge::gl::Shader> fragmentShader = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, fragmentShaderSrc);

   shaderProgram = std::make_shared<ge::gl::Program>(vertexShader,fragmentShader);

   //! [shader]

   //![VAO]

   dummyVAO = std::make_shared<ge::gl::VertexArray>();

   //![VAO]

   initialized = true;
}

//! [render]
void ge::examples::OpenGLWindow::render()
{
   const qreal retinaScale = devicePixelRatio();
   gl->glViewport(0, 0, width() * retinaScale, height() * retinaScale);
   gl->glClearColor(0.5, 0.5, 0.2, 1.0);
   gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   shaderProgram->use(); //glUseProgram
   dummyVAO->bind(); //glBindVertexArray
   gl->glDrawArrays(GL_TRIANGLES,0,3);

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