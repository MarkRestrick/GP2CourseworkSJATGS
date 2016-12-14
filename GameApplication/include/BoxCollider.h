#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Common.h"

class BoxCollider
{
public:
	BoxCollider();
	~BoxCollider();

	void setCollider(vec3 high, vec3 low);

	void scaleCollider();

	void setTransform(vec3 position, vec3 scale)
	{
		m_Position = position;
		m_Scale = scale;
	};
	bool checkCollision(vec3 position);

	void onRender();

private:

	vec3 m_Position;
	vec3 m_Scale;

	vec3 m_High;
	vec3 m_Low;

	bool m_xCollision = false;
	bool m_yCollision = false;
	bool m_zCollision = false;

	bool scaled = false;
};
#endif