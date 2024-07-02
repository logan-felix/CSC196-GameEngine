#pragma once
#include <SDL.h>
#include <string>

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();

	bool CreateWindow(std::string title, int width, int height);
	void BeginFrame();
	void EndFrame();

	void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void DrawLine(int x1, int y1, int x2, int y2);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawPoint(int x, int y);
	void DrawPoint(float x, float y);

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};