#include "Engine.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Font.h"
#include "Text.h"

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	SpaceGame* game = new SpaceGame(&g_engine);
	game->Initialize();

	Font* font = new Font();
	font->Load("arcadeclassic.ttf", 20);

	g_engine.GetAudioBG().AddSound("stardust.mp3");
	g_engine.GetAudioSFX().AddSound("game_over.wav");
	g_engine.GetAudioSFX().AddSound("power_up.wav");
	g_engine.GetAudioSFX().AddSound("shoot.mp3");
	g_engine.GetAudioSFX().AddSound("game_start.mp3");

	//Text* text = new Text(font);
	//text->Create(g_engine.GetRenderer(), "Hello World", Color{ 1, 1, 1, 1 });

	while (!g_engine.IsQuit())
	{
		g_engine.Update();
		game->Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		game->Draw(g_engine.GetRenderer());
		g_engine.GetPS().Draw(g_engine.GetRenderer());
		//text->Draw(g_engine.GetRenderer(), 40, 40);

		g_engine.GetRenderer().EndFrame();
	}

	g_engine.Shutdown();

	return 0;
}

/*
	// add audio sounds
	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("snare.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");

	std::vector<Particle> particles;
	float offset = 0;

	// actor
	Model* model = new Model{ GameData::shipPoints, Color{ 1, 1, 1 } };
	Scene* scene = new Scene();

	Transform transform{ Vector2{ 400, 300 }, 0, 3 };
	Player* player = new Player( randomf( 300, 400 ), transform, model);
	player->SetDamping(2.0f);
	player->SetTag("Player");
	scene->AddActor(player);

	auto* enemyModel = new Model{ GameData::shipPoints, Color{ 1, 1, 0 } };
	auto* enemy = new Enemy(100, Transform{ { randomf(0, g_engine.GetRenderer().GetWidth()), randomf(0, g_engine.GetRenderer().GetHeight()) }, 0, 4 }, enemyModel);
	enemy->SetDamping(1.0f);
	enemy->SetTag("Enemy");
	scene->AddActor(enemy);

	float spawnTimer = 3000;

	// 0001 = 1
	// 0010 = 2
	// 0100 = 4
	// 1000 = 8
	// 1000 >> 1 = 0100

	Vector2 position{ 400, 300 };
	float rotation = 0;

	// asteroid points
	std::vector<Vector2> asteroid;
	asteroid.push_back(Vector2{ 0, -12 });
	asteroid.push_back(Vector2{ 3, -9 });
	asteroid.push_back(Vector2{ 9, -6 });
	asteroid.push_back(Vector2{ 12, 3 });
	asteroid.push_back(Vector2{ 9, 6 });
	asteroid.push_back(Vector2{ 6, 12 });
	asteroid.push_back(Vector2{ 3, 9 });
	asteroid.push_back(Vector2{ -3, 12 });
	asteroid.push_back(Vector2{ -9, 3 });
	asteroid.push_back(Vector2{ -6, 0 });
	asteroid.push_back(Vector2{ -9, -6 });
	asteroid.push_back(Vector2{ -6, -9 });
	asteroid.push_back(Vector2{ 0, -12 });
	Model asteroidModel{ asteroid, Color{ 1, 1, 1 } };


	// main loop
	while (!g_engine.IsQuit())
	{
		g_engine.Update();

		// spawn timer
		spawnTimer -= 1;
		if (spawnTimer <= 0)
		{
			auto* enemy = new Enemy(100, Transform{ { randomf(0, g_engine.GetRenderer().GetWidth()), randomf(0, g_engine.GetRenderer().GetHeight()) }, 0, 4 }, enemyModel);
			enemy->SetDamping(1.0f);
			enemy->SetTag("Enemy");
			scene->AddActor(enemy);
			spawnTimer = 3000;
		}

		// UPDATE
		scene->Update(g_engine.GetTime().GetDeltaTime());

		// update audio
		g_engine.GetAudio().Update();

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_Q)) g_engine.GetAudio().PlaySound("bass.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_W)) g_engine.GetAudio().PlaySound("snare.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_E)) g_engine.GetAudio().PlaySound("cowbell.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_A)) g_engine.GetAudio().PlaySound("clap.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_S)) g_engine.GetAudio().PlaySound("open-hat.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_D) && !g_engine.GetInput().GetPreviousKeyDown(SDL_SCANCODE_D)) g_engine.GetAudio().PlaySound("close-hat.wav");
		
		// update particles
		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
		if (g_engine.GetInput().GetMouseButtonDown(0))
		{
			for (int i = 0; i < 300; i++)
			{
				particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(10, 200), (float)random(1, 5000),
					(uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256) });
			}
		}

		for (Particle& particle : particles)
		{
			particle.Update(g_engine.GetTime().GetDeltaTime());

			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;

			particle.lifespan -= 1;
		}

		// DRAW
		// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		g_engine.GetRenderer().SetColor(255, 255, 255, 0);


		float radius = 200;
		offset += (90 * g_engine.GetTime().GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 120)
		{
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.01f) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Cos((offset + angle) * 0.01f) * radius;

			//g_engine.GetRenderer().DrawRect(400 + x, 300 + y, 4.0f, 4.0f);
		}

		// draw particles
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		for (Particle particle : particles)
		{
			particle.Draw(g_engine.GetRenderer());
		}

		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		scene->Draw(g_engine.GetRenderer());
		//asteroidModel.Draw(*g_engine.GetRenderer(), transform);

		// show screen
		g_engine.GetRenderer().EndFrame();
	}


	return 0;
}
*/