#version 410

layout (location = 0) in vec3 vertexPosition;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

out vec2 textureCoords;

void main()
{
    gl_Position = lightSpaceMatrix * model * vec4(vertexPosition, 1.0f);
}  