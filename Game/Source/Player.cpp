#include "Player.h"
#include "Engine.h"
#include "Bullet.h"
#include "Scene.h"
#include "GameData.h"
#include "SpaceGame.h"

#include <iostream>

void Player::Update(float dt)
{
	// movement
	Vector2 direction{ 0, 0 };
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.x = 1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.x = -1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q)) direction.y = -1;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E)) direction.y = 1;

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) m_transform.rotation -= Math::DegToRad(200) * dt;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) m_transform.rotation += Math::DegToRad(200) * dt;

	Vector2 acceleration = direction.Rotate(m_transform.rotation) * m_speed;
	m_velocity += acceleration * dt;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());

	// fire
	m_fireModTimer -= dt;
	if (m_fireModTimer <= 0) m_fireModifier = 1;

	m_fireTimer -= dt;
	if (g_engine.GetInput().GetMouseButtonDown(0) && m_fireTimer <= 0) //!g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
	{
		g_engine.GetAudioSFX().PlaySound("shoot.mp3");
		m_fireTimer = 0.5f * m_fireModifier;

		Vector2 direction = g_engine.GetInput().GetMousePosition() - m_transform.position;
		float angle = direction.Angle();

		// actor
		Model* model = new Model{ GameData::shipPoints, Color{ 1, 0, 0 } };
		Transform transform{ m_transform.position, angle, 1.0f };

		auto bullet = std::make_unique<Bullet>(400.0f, transform, model);
		bullet->SetLifespan(1);
		bullet->SetTag("PlayerBullet");
		m_scene->AddActor(std::move(bullet));
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (!isShielded) 
	{
		if (actor->GetTag() == "Asteroid")
		{
			m_destroyed = true;
			dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath();
		}
	}
	else {
		isShielded = false;
	}
}
