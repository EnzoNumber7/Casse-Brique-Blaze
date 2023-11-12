#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
public:

	Ball();

	void			Move(float deltaTime);
	void			Rebound(char direction, float deltaTime);
};

