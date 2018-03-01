#version 330

in vs_output_interface
{
    vec3 color;
}attribs;

out vec4 fragColor;

void main()
{
    fragColor = vec4(attribs.color,1.0f);
}