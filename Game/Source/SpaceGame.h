#pragma once
#include "Game.h"

class SpaceGame : public Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};

public:
	SpaceGame(Engine* engine) : Game{ engine } 
	{
		
	}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

private:
	eState m_state{ eState::Title };
	float m_spawnTimer{ 0 };
	float m_spawnTime{ 0 };
};