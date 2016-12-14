#include "CameraController.h"

CameraController::CameraController()
{
	m_CameraRotation = vec3(0.0f, radians(270.0f), 0.0f);
	m_CameraPosition = vec3(0.0f, 25.0f, 150.0f);

	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), 0, sin(m_CameraRotation.y));
}

CameraController::~CameraController()
{
}


void CameraController::moveForward()
{
	m_CameraPosition += vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), 0, sin(m_CameraRotation.y));
}

void CameraController::moveBackward()
{
	m_CameraPosition -= vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), 0, sin(m_CameraRotation.y));
}

void CameraController::rotateCamera(float amount)
{
	if (amount > 0)
	{
		m_CameraRotation += vec3(0.0f, radians(amount), 0.0f);
		if (m_CameraRotation.y > 3.141592654f * 2)
		{
			m_CameraRotation += vec3(0.0f, -radians(360.0f), 0.0f);
		}
	}
	if (amount < 0)
	{
		m_CameraRotation += vec3(0.0f, radians(amount), 0.0f);
		if (m_CameraRotation.y < 0)
		{
			m_CameraRotation += vec3(0.0f, radians(360.0f), 0.0f);
		}
	}
	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), 0, sin(m_CameraRotation.y));
}