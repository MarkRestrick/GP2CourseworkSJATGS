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

	vec3 collisionCheck(string direction);

	void move(string direction);
	void mouseRotation(float x, float y);

	void onUpdate();

	void setGrounded(bool grounded)
	{
		m_Grounded = grounded;
	};

	float getForce()
	{
		return m_Force;
	};

	void jump(bool debug);
	void down();
private:
	vec3 m_CameraPosition;
	vec3 m_CameraRotation;
	vec3 m_CameraLookAtPosition;

	bool m_Grounded;
	float m_Force;
	bool m_Jumping = false;
};

#endif