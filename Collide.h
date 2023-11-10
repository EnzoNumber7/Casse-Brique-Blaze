#pragma once

class GameObject;

class Collide
{
private:
	GameObject* c_object;
	GameObject* c_collider;

public:
	bool OnCollideEnter();
	bool OnCollideStay();
	bool OnCollideExit();
};

