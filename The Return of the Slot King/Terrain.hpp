#pragma once
#include "raylib.h"

struct Terrain
{
	Terrain(const char*, int, int, Rectangle, Color);
	Terrain();

	Texture2D texture;
	Rectangle tile;
	Color color;
};