
 \example "geGL 4 VAO"

Vertex Arrays are structures/objects that are associated with the part of OpenGL state that links buffers with attributes bindings and then these to shader program attributes. More on this topic is in OpenGL documentation. As we've seen in previous example a bound VAO is required for a draw command in modern OpenGL. GPUEngine simplifies the the process of working with VAOs the same way it does with buffers.

We load shaders the same way we did earlier:
\snippet "geGL 4 VAO/QtGui/OpenGLWindow.cpp" shaders
Since ve haven't dealt with model loading (yet?) we have our attributes stored staticaly in vectors, for convenience. We just need to send them to GPU.
\snippet "geGL 4 VAO/QtGui/OpenGLWindow.cpp" buffer_ctor
Now we setup VAO. Since we are interested only in basic features we use the equivalent of glAttribPointer, the attribute enabling and other things needed are done automaticaly. You can always mix the geGL object calls with "vanilla" OpenGL.
\snippet "geGL 4 VAO/QtGui/OpenGLWindow.cpp" VAO
And we need to render it. So we use the program, bind the VAO and call drawElements. Then the colored triangle should appear.
\snippet "geGL 4 VAO/QtGui/OpenGLWindow.cpp" render