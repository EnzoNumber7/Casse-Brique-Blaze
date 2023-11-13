#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
public:
	bool			isMoving;

	Ball();

	void			Move(float deltaTime);
	void			Rebound(char direction, float deltaTime);
	void			OnCollisionStay(char direction, float deltaTime) override;
};

