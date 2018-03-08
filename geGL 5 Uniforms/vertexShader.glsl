#version 430

in layout(location = 0) vec3 position;

layout(std430, binding=0) buffer perDrawData_t
{
    mat4 model[];
};


//uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model[0] *  vec4(position,1.0f);
}