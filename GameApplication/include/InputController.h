#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "Common.h"

class InputController
{
public:
	InputController();
	~InputController();

	vec3 getCameraPosition()
	{
		return m_CameraPosition;
	};

private:
	vec3 m_CameraPosition;
};

#endif // !INPUTCONTROLLER_h

