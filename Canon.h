#pragma once

#include "GameObject.h"

class Canon : public GameObject
{
public:
	Canon();

	void	FollowMouse(GameWindow* window);
};

