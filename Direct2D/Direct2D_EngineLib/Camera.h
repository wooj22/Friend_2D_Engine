#pragma once
#include "Transform.h"

class Camera
{
public:
	float width, height;
	Transform* transform;

	//Camera(int w, int h) : width(w), height(h) {};
	Camera() { transform = new Transform; }
	~Camera() { if (transform) delete transform; }
	void SetSize(int w, int h) { width = w;	height = h; }
};

