#pragma once
#include "Actor.h"

class Shield : public Actor
{
public:
	Shield() = default;
	Shield(const Transform& transform) : Actor{ transform } {}
	Shield(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}

	void OnCollision(Actor* actor) override;

protected:
	float m_fireModTimer = 0;
};