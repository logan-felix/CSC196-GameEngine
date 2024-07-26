#include "Engine.h"

//Engine Engine::ms_engine;
Engine g_engine;

bool Engine::Initialize()
{
    m_renderer = std::make_unique<Renderer>();
    m_input = std::make_unique<Input>();
    m_audioBg = std::make_unique<Audio>();
    m_audioSfx = std::make_unique<Audio>();

    m_renderer->Initialize();
    m_renderer->CreateWindow("Game Engine", 800, 600);
    m_input->Initialize();
    m_audioBg->Initialize();
    m_audioSfx->Initialize();

    m_time = std::make_unique<Time>();

    m_particleSystem = std::make_unique<ParticleSystem>();

    return true;
}

void Engine::Shutdown()
{
    m_renderer->Shutdown();
    m_input->Shutdown();
    m_audioBg->Shutdown();
    m_audioSfx->Shutdown();
}

void Engine::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        {
            quit = true;
        }
    }

    m_time->Tick();

    m_input->Update();
    m_audioBg->Update();
    m_audioSfx->Update();
    m_particleSystem->Update(m_time->GetDeltaTime());
}
