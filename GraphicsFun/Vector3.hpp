#pragma once

#include <cmath>

struct Vector3 {
	float x;
	float y;
	float z;

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};


extern Vector3 vecZero;


Vector3 vecNorm(Vector3 vec);

Vector3 vecAdd(Vector3 a, Vector3 b);

Vector3 vecSub(Vector3 a, Vector3 b);

Vector3 vecScale(Vector3 vec, float scale);

Vector3 headingToNormalRad(float yaw, float pitch);

float vecDis(Vector3 a, Vector3 b);