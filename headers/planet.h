#pragma once
#include "player.h"

extern void SelectLevel();

extern int level1;


class Node
{
public:
    Texture2D texture;
    Vector2 position;
    float rotation;

    Node();

    void Draw();
};

class Planet
{
public:
    Sound shot;
    Texture2D texture;
    float rotation;
    float speed;
    Node node;
    Planet();
    Planet(Texture2D f){
        settexture(f);
    };
   void settexture(Texture2D n){
       texture = n;
    };
    Texture2D gettexture(){
        return texture;
    }


    void Draw();

    void SetRotation(float value);

    bool CheckCollision(Player player);
};