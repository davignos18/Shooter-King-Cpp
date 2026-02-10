#pragma once
#include "raylib.h"
#include "animations.hpp"
#include <chrono>




class Sprite
{
public:
	//filePath, height, width, HBheight, HBwidth, xPos, yPos, totalNumOfFrames, totalNumOfRow
	Sprite(const char*, int, int, int, int, int, int, int, int);
	Sprite();

	animations animation;
	
	bool isAlive = true;
	bool facingRight = true;

	int totalHealthPoints = 100;
	int currentHealthPoints = 100;


	Rectangle hitbox;
	Rectangle feetHitbox;
	Texture2D texture;

	float movementSpeed;

	bool inAir = true;
	float gravity = 0.f;			//Aggiunge effetto gravità al salto
	float deltaGravity = 0.035f;	//Variazione della gravità durante il salto (più si arriva in alto, meno veloci si salirà)
	float jumpSpeed = 1000;
	float deltaY = 0;

	//Variabili delta calcolate per lo spostamento dei proiettili
	float dx = 0;
	float dy = 0;





	//Disegna texture 1 frame
	void drawSprite();

	//Disegna frame dell'animazione
	void drawFrame();

	//unsigned char = newRowIndex
	bool drawDeathFrame(unsigned char);


	//Stampa hitbox dello Sprite
	void showHB();

	
};



class Projectile : public Sprite
{
public:
	using Sprite::Sprite;

	const int bulletTimeTravel = 2;

	Vector2 bulletStartingPoint;
	Vector2 bulletEndPoint;
	float bulletMovementX;
	float bulletMovementY;


	std::chrono::system_clock::time_point finito; //variabile che gestisce quando il colpo deve sparire


	void setBullet();
	void updateBullet(bool&);

};

