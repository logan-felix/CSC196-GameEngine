#include "Asteroid.h"
#include "Player.h"
#include "Scene.h"
#include "Game.h"
#include "Engine.h"
#include "GameData.h"

void Asteroid::Update(float dt)
{
	m_velocity += m_direction.Normalized() * m_speed * dt;
	m_transform.rotation = m_direction.Angle();

	Actor::Update(dt);
}

void Asteroid::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "PlayerBullet")
	{
		if (isSmall) 
		{
			m_scene->GetGame()->AddPoints(50);
			m_destroyed = true;
		}
		else {
			m_destroyed = true;
			auto* smallAsteroidModel = new Model{ GameData::smallAsteroidPoints, Color{ 1, 1, 1 } };

			auto asteroid = std::make_unique<Asteroid>(100, m_transform, smallAsteroidModel);
			asteroid->SetDamping(1.0f);
			asteroid->SetTag("Asteroid");
			asteroid->setSmall(true);

			auto asteroid2 = std::make_unique<Asteroid>(100, m_transform, smallAsteroidModel);
			asteroid2->SetDamping(1.0f);
			asteroid2->SetTag("Asteroid");
			asteroid2->setSmall(true);

			m_scene->AddActor(std::move(asteroid));
			m_scene->AddActor(std::move(asteroid2));
		}
	}
	else if (actor->GetTag() == "Player")
	{
		m_destroyed = true;
	}
}

void Asteroid::setSmall(bool small)
{
	this->isSmall = small;
}
