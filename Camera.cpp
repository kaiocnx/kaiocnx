#include "Library.h"
#include "Camera.h"

Camera::Camera() : Active(false), Moving(false), X(0), Y(0), Side(0)
{
}

Camera::~Camera()
{
}

void Camera::Restore()
{
	pCameraZoom = 35.f;
	pCameraRotY = 48.5f;
	pCameraRotZ = -45.f;
	pCameraPosZ = 150.f;

	this->FixClip();
}

void Camera::Start(int PosX, int PosY)
{
	if (this->Active)
	{
		this->X = PosX;
		this->Y = PosY;
		this->Moving = true;
	}
}

void Camera::End()
{
	if (this->Moving)
	{
		this->Moving = false;

		switch (this->Side)
		{
			case 1: // Right
			{
				pCameraRotZ += 0.5f;
				Sleep(1);
				pCameraRotZ += 0.4f;
				Sleep(1);
				pCameraRotZ += 0.3f;
				Sleep(1);
				pCameraRotZ += 0.2f;
				Sleep(1);
				pCameraRotZ += 0.1f;

				break;
			}
			case 2: // Left
			{
				pCameraRotZ -= 0.5f;
				Sleep(1);
				pCameraRotZ -= 0.4f;
				Sleep(1);
				pCameraRotZ -= 0.3f;
				Sleep(1);
				pCameraRotZ -= 0.2f;
				Sleep(1);
				pCameraRotZ -= 0.1f;
				
				break;
			}
		}

		this->Side = 0;
	}
}

void Camera::SetZoom(int Direction)
{
	if (this->Active && pState == STATE_PLAYING)
	{
		if (Direction > 0)
		{
			if (pCameraZoom > 20.f)
			{
				pCameraZoom -= 2.f;
			}

			if (pCameraZoom < 20.f)
			{
				pCameraZoom = 20.f;
			}
		}
		else if (Direction < 0)
		{
			if (pCameraZoom < 62.f) // 62
			{
				pCameraZoom += 2.f;
			}

			if (pCameraZoom > 62.f)
			{
				pCameraZoom = 62.f;
			}
		}

		this->Distance = pCameraZoom * 10.f;

		this->FixClip();
	}
}

void Camera::Move(int PosX, int PosY)
{
	if (this->Moving)
	{
		if (this->X < PosX)
		{
			pCameraRotZ += 5.f;

			if (pCameraRotZ > 315.f)
			{
				pCameraRotZ = -45.f;
			}

			this->Side = 1; // Right
		}
		else if (this->X > PosX)
		{
			pCameraRotZ -= 5.f;

			if (pCameraRotZ < -405.f)
			{
				pCameraRotZ = -45.f;
			}

			this->Side = 2; // Left
		}

		if (this->Y < PosY)
		{
			if (pCameraRotY > 45.f)
			{
				pCameraPosZ -= 44.f;
				pCameraRotY -= 2.42f;
			}
		}
		else if (this->Y > PosY)
		{
			if (pCameraRotY < 90.f)
			{
				pCameraPosZ += 44.f;
				pCameraRotY += 2.42f;
			}
		}

		this->X = PosX;
		this->Y = PosY;

		this->FixClip();
	}
}

void Camera::FixClip()
{
	auto Absolute = abs(pCameraPosZ - 150.f) * 3.f;

	pCameraClipX = (((pScreenWidth >= 1280) ? 3190.f : 2190.f) + Absolute) * 2.2f + this->Distance;
	pCameraClipX2 = (((pScreenWidth >= 1280) ? 3190.f : 2190.f) + Absolute) * 2.2f + this->Distance;
	pCameraClipY = (2400.f + Absolute) * 2.2f + this->Distance;
	pCameraClipY2 = (2400.f + Absolute) * 2.2f + this->Distance;
	pCameraClipB = (1128.f + Absolute) * 2.2f + this->Distance;
	pCameraClipGL = (2100.f + Absolute) * 2.2f + this->Distance;
}

Camera gCamera;