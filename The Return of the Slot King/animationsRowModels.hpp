#pragma once

//Entità esistenti
#define PLAYER 1
#define GOLBAT 2
#define WHEEL 3
#define GORMITI 4

struct animationRows
{
	unsigned char walking_animation;
	unsigned char idle_animation;
	unsigned char jumping_animation;
	unsigned char falling_animation;
	unsigned char death_animation;
	unsigned char attack_animation;

};

//WALK (1) -- IDLE (2) -- JUMP (3) -- FALL (4) -- DEATH (5) -- ATTACK (6)
unsigned char getAnimationIndex(int requestingSprite, int animationRequested); //dopo cambia nome dei parametri e tipo
