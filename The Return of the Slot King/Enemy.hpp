#pragma once
#include "Sprite.hpp"
#include "Terrain.hpp"
static const int MAX_ENEMIES = 3;
class Enemy : public Sprite
{
public:
	using Sprite::Sprite;

	

	float temp = 0;		//Serve a capire se abbiamo eseguito un giro completo del cerchio (raggio * 4 (avanti e indietro))
	float radius = 60;
	float circlePointX = 0;
	float circlePointY = 0;
	float previousPointY = 0;
	

	bool seMurt = false;		//serve per capire se il frame prima è stato ucciso il nemico e quindi non farlo di nuovo stampare


	void golbatAI();
	void update();
	void wheelAI(Rectangle,Terrain[],int);
	void setEnemy(int);
	void deleteEnemy();
};