#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt)
{
	m_velocity = Vector2{ 1, 0 }.Rotate(m_transform.rotation) * m_speed;



	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy")
	{
		m_destroyed = true;
	}
}
