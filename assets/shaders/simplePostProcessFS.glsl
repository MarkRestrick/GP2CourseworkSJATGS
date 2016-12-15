#version 410

out vec4 FragColor;
in vec2 textureCoords;

uniform sampler2D texture0;

void main()
{
    //float depthValue = texture(texture0, textureCoords).r;
    //FragColor = vec4(vec3(depthValue), 1.0);
	FragColor = texture(texture0, textureCoords);
}









/*
out vec4 FragColor;
in vec2 textureCoords;

uniform sampler2D texture0;

void main()
{
	FragColor = texture(texture0, textureCoords);
}
*/