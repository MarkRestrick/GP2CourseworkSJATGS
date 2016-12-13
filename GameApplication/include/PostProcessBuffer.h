#ifndef POSTPROCESSBUFFER_H
#define POSTPROCESSBUFFER_H

#include "Common.h"

class PostProcessBuffer
{
public:
	PostProcessBuffer();
	~PostProcessBuffer();

	bool create(unsigned int width, unsigned int height);
	void destroy();

	void bind();
	void unbind();

	GLuint GetTexture()
	{
		return m_Texture;
	};
private:
	GLuint m_Texture;
	GLuint m_Sampler;
	GLuint m_DepthBuffer;
	GLuint m_Framebuffer;
};

#endif