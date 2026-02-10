#include "Enemy.hpp"
#include "math.h"
#include <iostream>

void Enemy::update()
{
	if (hitbox.x + movementSpeed * GetFrameTime() <= 0 || hitbox.x + movementSpeed * GetFrameTime() >= GetScreenWidth() - hitbox.width)
	{
		movementSpeed *= -1;

		if (facingRight)
			facingRight = false;
		else
			facingRight = true;
	}

	hitbox.x += movementSpeed * GetFrameTime();

}

void Enemy::wheelAI(Rectangle ground, Terrain grounds[],int size) {
	
	if (CheckCollisionRecs(hitbox, ground))
		inAir = false;
	else
	{
		for (int i = 0; i < size;i++)
		{

			if (CheckCollisionRecs(hitbox, grounds[i].tile)) {
				inAir = false;
				gravity = 0.0f;
			}
			else
				inAir = true;

		}
	}

		if(inAir)
		{
			deltaY = jumpSpeed * GetFrameTime() * gravity;
			hitbox.y += deltaY;				
			gravity += deltaGravity;
		}
			
		if (hitbox.x + movementSpeed * GetFrameTime() <= 0 || hitbox.x + movementSpeed * GetFrameTime() >= GetScreenWidth() - hitbox.width)
		{
			movementSpeed *= -1;

			if (facingRight)
				facingRight = false;
			else
				facingRight = true;
		}


		hitbox.x += movementSpeed * GetFrameTime();
	
}


void Enemy::golbatAI() {
	previousPointY = circlePointY;


	if (circlePointX >= radius * 2)
		circlePointX = 0;


	circlePointY = sqrt(radius * radius - ((circlePointX - radius) * (circlePointX - radius)));
	if (temp > radius * 2 && temp < radius * 4)
		circlePointY *= -1;
	else if (temp >= radius * 4)
		temp = 0;

	temp++;

	if (hitbox.x + movementSpeed * GetFrameTime() <= 0 || hitbox.x + movementSpeed * GetFrameTime() >= GetScreenWidth() - hitbox.width)
		movementSpeed *= -1;

	hitbox.x += movementSpeed * GetFrameTime();
	hitbox.y +=   previousPointY- circlePointY;

	circlePointX++;
}














//
void Enemy::setEnemy(int maxH) {
	totalHealthPoints = maxH;
	currentHealthPoints = maxH;
}

void Enemy::deleteEnemy() {
	hitbox.x = -500;
	hitbox.y = -500;
}



