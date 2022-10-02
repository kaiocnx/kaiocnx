#pragma once

class Camera
{
public:
	Camera();
	~Camera();

public:
	void Restore();
	void Start(int X, int Y);
	void End();
	void SetZoom(int Distance);
	void Move(int X, int Y);
	void FixClip();

public:
	bool Active;

private:
	bool Moving;
	int X;
	int Y;
	BYTE Side;

public:
	float Distance;
};

extern Camera gCamera;