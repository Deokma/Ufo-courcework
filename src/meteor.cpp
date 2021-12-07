#include "../include/raylib.h"
#include <iostream>
#include <cmath>
#include "../headers/meteor.h"


Meteor::Meteor()
{
    int rand = GetRandomValue(0, 6);
    int rand2 = GetRandomValue(1, 6);
    hit = LoadSound("data/audio/meteorhit.wav");
    switch(rand)
    {
            /*




            |-------------------------|
            */
        case 0:
            position.x = GetRandomValue(0, 1363);
            position.y = 0;
            velocity.x = GetRandomValue(10, 40) / 10 * rand2;
            velocity.y = 1 * rand2;
            break;
            /*
            |-------------------------|
        

        
            
            */
        case 1:
            position.x = GetRandomValue(0, 1363);
            position.y = 765;
            velocity.x = GetRandomValue(0, 40) / 10 * rand2;
            velocity.y = -1 * rand2;
            break;
            /*
            |
            |
            |
            |
            |
            */
        case 2:
            position.x = 0;
            position.y = GetRandomValue(0, 765);
            velocity.x = 1 * rand2;
            velocity.y = GetRandomValue(10, 40) / 10 * rand2;
            break;
            /*
                                |
                                |
                                |
                                |
                                |
            */
        case 3:
            position.x = 1363;
            position.y = GetRandomValue(0, 765);
            velocity.x = -1 * rand2;
            velocity.y = GetRandomValue(10, 40) / 10 * rand2;
            break;
        default:
            position.x = 1363;
            position.y = GetRandomValue(0, 765);
            velocity.x = -1 * rand2;
            velocity.y = GetRandomValue(0, 40) / 10 * rand2;
            break;
    }
}

void Meteor::Draw()
{
    DrawCircle(position.x, position.y, 20, GRAY);
}

void Meteor::Move()
{
    position.x += velocity.x;
    position.y += velocity.y;
}