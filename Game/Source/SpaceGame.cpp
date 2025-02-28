#include "SpaceGame.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "GameData.h"
#include "Asteroid.h"
#include "Font.h"
#include "Text.h"
#include "Pickup.h"
#include "Shield.h"
#include "Audio.h"

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
        g_engine.GetAudioSFX().PlaySound("game_start.mp3");

        m_score = 0;
        m_lives = 3;

        m_state = eState::StartLevel;
        break;
    case eState::StartLevel:
        m_scene->RemoveAll();
        {
            Transform transform{ Vector2{ 400, 300 }, 0, 3 };
            Model* model = new Model{ GameData::shipPoints, Color{ 1, 1, 0 } };
            auto player = std::make_unique<Player>(randomf(300, 400), transform, model);
            player->SetDamping(2.0f);
            player->SetTag("Player");
            m_scene->AddActor(std::move(player));
        }
        
        m_spawnTime = 3;
        m_spawnTimer = m_spawnTime;
        m_pickupTimer = 5;
        m_shieldTimer = 3;
        
        m_state = eState::Game;
        break;
    case eState::Game:
        if (!g_engine.GetAudioBG().isSoundPlaying())
        {
            g_engine.GetAudioBG().PlaySound("stardust.mp3");
        }

        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0)
        {
            if (m_spawnTime > 1) m_spawnTime -= 0.1f;
            m_spawnTimer = m_spawnTime;

            int side = random(1, 4);
            int x = 0, y = 0;
            switch (side)
            {
            case 1: // top side
                x = randomf(0, g_engine.GetRenderer().GetWidth());
                y = 0;
                break;
            case 2: // bottom side
                x = randomf(0, g_engine.GetRenderer().GetWidth());
                y = g_engine.GetRenderer().GetHeight();
                break;
            case 3: // left side
                x = 0;
                y = randomf(0, g_engine.GetRenderer().GetHeight());
                break;
            case 4: // right side
                x = g_engine.GetRenderer().GetWidth();
                y = randomf(0, g_engine.GetRenderer().GetHeight());
                break;
            default:
                break;
            }

            // create asteroid
            auto* asteroidModel = new Model{ GameData::asteroidPoints, Color{ 1, 1, 1 } };
            auto asteroid = std::make_unique<Asteroid>(100, Transform{ { x, y }, 0, 4 }, asteroidModel);
            asteroid->SetDamping(1.0f);
            asteroid->SetTag("Asteroid");
            m_scene->AddActor(std::move(asteroid));
        }

        m_pickupTimer -= dt;
        if (m_pickupTimer <= 0) 
        {
            m_pickupTimer = 45;

            // create pickup
            auto* pickupModel = new Model{ GameData::pickupPoints, Color{ 1, 0, 1 } };
            auto pickup = std::make_unique<Pickup>(Transform{ { randomf(0, g_engine.GetRenderer().GetWidth()), randomf(0, g_engine.GetRenderer().GetHeight()) }, 0, 4 }, pickupModel);
            pickup->SetDamping(1.0f);
            pickup->SetTag("Pickup");
            m_scene->AddActor(std::move(pickup));
        }

        m_shieldTimer -= dt;
        if (m_shieldTimer <= 0)
        {
            m_shieldTimer = 60;

            // create shield
            auto* pickupModel = new Model{ GameData::pickupPoints, Color{ 0, 0, 1 } };
            auto shield = std::make_unique<Shield>(Transform{ { randomf(0, g_engine.GetRenderer().GetWidth()), randomf(0, g_engine.GetRenderer().GetHeight()) }, 0, 4 }, pickupModel);
            shield->SetDamping(1.0f);
            shield->SetTag("Shield");
            m_scene->AddActor(std::move(shield));
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
        m_textTitle->Create(renderer, "Asteroid", Color{ 0.5, 0.75, 1, 1 });
        m_textTitle->Draw(renderer, 250, 225);
        m_textTitle->Create(renderer, "Blaster", Color{ 0.5, 0.75, 1, 0 });
        m_textTitle->Draw(renderer, 270, 275);
        break;
    case SpaceGame::eState::GameOver:
        // draw text "Game Over"
        m_textTitle->Create(renderer, "GAME  OVER", Color{ 1, 0, 0, 1 });
        m_textTitle->Draw(renderer, 250, 250);
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
    if (m_lives == 0) {
        g_engine.GetAudioBG().StopSound();
        m_state = eState::GameOver;
        g_engine.GetAudioSFX().PlaySound("game_over.wav");
    }
    else {
        m_state = eState::PlayerDead;
    }
    m_stateTimer = 5;
}
