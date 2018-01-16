//
// Created by forry on 24.11.2017.
//

#pragma once

#include <QtGui/QWindow>
#include <memory>

class QOpenGLPaintDevice;
namespace ge
{
   namespace gl
   {
      class Context;
      class Program;
      class VertexArray;
   }
   namespace examples
   {

      /**
       * Basic QWindow subclass for simple OpenGL rendering.
       */
      class OpenGLWindow : public QWindow
      {
      Q_OBJECT
      public:
         explicit OpenGLWindow(QWindow *parent = 0);

         ~OpenGLWindow();

         virtual void render();
         virtual void initialize();

         static const std::string fragmentShaderSrc;

      public slots:

         void renderNow();

      protected:
         bool event(QEvent *event) override;
         void exposeEvent(QExposeEvent *event) override;

      private:
         bool initialized;

         static std::vector<float> trianglePos;
         static std::vector<float> triangleCol;
         static std::vector<int> indices;
         std::shared_ptr<ge::gl::Context> gl;
         std::shared_ptr<ge::gl::Program> shaderProgram;
         std::shared_ptr<ge::gl::VertexArray> dummyVAO;
         QOpenGLContext *context;
         QSurfaceFormat surfaceFormat;
      };
   }
}



