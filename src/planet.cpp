#include "../include/raylib.h"
#include <iostream>
#include <cmath>
#include "../headers/planet.h"
#include <fstream>
#include <string>

using namespace std;

extern int radplan;



Node::Node()
{
    rotation = GetRandomValue(0, 360);
    position.x = 683 + cos(rotation)*radplan;
    position.y = 400 + sin(rotation)*radplan;
}

void Node::Draw()
{
    if(rotation < 0) {rotation += 360;}
    position.x = 683 + cos(rotation)*radplan;
    position.y = 400 + sin(rotation)*radplan;
    DrawCircle(position.x, position.y, 20, ORANGE);
}

Planet::Planet(){
    texture = LoadTexture("data/images/earth.png");;
    texture.width /= 17.0f;
    texture.height /= 17.0f;
    shot = LoadSound("data/audio/hitnode.wav");
    speed = .5f;
}
void Planet::Draw()
{
    node.Draw();
    int frameWidth = texture.width;
    int frameHeight = texture.height;

    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    Rectangle destRec = { 683.0f, 400.0f, frameWidth*2, frameHeight*2 };
    Vector2 origin = { (float)frameWidth, (float)frameHeight};
    DrawTexturePro(texture, sourceRec, destRec, origin, (float)rotation, WHITE);
}

void Planet::SetRotation(float value)
{
    rotation += value * speed;
    node.rotation += value / 50 * speed;
}

bool Planet::CheckCollision(Player player)
{
    for(int i = 0; i < player.bullets.size(); i++)
    {
        if(CheckCollisionCircles(player.bullets[i].position, 5, node.position, 20))
        {
            PlaySound(shot);
            node = Node();
            player.bullets.erase(player.bullets.begin() + i);
            return true;
        }
    }
    return false;
}