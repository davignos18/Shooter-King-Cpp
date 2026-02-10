#pragma once
#include "raylib.h"

struct animations
{
	//animazioni
	Rectangle currentFrameSize;		//Dimensione selezione frame nel png della Texture
	int currentFrameIndex = 0;		//Index frame corrente
	int totalFrameNumber;			//Numero totale di frame dell'animazione
	int frameCounter = 0;			//Contatore frame
	int frameCounterDeath = 0;		//Contatore frame morte
	Vector2 textureFramePos;		//Posizione dove andare a disegnare il frame
	int totalFrameRow = 0;			//Numero totale di righe (animazioni) nella texture
	int currentFrameRow = 0;		//Riga corrente della texture (0, 1, 2, 3)


};