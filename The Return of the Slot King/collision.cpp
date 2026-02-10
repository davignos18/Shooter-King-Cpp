#include "collision.hpp"
#include "Terrain.hpp"
#include <iostream>


//Passa come parametro il deltaY.
//Passa playerHB per riferimento


bool isPlayerOnGround(Rectangle playerHB, Rectangle ground,Terrain groundTiles[], int size, int deltaY)
{
	Vector2 feetHitboxStartL;
	feetHitboxStartL.x = playerHB.x;
	feetHitboxStartL.y = playerHB.y;
	Vector2 feetHitboxEndL;
	feetHitboxEndL.x = playerHB.x;
	feetHitboxEndL.y = playerHB.y + deltaY;

	Vector2 feetHitboxStartR;
	feetHitboxStartR.x = playerHB.x + playerHB.width;
	feetHitboxStartR.y = playerHB.y;
	Vector2 feetHitboxEndR;
	feetHitboxEndR.x = playerHB.x + playerHB.width;
	feetHitboxEndR.y = playerHB.y + deltaY;



	Vector2 groundHitboxStart;
	Vector2 groundHitboxEnd;







	if (CheckCollisionRecs(playerHB,ground))
		return true;

	for (int i = 0; i < size; i++)
	{
		groundHitboxStart.x = groundTiles[i].tile.x;
		groundHitboxStart.y = groundTiles[i].tile.y;

		groundHitboxEnd.x = groundTiles[i].tile.x + groundTiles[i].tile.width;
		groundHitboxEnd.y = groundTiles[i].tile.y;
		
		if (CheckCollisionLines(feetHitboxStartL, feetHitboxEndL, groundHitboxStart, groundHitboxEnd, NULL) || CheckCollisionLines(feetHitboxStartR, feetHitboxEndR, groundHitboxStart, groundHitboxEnd, NULL))
			return true;
		
	}
	return false;
}



