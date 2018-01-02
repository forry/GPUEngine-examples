
 \example "geGL 2 Shaders"
 This example adds very simple shaders and shows couple of ways of loading them. It adds a little to the previos example
  "geGL 1 QtGui Context Init".
  
  First you need to get the shader source somehow. Nowadays most of the shaders are packed with other resources in some
  engine specific file. Or they could be generated or inserted in the source files. We cover this two methods since we
  have two shaders. A fragment shader and a vertex shader. Fragment shader is a simpler one so let's begin with it. We
  can find it's source in the static variable in our OpenGLWindow.
  \snippet OpenGLWindow.cpp fragment
  It is defined as a multi line string literal. The other shader is available as a text file triag_vs.glsl. Since it is
  somewhere on our disk we are unable to just open it from our program via the relative path. Remember that an out of 
  source build is a good practice and even if we could miraculously guarantee that our exe file and the shader are together
  the relative path actualy refers to a working directory from where we started the executable not to the executable intself.
  In production code we have the thin probably installed and there is an absolute path to it in e.g. window registry or
  we are just forcing user to run the application in our install directory. Here in this example we just use CMake to
  get the path for us since we are not installing anything. The only information we have is from our build configuration.
  And since the purpose of these examples are to be read and build from the source code this is ok.
  \code{.cmake}
  
  find_file(vertexShader triag_vs.glsl
          HINTS ${CMAKE_CURRENT_LIST_DIR}/..
          )

  ...

  target_compile_definitions(geGL_2_Shaders PUBLIC "VERTEX_SHADER=\"${vertexShader}\"")
  
  \endcode
  This sets us with the VERTEX_SHADER define with the absolute path to the shader file which we can use to load the shader.
  Loading a simple text file is a well known thing so we use the text file loader from geCore package. It all looks like 
  this:
  \snippet OpenGLWindow.cpp shader
  After these 3 lines the shaders should be created, compiled, attached and link together at the shaderProgram object.
  Now all we need to do is run it. We add 3 more lines to our render function. It all looks like this:
  \snippet OpenGLWindow.cpp render
  If you wonder where are the vertices come from since we haven't loaded anything into any buffers yet that's for your
  homework. Simple answer is nowhere and you might want to check the vertex shader:
  \code{.glsl}
  
  #version 330
  
  void main()
  {
     if(gl_VertexID == 0)
     {
        gl_Position = vec4(-0.5, 0.5, 0, 1);
     }
     else if(gl_VertexID == 1)
     {
        gl_Position = vec4(0.5, 0.5, 0, 1);
     }
     else
     {
        gl_Position = vec4(0.5, -0.5, 0, 1);
     }
  }
  
  \endcode

 [Qt OpenGL Window Example]:http://doc.qt.io/qt-5/qtgui-openglwindow-example.html "Qt OpenGL Window Example"