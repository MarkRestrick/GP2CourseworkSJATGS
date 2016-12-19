#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec4 fragPosLightSpace;
in vec3 FragPos;


uniform sampler2D shadowMap;
uniform vec3 lightPos;
uniform vec3 lightDirection;

uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform vec4 diffuseMaterialColour=vec4(0.8f,0.0f,0.0f,1.0f);
uniform vec4 specularMaterialColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform float specularPower=25.0f;

uniform vec4 ambientLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform vec4 diffuseLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform vec4 specularLightColour=vec4(1.0f,1.0f,1.0f,1.0f);

float ShadowCalculation(vec4 fragPosLightSpace)
{
vec3 projCoords=fragPosLightSpace.xyz/fragPosLightSpace.w;
projCoords=projCoords*0.5+0.5;
float closestDepth=texture(shadowMap,projCoords.xy).r;
float currentDepth=projCoords.z;
float shadow = currentDepth>closestDepth? 1.0:0.0;

return shadow;
}

void main()
{
	vec3 lightDir=normalize(-lightDirection);
	float diffuseTerm = dot(vertexNormalOut, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(vertexNormalOut, halfWayVec), specularPower);

	
	float shadow=ShadowCalculation(fragPosLightSpace);
	
	FragColor = (ambientMaterialColour*ambientLightColour) + (((diffuseMaterialColour*diffuseLightColour*diffuseTerm) + (specularMaterialColour*specularLightColour*specularTerm))*(1.0-shadow));
}
