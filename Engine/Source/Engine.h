#pragma once

#include "Renderer.h"
#include "Audio.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtil.h"
#include "Model.h"
#include "Transform.h"
#include "ParticleSystem.h"

#include <fmod.hpp>
#include <SDL.h>

//#define RENDERER g_engine.GetRenderer()

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	ParticleSystem& GetPS() { return *m_particleSystem; }

	Time& GetTime() { return *m_time; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::shared_ptr<Time> m_time;

	std::shared_ptr<Renderer> m_renderer;
	std::shared_ptr<Input> m_input;
	std::shared_ptr<Audio> m_audio;

	std::unique_ptr<ParticleSystem> m_particleSystem;

	//static Engine ms_engine;
};

extern Engine g_engine;


