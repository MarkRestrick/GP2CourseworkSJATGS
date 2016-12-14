#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::setTransform(vec3 position, vec3 scale)
{
	m_Position = position;
	m_ColliderSize = scale;
}

bool BoxCollider::checkCollision(vec3 position)
{
	m_xCollision = false;
	m_yCollision = false;
	m_zCollision = false;

	if (position.x < m_Position.x + m_ColliderSize.x && position.x > m_Position.x - m_ColliderSize.x)
	{
		m_xCollision = true;
	}

	if (position.y < m_Position.y + m_ColliderSize.y / 2 && position.y > m_Position.y - m_ColliderSize.y / 2)
	{
		m_yCollision = true;
	}

	if (position.z < m_Position.z + m_ColliderSize.z / 2 && position.z > m_Position.z - m_ColliderSize.z / 2)
	{
		m_zCollision = true;
	}

	if (m_xCollision == true && m_yCollision == true && m_zCollision == true)
	{
		return true;
	}

	return false;
}

