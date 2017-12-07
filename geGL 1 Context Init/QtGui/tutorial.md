
 \example "geGL 1 QtGui Context Init"
 This example shows how to initialize OpenGL context with Qt Gui and use this context
 for geGL initialization. Then we show simple usage of common gl functions. This example is build upon an original
 [Qt OpenGL Window Example]. The main is super simple and just instantiates
 our window subclass.
 \snippet ./main.cpp main
 Everything is done in the OpenGLWindow class. It is important to set the correct surface type before creating a context.
 We do this in constructor. We can also setup our custom surface format
 \snippet OpenGLWindow.cpp ctor
 We can initialize the context only after the window is shown or first exposed as the Qt doc said. The exposed event
 can be intercepted by overriding the exposeEvent() function of QWindow.
 \snippet OpenGLWindow.cpp expose
 The initialization is called from the renderNow method. But it can be called wherever. Just remember, the window needs
 to exist at that time.
 \snippet OpenGLWindow.cpp renderNow
 The first part of the initialization is context creation. Since GPUEngine doesn't provide us with the necessary tools
 because it is platform independent/unaware that's what we use Qt for.
 \snippet OpenGLWindow.cpp qt_context
 Next we need to say our OS that we want to use this context. Otherwise all context related calls will fail.
 \snippet OpenGLWindow.cpp makeCurrent
 Then we can proceed with the geGL initialization which is very simple.
 \snippet OpenGLWindow.cpp geGL_init
 After that we should have all available gl functions entry points saved in the gl object. Which we can simply use like this:
 \snippet OpenGLWindow.cpp render
 Of course we need to call swapBuffers somewhere. Just note that this is also a OS function not the OpenGL one, so we
 use Qt for that not the geGL. There are some instances where this is done for us by the library that provides us with
 context or the visualization loop. E.g. if we'd used the Qt Quick we would got the context created and the Qt would call
 the swap buffer for us at the end of its inner rendering loop. If you need to complete OpenGL operation for e.g. synchronization
 reasons use glFinish which is a gl call so it would be made available by the geGL.


 [Qt OpenGL Window Example]:http://doc.qt.io/qt-5/qtgui-openglwindow-example.html "Qt OpenGL Window Example"