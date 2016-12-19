#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;
in vec4 fragPosLightSpace;
in vec3 FragPos;

uniform sampler2D shadowMap;
//uniform vec3 lightPos;

struct DirectionalLight
{
	vec3 direction;

	vec4 ambientColour;
	vec4 diffuseColour;
	vec4 specularColour;
};

uniform DirectionalLight directionLight;



uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform vec4 diffuseMaterialColour=vec4(0.8f,0.0f,0.0f,1.0f);
uniform vec4 specularMaterialColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform float specularPower=25.0f;
uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform sampler2D normalSampler;

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
	vec3 lightDir=normalize(-directionLight.direction);
	
	float diffuseTerm = dot(vertexNormalOut, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(vertexNormalOut, halfWayVec), specularPower);
	vec4 textureColour = texture(diffuseSampler, vertexTextureCoordsOut);
	vec4 specColour = texture(specularSampler, vertexTextureCoordsOut);

	
	float shadow=ShadowCalculation(fragPosLightSpace);
	
	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (((textureColour*directionLight.diffuseColour*diffuseTerm) + (specColour*directionLight.specularColour*specularTerm))*(1.0-shadow));
}
