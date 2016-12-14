#ifndef POSTPROCESSING_EFFECT_H
#define POSTPROCESSING_EFFECT_H

#include "Common.h"

class PostProcessingEffect
{
public:
	PostProcessingEffect();
	virtual ~PostProcessingEffect();

	bool loadShader(const string& FSFilename);

	GLuint getShaderProgram()
	{
		return m_ShaderProgram;
	}

	virtual void bind()
	{
		glUseProgram(m_ShaderProgram);
	};

	void destroy()
	{
		glDeleteProgram(m_ShaderProgram);
	};

private:
	GLuint m_ShaderProgram;
};
#endif