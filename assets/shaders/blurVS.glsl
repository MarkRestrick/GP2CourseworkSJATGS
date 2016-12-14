#version 410

layout (location = 0) in vec2 vertexPosition;


out vec2 textureCoords;

void main()
{
    gl_Position = vec4(vertexPosition, 0.0, 1.0);
    textureCoords = (vertexPosition + 1.0) / 2.0;
}  