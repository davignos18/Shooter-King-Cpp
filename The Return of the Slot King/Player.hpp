#pragma once
#include "raylib.h"
#include "Sprite.hpp"
#include "collision.hpp"
#include "Enemy.hpp"
#include <chrono>			//Libreria che gestisce il tempo,timer
#include "animationsRowModels.hpp"

class Player : public Sprite
{
public:
	using Sprite::Sprite;

	
	bool isJumping = false;
	bool isShooting = false;
	bool hasMoved = false;





	Projectile bullet = { "..\\images\\animations\\cardThrow.png", 256, 32, 32, 32, 0, 0, 8, 1 };
	
	static const int HEALTHBAR_TEXTURE_LAYERS = 3;
	Texture2D healthBarTextures[HEALTHBAR_TEXTURE_LAYERS] = { LoadTexture("..\\images\\UI\\Layer1HealthBar.png"),LoadTexture("..\\images\\UI\\Layer2HealthBar.png"),LoadTexture("..\\images\\UI\\Layer3HealthBar.png") };
	Rectangle healthBarTextureFrame = {0,0,330,94};
	Vector2 healthBarPos = { 30,30 };





	void updatePosition(Rectangle, Terrain[], int);
	
	void updateHealth();

	void drawHealthBar();

	void hasHitSomething(Enemy enemies[]);
};