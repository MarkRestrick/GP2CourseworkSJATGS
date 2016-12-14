#include "PostProcessingEffect.h"
#include "Shader.h"

const string postProcessingVSShaderCode =
"#version 410\n"
"\n"
"layout(location=0) in vec2 vertexPosition;\n"
"\n"
"out vec2 textureCoords;\n"
"\n"
"void main()\n"
"{\n"
"	textureCoords = (vertexPosition + 1.0) / 2.0;\n"
"	gl_Position = vec4(vertexPosition, 0.0, 1.0);\n"
"}\n";

PostProcessingEffect::PostProcessingEffect()
{
	m_ShaderProgram = 0;
}

PostProcessingEffect::~PostProcessingEffect()
{
}

bool PostProcessingEffect::loadShader(const string & FSFilename)
{
	GLuint vertexShaderProgram = loadShaderFromMemory(postProcessingVSShaderCode.c_str(), VERTEX_SHADER);
	GLuint fragmentShaderProgram = loadShaderFromFile(FSFilename, FRAGMENT_SHADER);

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	logShaderInfo(m_ShaderProgram);

	return false;
}