#pragma once
#include "Actor.h"
#include "Engine.h"

class Asteroid : public Actor
{
public:
	Asteroid() = default;
	Asteroid(const Transform& transform) : Actor{ transform } {}
	Asteroid(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}
	Asteroid(float speed, const Transform& transform, Model* model) :
		Actor{ transform, model },
		m_speed{ speed }
	{}

	void Update(float dt);
	virtual void OnCollision(Actor* actor);

	void setSmall(bool small);

private:
	bool isSmall;
	float m_speed = 0;
	Vector2 m_direction = Vector2{ randomf(0, g_engine.GetRenderer().GetWidth()), randomf(0, g_engine.GetRenderer().GetHeight()) } - m_transform.position;
};