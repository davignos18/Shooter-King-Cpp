#include "Player.hpp"
#include <math.h>
#include <iostream>





void Player::updatePosition(Rectangle ground,Terrain groundTiles[], int size)
{
	//Sposta Hitbox piedi alla fine dell'hitbox totale
	feetHitbox.x = hitbox.x;
	feetHitbox.y = hitbox.y + hitbox.height - feetHitbox.height;


	//Se non sta sparando, posiziona il proiettile sotto all'hitbox del player
	if (!isShooting)
	{
		bullet.hitbox.x = hitbox.x + hitbox.width / 2;
		bullet.hitbox.y = hitbox.y + hitbox.height / 2;
	}


	if (hasMoved)
		hasMoved = false;
	else if (!inAir)
		animation.currentFrameRow = getAnimationIndex(PLAYER,2);     //idle_animation
	
	if (!isPlayerOnGround(feetHitbox,ground, groundTiles, size, deltaY))
		inAir = true;
	else
	{
		inAir = false;
		gravity = 0.0f;
	}

	//Jumping mechanic
	if ((IsKeyPressed(KEY_SPACE) && !inAir) || isJumping)
	{

		//controllo per sistemare velocit‡ di caduta dalle piattaforme
		if (gravity == 0.0f)
			gravity = 1.f;

		animation.currentFrameRow = getAnimationIndex(PLAYER, 3);	//jumping_animation
		isJumping = true;
		hitbox.y -= jumpSpeed * GetFrameTime() * gravity;
		gravity -= deltaGravity;
	}
	else if (inAir && !isJumping)
	{
		animation.currentFrameRow = getAnimationIndex(PLAYER, 4);	//falling_animation
		deltaY = jumpSpeed * GetFrameTime() * gravity;
		hitbox.y += deltaY;
		gravity += deltaGravity;
	}

	if (gravity <= 0)
	{
		isJumping = false;
	}
	

	//Movimento DX/SX
	if (IsKeyDown(KEY_A)) {
		float deltaX = movementSpeed * GetFrameTime();
		if (hitbox.x - deltaX <= 0)
			hitbox.x = 0;
		else
			hitbox.x -= deltaX;

		hasMoved = true;
		if(!inAir)
			animation.currentFrameRow = getAnimationIndex(PLAYER,1);
		facingRight = false;
	}
	if (IsKeyDown(KEY_D)) {
		float deltaX = movementSpeed * GetFrameTime();
		if (hitbox.x + deltaX >= GetScreenWidth()-hitbox.width)
			hitbox.x = GetScreenWidth() - hitbox.width;
		else
			hitbox.x += deltaX;
		hasMoved = true;
		if (!inAir)
			animation.currentFrameRow = getAnimationIndex(PLAYER,1);
		facingRight = true;
	}

	//Aggiorno la posizione del proiettile se necessario
	bullet.updateBullet(isShooting);


	//Controllo sparo proiettile
	if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
	{
		if (!isShooting)
		{
			isShooting = true;
			bullet.setBullet();
		}
	}
}






void Player::updateHealth()
{
	healthBarTextureFrame.width = totalHealthPoints / 100 * currentHealthPoints * 3;
	if (animation.frameCounter % 5 == 0)
		currentHealthPoints -= 10;
	//TEST FÏDO
	if (currentHealthPoints <= 0)
		currentHealthPoints = 100;
}

void Player::drawHealthBar()
{
	for (int i = 0; i < HEALTHBAR_TEXTURE_LAYERS; i++)
	{
		if (i == 1)
			DrawTextureRec(healthBarTextures[i], healthBarTextureFrame, healthBarPos, WHITE);
		else
			DrawTexture(healthBarTextures[i], healthBarPos.x, healthBarPos.y, WHITE);
	}
}


void Player::hasHitSomething(Enemy enemies[]) {
	for (int i = 0;i < MAX_ENEMIES;i++) {
		if (CheckCollisionRecs(bullet.hitbox, enemies[i].hitbox)) {
			isShooting = false;
			enemies[i].currentHealthPoints -= 50;
			if (enemies[i].currentHealthPoints <= 0)
			{
				enemies[i].isAlive = false;
				enemies[i].animation.currentFrameIndex = 0;
			}

			std::cout << enemies[i].currentHealthPoints << std::endl;

		}
	}
}