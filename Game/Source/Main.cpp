#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtil.h"
#include <fmod.hpp>

#include <SDL.h>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

int main(int argc, char* argv[])
{
	// create systems
	 
	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	// create renderer
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	// create input system
	Input input;
	input.Initialize();

	// create time system
	Time time;

	std::vector<Particle> particles;

	float offset = 0;

	FMOD::Sound* sound = nullptr;
	audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);

	audio->playSound(sound, 0, false, nullptr);

	std::vector<FMOD::Sound*> sounds;
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound); // 0
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound); // 1
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound); // 2
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound); // 3
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound); // 4
	sounds.push_back(sound);

	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound); // 5
	sounds.push_back(sound);



	bool quit = false;
	while (!quit)
	{
		time.Tick();
		std::cout << time.GetTime() << std::endl;

		// INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// UPDATE

		// update audio
		audio->update();

		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPreviousKeyDown(SDL_SCANCODE_Q))
		{
			audio->playSound(sounds[0], 0, false, nullptr); // bass
		}
		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPreviousKeyDown(SDL_SCANCODE_W))
		{
			audio->playSound(sounds[1], 0, false, nullptr); // snare
		}
		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPreviousKeyDown(SDL_SCANCODE_E))
		{
			audio->playSound(sounds[2], 0, false, nullptr); // cowbell
		}
		if (input.GetKeyDown(SDL_SCANCODE_A) && !input.GetPreviousKeyDown(SDL_SCANCODE_A))
		{
			audio->playSound(sounds[3], 0, false, nullptr); // clap
		}
		if (input.GetKeyDown(SDL_SCANCODE_S) && !input.GetPreviousKeyDown(SDL_SCANCODE_S))
		{
			audio->playSound(sounds[4], 0, false, nullptr); // open hat
		}
		if (input.GetKeyDown(SDL_SCANCODE_D) && !input.GetPreviousKeyDown(SDL_SCANCODE_D))
		{
			audio->playSound(sounds[5], 0, false, nullptr); // close hat
		}
		
		// update particles
		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonDown(0))
		{
			for (int i = 0; i < 300; i++)
			{
				particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(10, 200), (float)random(1, 5000),
					(uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256) });
			}
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;

			particle.lifespan -= 1;
		}

		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.SetColor(255, 255, 0, 0);
		float radius = 200;
		offset += (90 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 120)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.01f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos((offset + angle) * 0.01f) * radius;

			renderer.DrawRect(400 + x, 300 + y, 4.0f, 4.0f);
		}

		// draw particles
		renderer.SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(renderer);
		}

		// show screen
		renderer.EndFrame();
	}


	return 0;
}
