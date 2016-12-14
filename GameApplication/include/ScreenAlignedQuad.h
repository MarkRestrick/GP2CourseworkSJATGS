#ifndef SCREEN_ALIGNED_QUAD_H
#define SCREEN_ALIGNED_QUAD_H

#include "Common.h"

class ScreenAlignedQuad
{
public:
	ScreenAlignedQuad();
	~ScreenAlignedQuad();

	void create();
	void render();
	void destroy();
private:
	GLuint m_VBO;
	GLuint m_VAO;
};
#endif