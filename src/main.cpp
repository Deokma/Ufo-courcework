#include <iostream>
#include "stdlib.h"
#include "../include/raylib.h"
#include "../headers/player.h"
#include "../headers/planet.h"
#include "../headers/meteor.h"
#include <time.h>
#include <cmath>
#include <string>

using namespace std;
void GameplayManager(float* speedPtr, float* speedTime, float* meteorTimer, std::vector<Meteor>* meteors, Player* player, int* meteorspeed,int* playerradius);
    int level;
    int radplan = 100;
    //float meteorspeed;
    int playerdistance = 260;
enum Scene
{
    Menu, Options, Game,Lose
};
enum pl{
    pl1, pl2
};

pl plc;

Music music;
int n;
// Сцена по умолчанию
Scene scene = Menu;

using namespace std;
int main(void)
{   
    float score;
    // Разрешение экрана
    const int screenWidth = 1366;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Ufo");
    Image favicon = LoadImage("data/images/ufologo.png");
    SetWindowIcon(favicon);
    SetTargetFPS(60);  
      
    Texture2D playert;
    playert = LoadTexture("data/images/player1.png");
    
    Player player({20, 20}, 1.0f, 10, 0,playert);
    Planet planet; 
    Texture2D ufologo = LoadTexture("data/images/ufologo.png");
    Texture2D player1t = LoadTexture("data/images/player1.png");
    Texture2D player2t = LoadTexture("data/images/player2.png");
    Texture2D player3t = LoadTexture("data/images/player3.png");
    Texture2D background = LoadTexture("data/images/background.png");
    Sound start;
    
    Music music;
  
    Texture2D backopt = LoadTexture("data/images/background.png");

    float lastBackTime = GetTime() - 1;
    float speed;
    float speedTime;
    float meteorTimer;
    int meteorspeed;
    int skin;
    int playerradius;
    float scrolebackground = 0.0f;
    bool fullc = false;
    
                    int scorei = 4;
                    int mind = scorei - 2;
                    int maxd = scorei + 2;
        
    ufologo.width = 200;
    ufologo.height = 200;   
    player1t.width = 300;
    player1t.height = 160;   
    player2t.width = 300;
    player2t.height = 160;
    player3t.width = 300;
    player3t.height = 160;    
    
    std::vector<Meteor> meteors;
    while (IsWindowReady())   
    {   if(!IsWindowFullscreen() && !fullc){ToggleFullscreen();fullc = true;}
        if (IsKeyPressed(KEY_DELETE)){
                EndDrawing();
                CloseWindow();
                return 0;
                };
        if (IsKeyPressed(KEY_F11)) {ToggleFullscreen();}
        scrolebackground -= 1.0f;
        if (scrolebackground <= -background.width*2) scrolebackground = 0;
        BeginDrawing();
        UpdateMusicStream(music);
        ClearBackground(BLACK);
        Rectangle startbutton = {590,410,150,60};
        Rectangle optionbutton = {580,490,170,60};
        //Rectangle exitbutton = {600,490,130,60};
        Rectangle exitbutton = {600,570,130,60};
        Rectangle backbutton = {1200,570,130,60};
        Rectangle player1 = {30,100,170,60};
        Rectangle player2 = {30,200,170,60};
        Rectangle player3 = {30,300,170,60};
        Vector2 mousePoint = { 0.0f, 0.0f };
        std::string s = std::to_string((int)score);
        char const *pchar = s.c_str();
        
        switch(scene)
        {


// MENU

            case Menu:
                music = LoadMusicStream("data/audio/music.mp3");
                //start = LoadSound("data/audio/start.wav");
                DrawTextureEx(background, Vector2{ scrolebackground, 20 }, 0.0f, 2.0f, WHITE);
                DrawTextureEx(background, Vector2{ background.width*2 + scrolebackground, 20 }, 0.0f, 2.0f, WHITE);
                DrawText("ufo", 580, 300 + sin(GetTime()*10)*1.2, 100, {200, 200, 200, 255});
                DrawTexture(ufologo, 540, 100 + sin(GetTime()*10)*1.2, WHITE);
                //DrawRectangle(550,200,200,100,WHITE);
               // DrawText("Score: ", 780, 600 , 80, {200, 200, 200, 255});
                //DrawText(pchar, 1050, 600 , 100, {200, 200, 200, 255});
                DrawRectangleRec(startbutton,WHITE);
                DrawText("Start", 610, 420, 40, GRAY);
                DrawRectangleRec(optionbutton,WHITE);
                DrawText("Options", 590, 500, 40, GRAY);
                DrawRectangleRec(exitbutton,WHITE);
                //DrawText("Exit", 625, 500, 40, GRAY);
                DrawText("Exit", 625, 580, 40, GRAY);
                mousePoint = GetMousePosition();
                 if (CheckCollisionPointRec(mousePoint, startbutton))
                {   
                    
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                    scene = Game;
                    meteors.clear();
                    speed = 1;
                    Player player({20, 20}, 1.0f, 10, 0,playert);
                    speedTime = GetTime();
                    meteorTimer = GetTime();
                    meteorspeed = 6;
                    score = 0;
                    InitAudioDevice();
                    PlayMusicStream(music);
                    PlaySound(start);
                }
                else{
                    DrawRectangleRec(startbutton, GRAY);
                    DrawText("Start", 610, 420, 40, BLACK);
                }
                };
                if (CheckCollisionPointRec(mousePoint, optionbutton))
                {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                    scene = Options;
                }
                else{
                    DrawRectangleRec(optionbutton, GRAY);
                    DrawText("Options", 590, 500, 40, BLACK);
                }};
                if (CheckCollisionPointRec(mousePoint, exitbutton))
                {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                        EndDrawing();
                    CloseWindow();
                    return 0;   
                }
                else{
                    DrawRectangleRec(exitbutton, GRAY);
                    //DrawText("Exit", 625, 500, 40, BLACK);
                    DrawText("Exit", 625, 580, 40, BLACK);
                }
                };
                
                if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_LEFT) && GetTime() > lastBackTime + 0.5f)
                {EndDrawing();CloseWindow();return 0;};
                break;

