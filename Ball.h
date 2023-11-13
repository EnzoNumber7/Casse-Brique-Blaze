#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
public:
	bool			isMoving;

	Ball();

	void			Move(float deltaTime);
	void			Rebound(CollisionSide direction, float deltaTime);
	void			OnCollisionEnter(const GameObject& Object, float deltaTime) override;
	void			OnCollisionStay(float deltaTime) override;
};

