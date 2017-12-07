#include <QtGui/QGuiApplication>
#include <OpenGLWindow.h>
#include <QtGui/QOpenGLContext>


int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);

    ge::examples::OpenGLWindow window;
    window.resize(640,480);
    window.show();

    return app.exec();
}