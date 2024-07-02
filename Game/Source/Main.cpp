#include "Renderer.h"
#include "Vector2.h"

#include <SDL.h>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include "Input.h"

int main(int argc, char* argv[])
{
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;

	Vector2 v1{ 400, 300 };
	Vector2 v2{ 700, 500 };

	std::vector<Vector2> points;
	/*for (int i = 0; i < 100; i++)
	{
		points.push_back(Vector2{rand() % 800, rand() % 600});
	}*/

	bool quit = false;
	while (!quit)
	{
		// input
		// update
		// draw

		// INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		//std::cout << mousePosition.x << " " << mousePosition.y << std::endl;

		if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0))
		{
			std::cout << "mouse pressed\n";
			points.push_back(mousePosition);
		}

		if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0))
		{
			float distance = (points.back() - mousePosition).Length();
			if (distance > 5) points.push_back(mousePosition);
		}

		/*Vector2 speed{ 0.1f, -0.1f };
		for (Vector2& point : points)
		{
			point = point + 0.002f;
		}*/


		// DRAW
		// clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.SetColor(255, 255, 255, 0);
		// draw triangles
		/*renderer.SetColor(255, 0, 0, 0);
		renderer.DrawLine(200, 450, 600, 450);
		renderer.SetColor(0, 255, 0, 0);
		renderer.DrawLine(600, 450, 400, 150);
		renderer.SetColor(0, 0, 255, 0);
		renderer.DrawLine(400, 150, 200, 450);
		
		renderer.SetColor(255, 0, 255, 0);
		renderer.DrawLine(300, 300, 400, 450);
		renderer.SetColor(255, 255, 0, 0);
		renderer.DrawLine(400, 450, 500, 300);
		renderer.SetColor(0, 255, 255, 0);
		renderer.DrawLine(500, 300, 300, 300);
		renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);*/

		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
		{
			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		}

		//for (int i = 0; i <= 100; i++) {
		//	renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, 0); // create random color
		//	renderer.DrawPoint(rand() % 800, rand() % 600); // draw a point in a random location
		//	renderer.DrawLine(rand() % 800, rand() % 600, rand() % 800, rand() % 600); // draw line between two random points
		//}

		// show screen
		renderer.EndFrame();
	}


	return 0;
}
