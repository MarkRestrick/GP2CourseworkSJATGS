#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "Common.h"

class CameraController
{
public:
	CameraController();
	~CameraController();

	vec3 getCameraPosition()
	{
		return m_CameraPosition;
	};

	vec3 getLookAtPosition()
	{
		return m_CameraPosition + m_CameraLookAtPosition;
	};

	float getCameraRotation()
	{
		return m_CameraRotation.y;
	};

	vec3 collisionCheck(bool forwards)
	{
		if (forwards)
			return m_CameraPosition + vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
		else
			return m_CameraPosition - vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	};

	void moveForward();
	void moveBackward();
	void rotateCamera(float amount);

private:
	vec3 m_CameraPosition;
	vec3 m_CameraRotation;
	vec3 m_CameraLookAtPosition;
};

#endif