//  OPTIONS

            case Options:
                DrawTexture(backopt,0,0, WHITE); 
                DrawRectangleRec(backbutton,WHITE);
                DrawRectangle(0,0,300,768,WHITE);
                DrawRectangleRec(player1, BLACK);
                DrawRectangleRec(player2, BLACK);
                DrawRectangleRec(player3, BLACK);
                DrawText("SELECT",50,10,50,BLACK);
                DrawText("Cartoon",45,120,35,WHITE);
                DrawText("Blue",80,220,35,WHITE);
                DrawText("Red",80,320,35,WHITE);
                DrawText("Back", 1220, 580, 40, GRAY);
                mousePoint = GetMousePosition();
               
                if (CheckCollisionPointRec(mousePoint, backbutton))
                {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                        scene = Menu;
                    break;
                }
                else{
                    DrawRectangleRec(backbutton, GRAY);
                    DrawText("Back", 1220, 580, 40, BLACK);
                }
                };
                ///////////////
                
                if (CheckCollisionPointRec(mousePoint, player1))
                {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                    UnloadTexture(playert);
                    Texture2D playert = LoadTexture("data/images/player1.png");
                    Player player({0, 0}, 0.0, -10, 0,playert);
                    skin = 1;
                    DrawTexture(player1t, 740, 250 + sin(GetTime()*10)*1.2, WHITE);
                }
                else{
                    DrawRectangleRec(player1, GRAY);
                    DrawTexture(player1t, 740, 250 + sin(GetTime()*10)*1.2, WHITE);
                    DrawText("Radius: 25",40,400,40,BLACK);
                    DrawText("Cartoon",45,115,35,WHITE);
                }};
                if (CheckCollisionPointRec(mousePoint, player2))
                {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                    UnloadTexture(playert);
                    playert = LoadTexture("data/images/player2.png");
                    Player player({0, 0}, 0.0, -10, 0,playert); 
                    skin = 2;
                    DrawTexture(player2t, 740, 250 + sin(GetTime()*10)*1.2, WHITE);
                }
                else{
                    DrawRectangleRec(player2, GRAY);
                    DrawTexture(player2t, 740, 250 + sin(GetTime()*10)*1.2, WHITE);
                    DrawText("Radius: 30",40,400,40,BLACK);
                    DrawText("Blue",80,215,35,WHITE);
                }};
                if (CheckCollisionPointRec(mousePoint, player3))
                {
                    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                    UnloadTexture(playert);
                    playert = LoadTexture("data/images/player3.png");
                    Player player({0, 0}, 0.0, -10, 0,playert); 
                    skin = 3;
                    DrawTexture(player3t, 740, 250 + sin(GetTime()*10)*1.2, WHITE);
                    
                }
                else{
                    DrawRectangleRec(player3, GRAY);
                    DrawTexture(player3t, 740, 250 + sin(GetTime()*10)*1.2, WHITE);
                    DrawText("Radius: 40",40,400,40,BLACK);
                    DrawText("Red",80,315,35,WHITE);
                }};
                
                /////////////
                if (IsKeyPressed(KEY_BACKSPACE)||IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_LEFT)){scene=Menu;StopMusicStream(music);break;};
                break;

