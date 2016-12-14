#ifndef DEPTHFRAMEBUFFER_H
#define DEPTHFRAMEBUFFER_H

#include "Common.h"

class depthFrameBuffer
{
public:
	depthFrameBuffer();
	~depthFrameBuffer();
	
	bool create();
	void bind();
	void unbind();
	GLuint GetTexture()
	{
		return depthMap;
	};
private:
	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	const GLuint SCR_WIDTH = 1024, SCR_HEIGHT = 768;
	GLuint depthMapFBO;
	GLuint depthMap;
};

#endif