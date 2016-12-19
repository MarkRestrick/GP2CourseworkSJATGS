#include "ScreenAlignedQuad.h"

ScreenAlignedQuad::ScreenAlignedQuad()
{
	m_VBO = 0;
	m_VAO = 0;
}

ScreenAlignedQuad::~ScreenAlignedQuad()
{
}

//Makes a quad object the size of the screen
void ScreenAlignedQuad::create()
{
	float vertices[] =
	{
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,
	};

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
}


//Renders the quad
void ScreenAlignedQuad::render()
{
	//glClearColor(1, 0, 0, 1); Used for debugging, sets quad to be red by default
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void ScreenAlignedQuad::destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}