
 \example "geGL 5 Uniforms"

This example will show you a couple ways of how to send uniforms into shaders. Attributes are bound as usual. We will draw a tetrahedron.
\snippet "geGL 5 Uniforms/QtGui/OpenGLWindow.cpp" attrib_buffer
Now we create one simple projection matrix. It is defined as uniform mat4 in the shader.
\snippet "geGL 5 Uniforms/QtGui/OpenGLWindow.cpp" projection
The model matrix is defined as a buffer. We make a vector on cpu side and use SSBO target for serving it to the GPU.
\snippet "geGL 5 Uniforms/QtGui/OpenGLWindow.cpp" SSBO
The setMatrix4fv calls glUniformMatrix4fv and the bindBuffer binds buffer to appropriate binding point and a shader storage target.
\snippet "geGL 5 Uniforms/QtGui/OpenGLWindow.cpp" uniforms
Not much has changed for VAO and the render method
\snippet "geGL 5 Uniforms/QtGui/OpenGLWindow.cpp" VAO
\snippet "geGL 5 Uniforms/QtGui/OpenGLWindow.cpp" render