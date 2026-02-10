#include "Sprite.hpp"
#include <iostream>

//filePath, height, width, HBheight, HBwidth, xPos, yPos, totalNumOfFrames, totalNumOfRow
Sprite::Sprite(const char* filePath, int width, int height,int HBwidth, int HBheight, int xPos,int yPos,int totalFrame, int totalFrameRows)
{
	//Carico texture
	texture = LoadTexture(filePath);
	texture.width = width;
	texture.height = height;

	//Creo dimensione hitbox
	hitbox.width = HBwidth;
	hitbox.height = HBheight;

	feetHitbox.width = hitbox.width;
	feetHitbox.height = 5;

	//Relativo poi cambialo
	hitbox.x = xPos;
	hitbox.y = yPos;


	animation.totalFrameNumber = totalFrame;
	animation.totalFrameRow = totalFrameRows;

	animation.currentFrameSize.height = texture.height / animation.totalFrameRow;
	animation.currentFrameSize.width = texture.width / totalFrame;
	animation.currentFrameSize.y = 0;
	animation.currentFrameSize.x = 0;

	animation.textureFramePos.x = xPos;
	animation.textureFramePos.y = yPos;
}
Sprite::Sprite()
{

}

void Sprite::drawSprite()
{
	DrawTexture(texture,hitbox.x,hitbox.y,WHITE);
}

void Sprite::showHB() 
{
	DrawRectangleRec(hitbox, RED);
}

void Sprite::drawFrame()
{

	float correctCurrentFrameRow = animation.currentFrameRow;
	if (!facingRight)
		correctCurrentFrameRow++;


	animation.frameCounter++;

	animation.textureFramePos.x = hitbox.x;
	animation.textureFramePos.y = hitbox.y;

	//Ogni 60FPS l'animazione completa viene eseguita 1 volta. Controlla ogni
	//quanti frame deve cambiare frame dell'animazione.
	//x es. animazione da 6 frame. Si cambia frame ogni 60/6=10 frame.

	animation.currentFrameSize.y = (texture.height / animation.totalFrameRow) * correctCurrentFrameRow;

	if (animation.frameCounter >= 60 / animation.totalFrameNumber)
	{
		animation.frameCounter = 1;
		animation.currentFrameIndex++;	//Aumento l'indice del frame da disegnare
		if (animation.currentFrameIndex > animation.totalFrameNumber - 1)	//Se finisco l'animazione ricomincio dal primo frame
			animation.currentFrameIndex = 0;

		//Aggiorno la texture del nuovo frame
		animation.currentFrameSize.x = (texture.width / animation.totalFrameNumber) * animation.currentFrameIndex;
	}

	//Disegno il frame
	DrawTextureRec(texture, animation.currentFrameSize, animation.textureFramePos, WHITE);
}

bool Sprite::drawDeathFrame(unsigned char newRowIndex) 
{
	if (animation.currentFrameIndex == animation.totalFrameNumber)
		return true;

	animation.currentFrameRow = newRowIndex;

	animation.frameCounterDeath++;

	animation.textureFramePos.x = hitbox.x;
	animation.textureFramePos.y = hitbox.y;

	animation.currentFrameSize.y = (texture.height / animation.totalFrameRow) * animation.currentFrameRow;

	if (animation.frameCounterDeath >= 60 / animation.totalFrameNumber)
	{

		animation.frameCounterDeath = 0;
		animation.currentFrameIndex++;	//Aumento l'indice del frame da disegnare
		if (animation.currentFrameIndex > animation.totalFrameNumber)	//Se finisco l'animazione ricomincio dal primo frame
			animation.currentFrameIndex = 0;

		//Aggiorno la texture del nuovo frame
		animation.currentFrameSize.x = (texture.width / animation.totalFrameNumber) * animation.currentFrameIndex;

	}

	//Disegno il frame
	if(animation.currentFrameIndex < animation.totalFrameNumber)
		DrawTextureRec(texture, animation.currentFrameSize, animation.textureFramePos, WHITE);


	return false;
	
}




void Projectile::setBullet()
{
	bulletStartingPoint.x = hitbox.x + hitbox.width / 2;
	bulletStartingPoint.y = hitbox.y + hitbox.height / 2;

	bulletEndPoint = GetMousePosition();

	float vx = bulletEndPoint.x - bulletStartingPoint.x;
	float vy = bulletEndPoint.y - bulletStartingPoint.y;
	float dist = sqrt(vx * vx + vy * vy); //100 = bullet speed
	dx = vx / dist;
	dy = vy / dist;
	dx *= 650;
	dy *= 650;


	finito = std::chrono::system_clock::now() + std::chrono::seconds(bulletTimeTravel);
}

//funzione che sposto ogni frame il proiettile, cancellandolo se passa troppo tempo sullo schermo
void Projectile::updateBullet(bool& isShooting)
{
	if (isShooting)
	{
		std::chrono::system_clock::time_point pointTime = std::chrono::system_clock::now();

		if (pointTime < finito && hitbox.x < GetScreenWidth() && hitbox.x > 0 && hitbox.y > 0 && hitbox.y < GetScreenHeight())
		{
			hitbox.x += dx * GetFrameTime();
			hitbox.y += dy * GetFrameTime();
		}
		else
			isShooting = false;

	}

}