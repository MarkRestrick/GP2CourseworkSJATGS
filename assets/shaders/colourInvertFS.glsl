#version 410

out vec4 FragColor;
in vec2 textureCoords;

uniform sampler2D texture0;
uniform mat3 colourFilter = mat3(0.238, 0.238, 0.238,
	0.130, 0.130, 0.130,
	0.238, 0.238, 0.238);

void main()
{

	vec3 textureColour=texture(texture0, textureCoords).rgb;
	//textureColour=textureColour*colourFilter;
	FragColor=vec4(1.0 - textureColour,1.0f);
}