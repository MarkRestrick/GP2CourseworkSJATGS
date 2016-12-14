#include "PostProcessBuffer.h"

PostProcessBuffer::PostProcessBuffer()
{
	m_Texture = 0;
	m_Sampler = 0;
	m_DepthBuffer = 0;
	m_Framebuffer = 0;
}

PostProcessBuffer::~PostProcessBuffer()
{

}

bool PostProcessBuffer::create(unsigned int width, unsigned int height)
{
	glGenSamplers(1, &m_Sampler);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glGenRenderbuffers(1, &m_DepthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &m_Framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBuffer);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG(ERROR, "%s", "Framebuffer incomplete");
		destroy();
		return false;
	}

	return true;
}

void PostProcessBuffer::destroy()
{
	glDeleteFramebuffers(1, &m_Framebuffer);
	glDeleteRenderbuffers(1, &m_DepthBuffer);
	glDeleteTextures(1, &m_Texture);
	glDeleteSamplers(1, &m_Sampler);
}

void PostProcessBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void PostProcessBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}