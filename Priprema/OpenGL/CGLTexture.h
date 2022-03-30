#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include "DImage.h"

class CGLTexture
{
protected:
	GLuint m_ID;

public:
	CGLTexture();
	virtual ~CGLTexture();
	static void PrepareTexturing(bool lighting_enabled);

	virtual void Load(CString file, GLenum s_wrap_mode = GL_REPEAT, GLenum t_wrap_mode = GL_REPEAT, GLenum mag_filter = GL_LINEAR, GLenum min_filter = GL_LINEAR_MIPMAP_LINEAR);
	virtual void Select();
	virtual void Release();
};

