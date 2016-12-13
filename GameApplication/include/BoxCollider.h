#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Common.h"

class BoxCollider
{
public:
	BoxCollider();
	~BoxCollider();

	void setTransform(vec3 position, vec3 scale);

	bool checkCollision(vec3 position);

private:

	vec3 m_Position;
	vec3 m_ColliderSize;
	bool m_xCollision = false;
	bool m_yCollision = false;
	bool m_zCollision = false;
};
#endif