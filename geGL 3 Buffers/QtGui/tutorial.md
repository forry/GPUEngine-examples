
\example "geGL 3 Buffers"

In this example we will look into OpenGL buffers. We can create and initialize buffer in constructor or just create an empty buffer. We need to specify the size.
\snippet "geGL 3 Buffers/QtGui/OpenGLWindow.cpp" buffer_ctor
We can realoc buffers easily but then tey need to be in shared pointer form since the internal implementation is creating a new buffer and then optionali it can also copy old data to it (see flags).
\snippet "geGL 3 Buffers/QtGui/OpenGLWindow.cpp" buffer_realoc
We can copy content of one buffer into another (sizes and offsets have to be accounted for).
\snippet "geGL 3 Buffers/QtGui/OpenGLWindow.cpp" buffer_cpy
Then we can read the copied data back out to a cpu memory.
\snippet "geGL 3 Buffers/QtGui/OpenGLWindow.cpp" buffer_read
Or we can map the buffer into a pinned memory and used it from cpu side.
\snippet "geGL 3 Buffers/QtGui/OpenGLWindow.cpp" buffer_map
Of course we should unmap the buffer when we no longer need it.
