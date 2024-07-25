#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt)
{
	// create particle trail
	for (int i = 0; i < 100; i++)
	{
		Particle::Data data
		{
			m_transform.position,
			Vector2{ 1, 0 }.Rotate(randomf(Math::TwoPi)) * 150,
			randomf(0.5f, 2.0f),
			255, 255, 255, 255
		};
		g_engine.GetPS().AddParticle(data);
	}

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
