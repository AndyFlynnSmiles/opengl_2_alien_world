float clampAngle(float angle)
{
	while (angle < -180) { angle += 360; }
	while (angle > 180) { angle -= 360; }
	return angle;
}

float easeInOut(float t)
{
	return t * t * (3 - 2 * t);
}