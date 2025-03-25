#include "Vector3.hpp"
using namespace std;


Vector3 vecZero = Vector3(0, 0, 0);


Vector3 vecNorm(Vector3 vec)
{
	float length = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	if (length == 0) {
		return Vector3(0, 0, 0);
	}
	else {
		return Vector3(vec.x / length, vec.y / length, vec.z / length);
	}
}

Vector3 vecAdd(Vector3 a, Vector3 b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 vecSub(Vector3 a, Vector3 b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector3 vecScale(Vector3 vec, float scale)
{
	return Vector3(vec.x * scale, vec.y * scale, vec.z * scale);
}

Vector3 headingToNormalRad(float yaw, float pitch)
{
	return Vector3(cos(yaw) * cos(pitch), sin(pitch), sin(yaw) * cos(pitch));
}

float vecDis(Vector3 a, Vector3 b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}