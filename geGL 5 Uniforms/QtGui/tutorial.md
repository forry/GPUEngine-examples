
 \example "geGL 4 VAO"

In this example we will look into OpenGL buffers. We can create and initialize buffer in constructor or just create an empty buffer. We need to specify the size.
\snippet OpenGLWindow.cpp buffer_ctor
We can copy content of one buffer into another (sizes and offsets have to be accounted for).
\snippet OpenGLWindow.cpp buffer_cpy
Then we can read the copied data back out to a cpu memory.
\snippet OpenGLWindow.cpp buffer_read
Or we can map the buffer into a pinned memory and used it from cpu side.
\snippet OpenGLWindow.cpp buffer_map
Of course we should unmap the buffer when we no longer need it.
