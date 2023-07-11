#ifndef COIN_HPP
#define COIN_HPP
#include "raylib.h"

class Coin
{
    private:
        float radius;
        Vector2 pos;
        bool isBigCoin;
        int value;
        Color color;
        bool isCollected;
    
    public:
        Coin(bool isBig, Vector2 inPos)
        {
            if(isBig)
            {
                radius = 20.0f;
                value = 2;
                isBigCoin = true;
            }
            else
            {
                radius = 15.0f;
                value = 1;
                isBigCoin = false;
            }
            pos = inPos;
            color = GOLD;
            isCollected = false;
        }

        Vector2 GetPos()
        {
            return pos;
        }

        void CollectCoin()
        {
            isCollected = true;
        }

        void DrawCoin()
        {   
            if(!isCollected)
            {
                DrawCircle(pos.x, pos.y, radius, color);
            }
        }
        bool GetIsBigCoin()
        {
            return isBigCoin;
        }

        float GetRadius()
        {
            return radius;
        }

        bool GetIsCollected()
        {
            return isCollected;
        }
};

#endif