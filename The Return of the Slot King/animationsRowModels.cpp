#include "animationsRowModels.hpp"

animationRows player =
{			
			0, //walk
			2, //idle
			4, //jumping
			6, //fall
			0, //death
			0, //attack
};

animationRows golBat = 
{			0,	//walk
			0,	//idle
			0,	//jump
			0,	//fall
			2,	//death
			1,	//attack
};

animationRows wheel = 
{			0,	//walk
			0,	//idle
			0,	//jump
			0,	//fall
			2,	//death
			0,	//attack
};

animationRows gormiti =
{			0,	//walk
			0,	//idle
			0,	//jump
			0,	//fall
			2,	//death
			0,	//attack
};

unsigned char getAnimationIndex(int requestingSprite, int animationRequested) //dopo cambia nome dei parametri e tipo
{

	//1 = golbat
	//2 = wheel
	//3 = gormiti
	switch (requestingSprite)
	{
	case PLAYER:
		switch (animationRequested)
		{
		case 1:
			return player.walking_animation;
			break;
		case 2:
			return player.idle_animation;
			break;
		case 3:
			return player.jumping_animation;
			break;
		case 4:
			return player.falling_animation;
			break;
		case 5:
			return player.death_animation;
			break;
		case 6:
			return player.attack_animation;
			break;
		}
		break;



	case GOLBAT:
		switch (animationRequested)
		{
		case 1:
			return golBat.walking_animation;
			break;
		case 2:
			return golBat.idle_animation;
			break;
		case 3:
			return golBat.jumping_animation;
			break;
		case 4:
			return golBat.falling_animation;
			break;
		case 5:
			return golBat.death_animation;
			break;
		case 6:
			return golBat.attack_animation;
			break;
		}
		break;



	case WHEEL:
		switch (animationRequested)
		{
		case 1:
			return wheel.walking_animation;
			break;
		case 2:
			return wheel.idle_animation;
			break;
		case 3:
			return wheel.jumping_animation;
			break;
		case 4:
			return wheel.falling_animation;
			break;
		case 5:
			return wheel.death_animation;
			break;
		case 6:
			return wheel.attack_animation;
			break;
		}
		break;




	case GORMITI:
		switch (animationRequested)
		{
		case 1:
			return gormiti.walking_animation;
			break;
		case 2:
			return gormiti.idle_animation;
			break;
		case 3:
			return gormiti.jumping_animation;
			break;
		case 4:
			return gormiti.falling_animation;
			break;
		case 5:
			return gormiti.death_animation;
			break;
		case 6:
			return gormiti.attack_animation;
			break;
		}
		break;
	}
}