#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;
in vec3 lightDirectionOut;
in vec4 vertexColoursOut;
in vec4 fragPosLightSpace;
in vec3 FragPos;


uniform sampler2D normalSampler;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;
uniform vec3 lightPos;
uniform vec3 viewPos;

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
uniform float bias=0.03;
uniform float scale = 0.015f;
uniform sampler2D heightMap;

float ShadowCalculation(vec4 fragPosLightSpace)
{
vec3 projCoords=fragPosLightSpace.xyz/fragPosLightSpace.w;
projCoords=projCoords*0.5f+0.5f;
float closestDepth=texture(shadowMap,projCoords.xy).r;
float currentDepth=projCoords.z;
float shadow = currentDepth>closestDepth?1.0:0.0;

return shadow;
}


void main()
{
	float height = texture(heightMap, vertexTextureCoordsOut).r;
	
	
	//vec2 correctedTexCoord = vertexTextureCoordsOut;
	vec3 cameraDirectionOutNorm = normalize(cameraDirectionOut);
	//bias = cameraDirectionOutNorm.xy / cameraDirectionOutNorm.z * (height * scale);
	//correctedTexCoord = correctedTexCoord - bias;
	
	//KS fix parallax bug
	vec2 correctedTexCoord=scale*vertexTextureCoordsOut.xy*height;
	correctedTexCoord=vertexTextureCoordsOut-correctedTexCoord-bias;

	vec3 bumpNormals = texture(normalSampler, correctedTexCoord).xyz;
	bumpNormals = normalize((bumpNormals*2.0f) - 1.0f);

	
	vec3 lightDir=normalize(-directionLight.direction);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	//float diffuseTerm = dot(vertexNormalOut, lightDir);
	//float specularTerm = pow(dot(vertexNormalOut, halfWayVec), specularPower);
	
	float diffuseTerm = dot(bumpNormals, lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);
	

	vec4 textureColour = texture(diffuseSampler, correctedTexCoord);
	vec4 specColour = texture(specularSampler, correctedTexCoord);

	float shadow=ShadowCalculation(fragPosLightSpace);
	
	//FragColor = vec4 ( halfWayVec, 1.0f);
	
	FragColor = (ambientMaterialColour*directionLight.ambientColour+(1.0-shadow)) + (textureColour*directionLight.diffuseColour*diffuseTerm) + (specColour*directionLight.specularColour*specularTerm);
}
