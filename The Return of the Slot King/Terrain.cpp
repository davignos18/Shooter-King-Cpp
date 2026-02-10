#include "Terrain.hpp"

Terrain::Terrain(const char* filePath, int textureWidth, int textureHeight, Rectangle setTile, Color setColor)
{
	texture = LoadTexture(filePath);
	texture.height = textureHeight;
	texture.width = textureWidth;
	tile = setTile;
	color = setColor;
}
Terrain::Terrain() {}