#include "GameData.h"

namespace GameData
{
	const std::vector<Vector2> shipPoints
	{
		{  5,  0 },
		{ -5, -5 },
		{ -5,  5 },
		{  5,  0 }
	};

	const std::vector<Vector2> asteroidPoints
	{
		{ 0, -12 },
		{ 3, -9 },
		{ 9, -6 },
		{ 12, 3 },
		{ 9, 6 },
		{ 6, 12 },
		{ 3, 9 },
		{ -3, 12 },
		{ -9, 3 },
		{ -6, 0 },
		{ -9, -6 },
		{ -6, -9 },
		{ 0, -12 }
	};

	const std::vector<Vector2> smallAsteroidPoints
	{
		{ 2, -3 },
		{ 5, -4 },
		{ 6, 0 },
		{ 4, 6 },
		{ 1, 3 },
		{ -2, 4 },
		{ -6, -2 },
		{ -2, -5 },
		{ 2, -3 }
	};

	const std::vector<Vector2> pickupPoints
	{
		{ 0, -3 },
		{ 3, 1 },
		{ 1, 1 },
		{ 1, 3 },
		{ -1, 3 },
		{ -1, 1 },
		{ -3, 1 },
		{ 0, -3 }
	};
}
