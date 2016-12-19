#include "CameraController.h"

CameraController::CameraController()
{
	m_CameraRotation = vec3(0.0f, radians(270.0f), 0.0f);
	m_CameraPosition = vec3(0.0f, 25.0f, 90.0f);

	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), 0, sin(m_CameraRotation.y));
}

CameraController::~CameraController()
{
}


vec3 CameraController::collisionCheck(string direction)
{
	if (direction == "Forward")
	{
		return m_CameraPosition + vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	}
	else if (direction == "Backward")
	{
		return m_CameraPosition - vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	}
	else if (direction == "Right")
	{
		return m_CameraPosition + vec3(-sin(m_CameraRotation.y), 0.0f, cos(m_CameraRotation.y));
	}
	else
	{
		return m_CameraPosition - vec3(-sin(m_CameraRotation.y), 0.0f, cos(m_CameraRotation.y));
	}
}

void CameraController::move(string direction)
{
	if (direction == "Forward")
	{
		m_CameraPosition += vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	}
	else if (direction == "Backward")
	{
		m_CameraPosition -= vec3(-sin(m_CameraRotation.y - radians(90.0f)), 0.0f, cos(m_CameraRotation.y - radians(90.0f)));
	}
	else if (direction == "Right")
	{
		m_CameraPosition += vec3(-sin(m_CameraRotation.y), 0.0f, cos(m_CameraRotation.y));
	}
	else
	{
		m_CameraPosition -= vec3(-sin(m_CameraRotation.y), 0.0f, cos(m_CameraRotation.y));
	}

	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), -tan(m_CameraRotation.x), sin(m_CameraRotation.y));
}


void CameraController::mouseRotation(float x, float y)
{
	m_CameraRotation += vec3(radians(y/2), radians(x/2), 0.0f);

	if (m_CameraRotation.x < radians(-80.0f))
		m_CameraRotation += vec3(radians(-y/2), 0.0f, 0.0f);

	if (m_CameraRotation.x > radians(80.0f))
		m_CameraRotation += vec3(radians(-y/2), 0.0f, 0.0f);

	m_CameraLookAtPosition = vec3(cos(m_CameraRotation.y), -tan(m_CameraRotation.x), sin(m_CameraRotation.y));
}

void CameraController::onUpdate()
{

	if (m_Force <= 0.1 && m_Jumping)
	{
		m_Jumping = false;
	}

	if (!m_Jumping && !m_Grounded)
	{
		m_CameraPosition -= vec3(0.0f, m_Force, 0.0f);
		m_Force += 0.1;
		if (m_Force < -24)
		{
			m_Force -= 0.1;
		}
	}

	if (m_Force > 0.1 && m_Jumping)
	{
		m_CameraPosition += vec3(0.0f, m_Force, 0.0f);
		m_Force -= 0.1;
	}

	if (m_Grounded && !m_Jumping)
	{
		m_Force = 0.0f;
	}

	//cout << m_Force << " " << m_Grounded << "\n";
}

void CameraController::jump(bool debug)
{
	if (!debug)
	{
		if (m_Grounded)
		{
			m_Force = 4.0f;
			m_Jumping = true;
		}
	}
	else
	{
		m_CameraPosition += vec3(0.0f, 3.0f, 0.0f);
	}

}

void CameraController::down()
{
	m_CameraPosition -= vec3(0.0f, 1.0f, 0.0f);
}

