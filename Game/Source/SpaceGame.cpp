#include "SpaceGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "GameData.h"
#include "Enemy.h"
#include "Font.h"
#include "Text.h"
#include "Pickup.h"

bool SpaceGame::Initialize()
{
    m_scene = new Scene(this);

    m_font = new Font();
    m_font->Load("arcadeclassic.ttf", 20);

    m_fontLarge = new Font();
    m_fontLarge->Load("arcadeclassic.ttf", 72);

    m_textScore = new Text(m_font);
    m_textLives = new Text(m_font);
    m_textTitle = new Text(m_fontLarge);

    return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
    switch (m_state)
    {
    case eState::Title:
        if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
        {
            m_state = eState::StartGame;
        }
        break;
    case eState::StartGame:
        m_score = 0;
        m_lives = 3;

        m_state = eState::StartLevel;
        break;
    case eState::StartLevel:
        m_scene->RemoveAll();
        {
            Transform transform{ Vector2{ 400, 300 }, 0, 3 };
            Model* model = new Model{ GameData::shipPoints, Color{ 1, 1, 1 } };
            auto player = std::make_unique<Player>(randomf(300, 400), transform, model);
            player->SetDamping(2.0f);
            player->SetTag("Player");
            m_scene->AddActor(std::move(player));
        }

        m_spawnTime = 3;
        m_spawnTimer = m_spawnTime;
        
        m_state = eState::Game;
        break;
    case eState::Game:
        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0)
        {
            m_spawnTime -= 0.2f;
            m_spawnTimer = m_spawnTime;

            // create enemy
            auto* enemyModel = new Model{ GameData::shipPoints, Color{ 1, 1, 0 } };
            auto enemy = std::make_unique<Enemy>(100, Transform{ { randomf(0, g_engine.GetRenderer().GetWidth()), randomf(0, g_engine.GetRenderer().GetHeight()) }, 0, 4 }, enemyModel);
            enemy->SetDamping(1.0f);
            enemy->SetTag("Enemy");
            m_scene->AddActor(std::move(enemy));

            // create pickup
            auto* pickupModel = new Model{ GameData::shipPoints, Color{ 1, 0, 1 } };
            auto pickup = std::make_unique<Pickup>(Transform{ { randomf(0, g_engine.GetRenderer().GetWidth()), randomf(0, g_engine.GetRenderer().GetHeight()) }, 0, 4 }, pickupModel);
            pickup->SetDamping(1.0f);
            pickup->SetTag("Pickup");
            m_scene->AddActor(std::move(pickup));
        }
        break;
    case eState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::StartLevel;
        }
        break;
    case eState::GameOver:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0)
        {
            m_state = eState::Title;
        }
        break;
    default:
        break;
    }

    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
    switch (m_state)
    {
    case SpaceGame::eState::Title:
        // draw text "Game Title"
        m_textTitle->Create(renderer, "Shoot Stuff", Color{ 1, 0, 0, 1 });
        m_textTitle->Draw(renderer, 200, 200);
        break;
    case SpaceGame::eState::GameOver:
        // draw text "Game Over"
        m_textTitle->Create(renderer, "Game Over", Color{ 1, 0, 0, 1 });
        m_textTitle->Draw(renderer, 200, 200);
        break;
    default:
        break;
    }

    // draw score
    std::string text = "Score  " + std::to_string(m_score);
    m_textScore->Create(renderer, text, { 0, 1, 0, 1 });
    m_textScore->Draw(renderer, 20, 20);

    // draw lives
    text = "Lives  " + std::to_string(m_lives);
    m_textLives->Create(renderer, text, { 0, 1, 0, 1 });
    m_textLives->Draw(renderer, renderer.GetWidth() - 100, 20);

    m_scene->Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    m_lives--;
    m_state = (m_lives == 0) ? eState::GameOver : eState::PlayerDead;
    m_stateTimer = 3;
}
