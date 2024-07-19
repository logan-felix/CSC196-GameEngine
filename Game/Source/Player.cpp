#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "GameData.h"

#include <iostream>

void Player::Update(float dt)
{
	// movement
	float thrust = 0;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -m_speed;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) m_transform.rotation -= Math::DegToRad(200) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) m_transform.rotation += Math::DegToRad(200) * dt;

	Vector2 acceleration = Vector2{ 1.0f, 0.0f }.Rotate(m_transform.rotation) * thrust;
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	// fire
	m_fireTimer -= dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0)//!g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
	{
		m_fireTimer = 0.2f;

		// actor
		Model* model = new Model{ GameData::shipPoints, Color{ 1, 0, 0 } };
		Transform transform{ m_transform.position, m_transform.rotation, 1.0f };

		Bullet* bullet = new Bullet(400.0f, transform, model);
		bullet->SetLifespan(1);
		bullet->SetTag("PlayerBullet");
		m_scene->AddActor(bullet);
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy")
	{
		m_destroyed = true;
	}
}