// GAME

            case Game:
                DrawTextureEx(background, Vector2{ scrolebackground, 20 }, 0.0f, 2.0f, WHITE);
                DrawTextureEx(background, Vector2{ background.width*2 + scrolebackground, 20 }, 0.0f, 2.0f, WHITE);
                GameplayManager(&speed, &speedTime, &meteorTimer, &meteors, &player,&meteorspeed,&playerradius);
                
                player.Move();
                planet.SetRotation(1*speed);
                
                while(score > scorei){

                    speed = mind + rand() % maxd;
                    scorei = scorei+5;
                    meteorspeed = meteorspeed - 1;
                    if(meteorspeed < 1){
                        meteorspeed = 1;
                    }
                }
                playerradius = 1;
                switch(skin){
                    case 1:
                    playerradius = 25;
                    
                case 2:
                    playerradius = 30;
                    
                case 3:
                    playerradius = 40; 
                default:
                playerradius = 25;
                }
                if(planet.CheckCollision(player))
                {
                    score++;
                }
                s = std::to_string((int)score);
                pchar = s.c_str(); 
                player.Draw();
                planet.Draw();
                
                DrawText("Score: ", 920, 30 , 80, {200, 200, 200, 255});
                DrawText(pchar, 1190, 20 , 100, {200, 200, 200, 255});
                
                 if (IsKeyPressed(KEY_BACKSPACE)||IsGamepadButtonDown(0, GAMEPAD_BUTTON_MIDDLE_LEFT) && GetTime() > lastBackTime + 0.5f){
                     scene=Menu;
                     StopMusicStream(music);
                     lastBackTime = GetTime();
                 break;};
                break;

//  You Lose

            case Lose:
                    DrawTextureEx(background, Vector2{ scrolebackground, 20 }, 0.0f, 2.0f, WHITE);
                    DrawTextureEx(background, Vector2{ background.width*2 + scrolebackground, 20 }, 0.0f, 2.0f, WHITE);
                    DrawText("You Lose", 500, 300 + sin(GetTime()*10)*1.2, 80, {200, 200, 200, 255});
                    DrawText("Press \"Space\" to continue",400,500,40,WHITE);
                    if (IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) || IsKeyPressed(KEY_SPACE)){scene=Menu;};
                    break;
        }
        EndDrawing();
    }
    UnloadTexture(background);
    //UnloadTexture(backopt);
    CloseWindow();
    return 0;
}

void GameplayManager(float* speedPtr, float* speedTime, float* meteorTimer, std::vector<Meteor>* meteors, Player* player, int* meteorspeed, int* playerradius)
{
    if(GetTime() > *speedTime + 20)
    {
        *speedTime = GetTime();
        *speedPtr *= -1.5f;
    }
    if(GetTime() > *meteorTimer + *meteorspeed)
    {
        *meteorTimer = GetTime();
        int meteorAmount = GetRandomValue(1, 8);
        for(int i = 0; i < meteorAmount; i++)
        {
            Meteor m;
            (*meteors).push_back(m);
        }
    }

    for(int i = 0; i < (*meteors).size(); i++)
    {
        (*meteors)[i].Draw();
        (*meteors)[i].Move();
        float xPos = (*meteors)[i].position.x;
        float yPos = (*meteors)[i].position.y;
        if(xPos > 1368 || xPos < -2 || yPos > 770 || yPos < -2)
        {
            (*meteors).erase((*meteors).begin() + i);
        }
        if(CheckCollisionCircles((*meteors)[i].position, 20, {683,400}, 100))
        {
            (*meteors).erase((*meteors).begin() + i);
            PlaySound((*meteors)[i].hit);
        }
        if(CheckCollisionCircles((*meteors)[i].position, 20, (*player).position, *playerradius))
        {
            StopMusicStream(music);
            Sound end = LoadSound("data/audio/end.wav");
            PlaySound(end);
            scene = Lose;
            (*meteors).erase((*meteors).begin() + i);
        }
    }
}