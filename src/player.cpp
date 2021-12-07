#include "../include/raylib.h"
#include <iostream>
#include "../headers/player.h"
#include <cmath>

extern int playerdistance;
extern Texture2D logo;

Player::Player(Vector2 _position, float _speed, int _size, float _rotation,Texture2D _player){
    position = _position;
    speed = _speed;
    size = _size;
    rotation = _rotation;
    texture = _player;
    texture.width /= 16;
    texture.height /= 16;
    lastShotTime = GetTime() - 1;
    InitAudioDevice();
    shot = LoadSound("data/audio/shot.wav");
}

void Player::Move()
{
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
    {
        rotation -= speed;
    }
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
    {
        rotation += speed;
    }

    if((IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) || IsKeyDown(KEY_SPACE)) && GetTime() > lastShotTime + 0.5f)
    {
        Shoot();   
        PlaySound(shot);
        lastShotTime = GetTime();
    }
}

void Player::Draw()
{
    int frameWidth = texture.width;
    int frameHeight = texture.height;
    float height;
    height = 240;
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    Rectangle destRec = { 683.0f, 400.0f, frameWidth*2, frameHeight*2 };
    Vector2 origin = { (float)frameWidth, (float)frameHeight + playerdistance + ((float)sin(GetTime() * 10))*2};
    DrawTexturePro(texture, sourceRec, destRec, origin, (float)rotation, WHITE);

    for(int i = 0; i < bullets.size(); i++)
    {
        //Hit Planet
        if(CheckCollisionCircles(bullets[i].position, 5 ,{683, 400}, 100))
        {
            bullets.erase(bullets.begin() + i);
            PlaySound(bullets[i].shot);
        }

        bullets[i].Move();
        bullets[i].Draw();
    }

    if(rotation < 0){rotation += 360;}
    if(rotation > 360){rotation -= 360;}

    float newRot = rotation - 90;

    position = {683 + cos((newRot * DEG2RAD)) * height, 400 + sin((newRot * DEG2RAD)) * height};
}

void Player::Shoot()
{
    float height;
        height = 230;
    

    float newRot = rotation - 90;
    position = {683 + cos((newRot * DEG2RAD)) * height, 400 + sin((newRot * DEG2RAD)) * height};
    Bullet b(position);
    bullets.push_back(b);
}

Bullet::Bullet(Vector2 _position)
{
    position = _position;
    direction.x = position.x - 683;
    direction.y = position.y - 400;
    shot = LoadSound("data/audio/bulletimpact.wav");
}

void Bullet::Draw()
{
    DrawCircle(position.x, position.y, 5, GREEN);
}

void Bullet::Move()
{
    position.x -= direction.x * 0.03f;
    position.y -= direction.y * 0.03f;
}