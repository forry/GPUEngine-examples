//
// Created by forry on 24.11.2017.
//

#include <OpenGLWindow.h>

#include <QtGui/QOpenGLContext>
#include <geGL/geGL.h>
#include <geCore/Text.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QDebug>

#include <iostream>

//![fragment]

std::vector<float> ge::examples::OpenGLWindow::trianglePos = {0.0f,0.0f,0.0f,
                                                              1.0f, 0.0f, 0.0f,
                                                              0.5f, 0.0f, -1.0f,
                                                              0.5f, 1.0f, -0.5f
                                                             };

std::vector<float> ge::examples::OpenGLWindow::triangleCol = {1.0f, 0.0f, 0.0f,
                                                              0.0f, 1.0f, 0.0f,
                                                              0.0f, 0.0f, 1.0f,};

std::vector<unsigned> ge::examples::OpenGLWindow::indices = {0,1,2,
                                                        0,1,3,
                                                        0,3,2,
                                                         1,2,3
};

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
   ge::gl::init();
   gl = std::make_shared<ge::gl::Context>();
   //! [geGL_init]

   //! [shaders]

   std::shared_ptr<ge::gl::Shader> vertexShader = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, ge::core::loadTextFile(VERTEX_SHADER));
   std::shared_ptr<ge::gl::Shader> fragmentShader = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, ge::core::loadTextFile(FRAGMENT_SHADER));
   shaderProgram = std::make_shared<ge::gl::Program>(vertexShader, fragmentShader);

   //! [shaders]

   std::shared_ptr<ge::gl::Buffer> positions = std::make_shared<ge::gl::Buffer>(trianglePos.size() * sizeof(float), trianglePos.data());
   std::shared_ptr<ge::gl::Buffer> element = std::make_shared<ge::gl::Buffer>(indices.size() * sizeof(unsigned), indices.data());

   std::vector<glm::mat4> modelMatrices;
   glm::mat4 mat = glm::translate(glm::mat4(1.0f), glm::vec3{0,0,-5});
   modelMatrices.push_back(mat);
   qDebug() << "matrix sizeof " << sizeof(glm::mat4) << " " << modelMatrices.size() << "\n";
   SSBO = std::make_shared<ge::gl::Buffer>(modelMatrices.size() * sizeof(glm::mat4), modelMatrices.data());

   //! [projection]

   glm::mat4 perpective = glm::perspective(glm::radians(45.f), (float)width() / height(), 0.1f, 1000.f); // no resizing yet

   shaderProgram->setMatrix4fv("projection", glm::value_ptr(perpective))
                ->bindBuffer("model",SSBO);

   //! [projection]

   printError();

   //! [VAO]

   VAO = std::make_shared<ge::gl::VertexArray>();

   VAO->bind();
   VAO->addElementBuffer(element);
   VAO->addAttrib(positions, 0, 3, GL_FLOAT);
   VAO->unbind();

   //! [VAO]


   initialized = true;
}

//! [render]
void ge::examples::OpenGLWindow::render()
{
   const qreal retinaScale = devicePixelRatio();
   gl->glViewport(0, 0, width() * retinaScale, height() * retinaScale);
   gl->glClearColor(.392, .584, 0.929, 1.0);
   gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

   shaderProgram->use();
   VAO->bind();
   gl->glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT, nullptr);

   printError();

   context->swapBuffers(this);
}
//! [render]

void ge::examples::OpenGLWindow::printError() const
{
   auto err = this->gl->glGetError();
   if(err != GL_NO_ERROR)
   {

      std::cout << err << std::endl;
   }
}

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