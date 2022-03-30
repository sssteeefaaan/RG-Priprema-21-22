#include "pch.h"
#include "CGLTexture.h"

CGLTexture::CGLTexture()
{
	m_ID = 0;
}

CGLTexture::~CGLTexture()
{
	Release();
}

void CGLTexture::PrepareTexturing(bool lighting_enabled)
{
	// Po default-u je vec ovako al kao ajde
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	if (lighting_enabled)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	else
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

}
void CGLTexture::Load(CString file, GLenum s_wrap_mode, GLenum t_wrap_mode, GLenum mag_filter, GLenum min_filter)
{
	if (!m_ID) Release();

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap_mode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

	DImage *img = new DImage();
	img->Load(file);
	img->Flip();

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img->Width(), img->Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img->GetDIBBits());

	delete(img);
}

void CGLTexture::Select()
{
	if (m_ID)
		glBindTexture(GL_TEXTURE_2D, m_ID);
}
void CGLTexture::Release()
{
	if (m_ID)
	{
		glDeleteTextures(1, &m_ID);
		m_ID = 0;
	}
}
