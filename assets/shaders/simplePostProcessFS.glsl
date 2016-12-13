2 lines (8 sloc)  150 Bytes
#version 410

out vec4 FragColor;
in vec2 textureCoords;

uniform sampler2D texture0;

void main()
{
	FragColor = texture(texture0, textureCoords);
}