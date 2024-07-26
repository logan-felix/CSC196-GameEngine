#pragma once
#include "Game.h"

class Font;
class Text;

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

	void OnPlayerDeath();

private:
	eState m_state{ eState::Title };
	float m_spawnTimer{ 0 };
	float m_spawnTime{ 0 };
	float m_stateTimer{ 0 };
	float m_pickupTimer{ 0 };
	float m_shieldTimer{ 0 };

	Font* m_font{ nullptr };
	Font* m_fontLarge{ nullptr };
	Text* m_textScore{ nullptr };
	Text* m_textLives{ nullptr };

	Text* m_textTitle{ nullptr };

	Text* m_textPickup{ nullptr };
};