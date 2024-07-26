#pragma once
#include "Vector2.h"
#include "Text.h"
#include "Transform.h"
#include "Color.h"
#include "Renderer.h"
#include <vector>

class Model
{
public:
	Model() = default;
	Model(const std::vector<Vector2>& points, const Color& color) :
		m_points{ points },
		m_color{ color }
	{}

	void Draw(Renderer& renderer, const Vector2& position, float angle, float scale);
	void Draw(Renderer& renderer, Transform transform);

	void SetColor(const Color& color) { m_color = color; }
	Color GetColor() { return m_color; }

	float GetRadius();

private:
	std::vector<Vector2> m_points;
	Text m_text;
	Color m_color;
};