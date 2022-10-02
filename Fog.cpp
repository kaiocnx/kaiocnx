#include "Library.h"
#include "Fog.h"
#include "Camera.h"
#include "Win32.h"

Fog::Fog() : Active(false), Color{}, Default{0.0f, 0.0f, 0.0f, 0.0f}
{
}

Fog::~Fog()
{
}

void Fog::Load()
{
	// Para adicionar a neblina, basta:
	// this->Add(<map_number>, <red>, <green>, <blue>, <alpha>);
}

void Fog::Add(BYTE Map, BYTE Red, BYTE Green, BYTE Blue, BYTE Alpha)
{
	this->Color[Map] = {(float)(Red / 255.f), (float)(Green / 255.f), (float)(Blue / 255.f), (float)(Alpha / 255.f)};
}

void Fog::Apply(GLenum Mode)
{
	if (this->Active)
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (pState == STATE_SELECT_SERVER)
		{
			glDisable(GL_FOG);
		}
		else if (pState == STATE_PLAYING)
		{
			if (Mode == GL_BLEND || Mode == GL_TEXTURE_2D || Mode == GL_DEPTH_TEST)
			{
				glDisable(GL_FOG);
			}

			pglEnable(GL_FOG);

			glFogi(GL_FOG_MODE, GL_LINEAR);
			glFogf(GL_FOG_DENSITY, 0.25f);

			if (this->Color.count(pMapNumber) > 0)
			{
				glFogfv(GL_FOG_COLOR, (const GLfloat*)(&this->Color.at(pMapNumber)));
			}
			else
			{
				glFogfv(GL_FOG_COLOR, (const GLfloat*)(&this->Default));
			}

			glFogf(GL_FOG_START, 2000.f + gCamera.Distance);
			glFogf(GL_FOG_END, 2500.f + gCamera.Distance);
			glHint(GL_FOG_HINT, GL_NICEST);

			if (Mode == GL_BLEND || Mode == GL_TEXTURE_2D || Mode == GL_DEPTH_TEST)
			{
				glDisable(GL_FOG);
			}
		}
	}
}

bool Fog::Apply()
{
	if (this->Active)
	{
		if (pState == STATE_SELECT_SERVER)
		{
			glBindTexture(GL_TEXTURE_2D, *this->Textures);
			pglClearColor(0.f, 0.f, 0.f, 0.f);

			return true;
		}
		else if (pState == STATE_PLAYING)
		{
			glBindTexture(GL_TEXTURE_2D, *this->Textures);

			if (this->Color.count(pMapNumber) > 0)
			{
				pglClearColor(this->Color[pMapNumber].R, this->Color[pMapNumber].G, this->Color[pMapNumber].B, 0.f);
			}
			else
			{
				pglClearColor(this->Default.R, this->Default.G, this->Default.B, 0.f);
			}
			
			return true;
		}
	}

	return false;
}

Fog gFog;