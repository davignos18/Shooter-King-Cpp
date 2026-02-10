#include "raylib.h"

#include <iostream>
#include <ctime>


#include "animationsRowModels.hpp"
#include "Sprite.hpp"
#include "Player.hpp"
#include "collision.hpp"
#include "Enemy.hpp"
#include "Terrain.hpp"



//cambiare funzione update per nemici
// fare attacco melee e sistemare sparo con tempo di ricarica e sparo con tasto destro
//BOSS PRIME MONKEY

void loadEnemy(Enemy e[], Enemy modello,int healthPoints)
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        e[i] = modello;
        e[i].setEnemy(healthPoints);
    }
}


void setSpawn(Enemy e[], int i, int enemyType)
{
    switch (enemyType)
    {
    case 1:
        e[i].hitbox.x = rand() % GetScreenWidth();
        e[i].hitbox.y = rand() % GetScreenHeight() / 5;
        break;
    case 2:
        e[i].hitbox.x = rand() % GetScreenWidth();
        e[i].hitbox.y = GetScreenHeight() - 79 - e[i].hitbox.height;
        break;
    case 3:
        e[i].hitbox.x = rand() % GetScreenWidth();
        e[i].hitbox.y = 50;
        break;
    default:
        ;
    }

}

int main(void)
{

    srand(time(NULL));

    //Inizializzazione Finestra
    const int screenWidth = 1200;
    const int screenHeight = 960;
    
    InitWindow(screenWidth, screenHeight, "The Return of the Slot King");
    SetTargetFPS(60);
    int ground_Y = GetScreenHeight() - 79;

    //Dimensione scritte su schermo
    int fontSize = 40;
    
    //Giocatore
    Player player("..\\images\\animations\\player.png",1024,1024,93,120, GetScreenWidth() / 2,50,8,8);     
    player.movementSpeed = 400.f;
    
    //Sfondo
    Texture2D background;
    background = LoadTexture("..\\images\\background.png");



    //INIZIALIZZAZIONE TERRAIN
    Rectangle groundHB;
    groundHB.height = 50;
    groundHB.width = GetScreenWidth();
    groundHB.x = 0;
    groundHB.y = ground_Y;
    const int NUMBER_OF_TILES = 5;
    //Texture2D terrainTexture = LoadTexture("..\\images\\tiles.png");
    Terrain groundTiles[NUMBER_OF_TILES];
    groundTiles[0] = { "..\\images\\tiles.png", 216, 24, { 50, 650, 216, 10}, RAYWHITE};       //LD
    groundTiles[1] = { "..\\images\\tiles.png", 216, 24, { 850, 650, 210, 10}, RAYWHITE };     //RD
    groundTiles[2] = { "..\\images\\tiles.png", 216, 24, {(float)(GetScreenWidth() / 2 - 216 / 2), (float)(GetScreenHeight() / 2 - 24), 216, 10}, RAYWHITE };
    groundTiles[3] = { "..\\images\\tiles.png", 216, 24, { 50, 250, 216, 10}, RAYWHITE };      //LU
    groundTiles[4] = { "..\\images\\tiles.png", 216, 24, { 850, 250, 216, 10}, RAYWHITE };     //RU



    //INIZIALIZZAZIONE NEMICI
    Enemy totalGolbat[MAX_ENEMIES];
    Enemy* golbatModel = new Enemy;
    *golbatModel = { "..\\images\\animations\\enemy1.png", 448, 192, 64, 64, 100, 500, 7, 4 };
    golbatModel->movementSpeed = 550.f;
    loadEnemy(totalGolbat, *golbatModel,20);
    delete golbatModel;

    Enemy totalWheels[MAX_ENEMIES];
    Enemy* wheelsModel = new Enemy;
    *wheelsModel = { "..\\images\\animations\\enemy3.png", 1024, 384, 128, 128, 200, ground_Y - 256, 8, 3 };
    wheelsModel->movementSpeed = 350.f;
    loadEnemy(totalWheels, *wheelsModel, 30);
    delete wheelsModel;

    Enemy totalGormiti[MAX_ENEMIES];
    Enemy* gormitiModel = new Enemy;
    *gormitiModel = { "..\\images\\animations\\enemy2.png",1024,384,128,128,200, ground_Y - 128, 8, 3 };
    gormitiModel->movementSpeed = 250.f;
    loadEnemy(totalGormiti, *gormitiModel,40);
    delete gormitiModel;



    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (totalGolbat[i].isAlive)
            setSpawn(totalGolbat, i,1);
        if (totalGormiti[i].isAlive)
            setSpawn(totalGormiti, i,2);
        if (totalWheels[i].isAlive)
            setSpawn(totalWheels, i,3);
    }


    std::cout << "COMINCIO TEST" << std::endl;

    while (!WindowShouldClose())
    {
        
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        //AGGIORNA / MUOVI NEMICI
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (totalGolbat[i].isAlive)
                totalGolbat[i].golbatAI();
            else if(totalGolbat[i].animation.currentFrameIndex == totalGolbat[i].animation.totalFrameNumber - 1)
                totalGolbat[i].deleteEnemy();


            if (totalGormiti[i].isAlive)
                totalGormiti[i].update();
            else if (totalGormiti[i].animation.currentFrameIndex == totalGormiti[i].animation.totalFrameNumber - 1)
                totalGormiti[i].deleteEnemy();


            if (totalWheels[i].isAlive)
                totalWheels[i].wheelAI(groundHB, groundTiles, NUMBER_OF_TILES);
            else if (totalWheels[i].animation.currentFrameIndex == totalWheels[i].animation.totalFrameNumber-1)
                totalWheels[i].deleteEnemy();

        }

        
        //Aggiornamenti player
        player.updatePosition(groundHB,groundTiles,NUMBER_OF_TILES);
        player.updateHealth();



        //STAMPA A VIDEO
        BeginDrawing();

        ClearBackground(WHITE);
        DrawTexture(background, 0, 0, WHITE);

        //STAMPA PIATTAFORME
        for (int i = 0; i < NUMBER_OF_TILES; i++)
            DrawTexture(groundTiles[i].texture,groundTiles[i].tile.x,groundTiles[i].tile.y,groundTiles[i].color);


        //STAMPA NEMICI
        for (int i = 0;i < MAX_ENEMIES;i++) {
            if (totalGolbat[i].isAlive)
                totalGolbat[i].drawFrame();
            else if(!totalGolbat[i].seMurt)
                totalGolbat[i].seMurt = totalGolbat[i].drawDeathFrame(getAnimationIndex(GOLBAT,5));

            if(totalGormiti[i].isAlive)
               totalGormiti[i].drawFrame();
            else if(!totalGormiti[i].seMurt)
                totalGormiti[i].seMurt = totalGormiti[i].drawDeathFrame(getAnimationIndex(WHEEL,5));

            if (totalWheels[i].isAlive)
                totalWheels[i].drawFrame();
            else if (!totalWheels[i].seMurt)
                totalWheels[i].seMurt = totalWheels[i].drawDeathFrame(getAnimationIndex(GORMITI,5));
        }


        //STAMPA PLAYER
        player.drawHealthBar();
        player.drawFrame();

        //STAMPA PROIETTILE
        if (player.isShooting) {
            player.hasHitSomething(totalGolbat);
            player.hasHitSomething(totalGormiti);
            player.hasHitSomething(totalWheels);
            player.bullet.drawFrame();
            //player.bullet.showHB();
        }


       



        //player.showHB();
        EndDrawing();
    }

    CloseWindow();        

    return 0;
}
