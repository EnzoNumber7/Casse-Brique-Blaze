#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
public:
	bool			isMoving;

	Ball();

private:
	void			Rebound(CollisionSide direction, float deltaTime);

public:
	void			Move(float deltaTime);

	// Collisions Override

	void			OnCollisionEnter(const GameObject& Object, float deltaTime) override;
	void			OnCollisionStay(float deltaTime) override;
};

