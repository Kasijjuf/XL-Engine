#include <stdlib.h>
#include "../../log.h"
#include "graphicsDeviceOGL.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

GraphicsDeviceOGL::GraphicsDeviceOGL(GraphicsDevicePlatform* platform) : GraphicsDevice(platform)
{
}

GraphicsDeviceOGL::~GraphicsDeviceOGL()
{
}

void GraphicsDeviceOGL::present()
{
	m_platform->present();
}

void GraphicsDeviceOGL::setWindowData(int nParam, void** param)
{
	m_platform->setWindowData(nParam, param);
	glClearColor(0, 0, 0, 0);

	//default vsync to off for now.
	m_platform->enableVSync(false);
}

void GraphicsDeviceOGL::clear()
{
	glClear( GL_COLOR_BUFFER_BIT );
}

void GraphicsDeviceOGL::setBlendMode(BlendMode mode)
{
	const u32 srcBlend[] = { GL_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE };	//OVER, ALPHA ADD, ADD
	const u32 dstBlend[] = { GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE };

	glBlendFunc(srcBlend[mode], dstBlend[mode]);
}

void GraphicsDeviceOGL::enableBlending(bool enable)
{
	if (enable)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

void GraphicsDeviceOGL::convertFrameBufferTo32bpp(u8* pSource, u32* pal)
{
	u32 *pDest = m_pFrameBuffer_32bpp;

	u32 uPixelCount = m_FrameWidth*m_FrameHeight;
	for (u32 p=0; p<uPixelCount; p++)
	{
		*pDest = pal[ *pSource ];
		pDest++;
		pSource++;
	}
}