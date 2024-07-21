#pragma once
#include "Renderer.h"
#include <iostream>

class Font
{
public:
	Font() = default;
	~Font();

	bool Load(const std::string& name, int fontSize);

private:
	_TTF_Font* m_ttfFont{ nullptr };

	friend class Text;
};