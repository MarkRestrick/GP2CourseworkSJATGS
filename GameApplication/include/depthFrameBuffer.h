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
	const GLuint SHADOW_WIDTH = 640, SHADOW_HEIGHT = 480;
	const GLuint SCR_WIDTH = 640, SCR_HEIGHT = 480;
	GLuint depthMapFBO;
	GLuint depthMap;
};

#endif