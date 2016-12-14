#ifndef POSTPROCESS_H
#define POSTPROCESS_H

#include "Common.h"
#include "PostProcessBuffer.h"
#include "PostProcessingEffect.h"
#include "ScreenAlignedQuad.h"

class PostProcess
{
public:
	PostProcess();
	~PostProcess();

	bool create(int bufferWidth, int bufferHeight, const string& fsFilename);
	void destroy();

	PostProcessBuffer * getBuffer()
	{
		return m_PostBuffer.get();
	};

	ScreenAlignedQuad * getQuad()
	{
		return m_ScreenAlignedQuad.get();
	};

	PostProcessingEffect * getEffect()
	{
		return m_PostEffect.get();
	};

private:
	unique_ptr<PostProcessBuffer> m_PostBuffer;
	unique_ptr<ScreenAlignedQuad> m_ScreenAlignedQuad;
	unique_ptr<PostProcessingEffect> m_PostEffect;
};

#endif