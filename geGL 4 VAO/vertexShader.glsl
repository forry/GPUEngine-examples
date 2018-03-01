#version 330

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;

out vs_output_interface
{
    vec3 color;
}attribs;

void main()
{
    attribs.color = color;
    gl_Position = vec4(position,1.0f);
}