#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::setCollider(vec3 high, vec3 low)
{
	m_High = high;
	m_Low = low;
}

void BoxCollider::scaleCollider()
{
	m_High.x *= m_Scale.x;
	m_Low.x *= m_Scale.x;
	m_High.y *= m_Scale.y;
	m_Low.y *= m_Scale.y;
	m_High.z *= m_Scale.z;
	m_Low.z *= m_Scale.z;

	cout << m_Position.x + m_High.x << " " << m_Position.x + m_Low.x << " " << m_Position.y + m_High.y << " " << m_Position.y + m_Low.y << " " << m_Position.z + m_High.z << " " << m_Position.z + m_Low.z << "\n";
}

bool BoxCollider::checkCollision(vec3 position)
{

	if (!scaled)
	{
		scaleCollider();
		scaled = true;
	}

	m_xCollision = false;
	m_yCollision = false;
	m_zCollision = false;

	if (position.x < m_Position.x + m_High.x && position.x >  m_Position.x + m_Low.x)
	{
		m_xCollision = true;
	}

	if (position.y <  m_Position.y + m_High.y && position.y >  m_Position.y + m_Low.y)
	{
		m_yCollision = true;
	}

	if (position.z <  m_Position.z + m_High.z && position.z >  m_Position.z + m_Low.z)
	{
		m_zCollision = true;
	}

	if (m_xCollision == true && m_yCollision == true && m_zCollision == true)
	{
		return true;
	}

	return false;
}