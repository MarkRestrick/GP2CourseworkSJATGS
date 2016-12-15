#include "PostProcess.h"

PostProcess::PostProcess()
{
	m_PostBuffer = nullptr;
	m_ScreenAlignedQuad = nullptr;
	m_PostEffect = nullptr;
}

PostProcess::~PostProcess()
{

}

bool PostProcess::create(int bufferWidth, int bufferHeight, const string& vsFilename, const string& fsFilename)
{
	m_PostBuffer = unique_ptr<PostProcessBuffer>(new PostProcessBuffer());
	m_PostBuffer->create(bufferWidth, bufferHeight);

	m_ScreenAlignedQuad = unique_ptr<ScreenAlignedQuad>(new ScreenAlignedQuad());
	m_ScreenAlignedQuad->create();

	m_PostEffect = unique_ptr<PostProcessingEffect>(new PostProcessingEffect());
	m_PostEffect->loadShader(fsFilename);

	return true;
}

void PostProcess::destroy()
{
	m_PostBuffer->destroy();
	m_PostEffect->destroy();
	m_ScreenAlignedQuad->destroy();
}