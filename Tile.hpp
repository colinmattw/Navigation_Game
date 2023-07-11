#ifndef TILE_HPP
#define TILE_HPP

#include "raylib.h"
#include "Coin.hpp"
#include <iostream>

class Tile
{
    private:
        int width;
        bool occupied;
        Color color;
        float posX;
        float posY;
        float midPointX;
        float midPointY;
        Tile *up;
        Tile *down;
        Tile *left;
        Tile *right;
        bool drawDot;
        bool hasCoin;
        Coin *coin;

        void calcMidpoint()
        {
            float dist = width / 2;
            midPointX = posX + dist;
            midPointY = posY + dist;
        }

    public:
        Tile()
        {
            width = 10;
            occupied = false;
            color = WHITE;
            posX = 0.0f;
            posY = 0.0f;
            up = nullptr;
            down = nullptr;
            left = nullptr;
            right = nullptr;
            drawDot = true;
            hasCoin = false;
            calcMidpoint();

        }
        Tile(int inWidth, bool inOccupied, Color inColor, float inPosX, float inPosY)
        {
            width = inWidth;
            occupied = inOccupied;
            color = inColor;
            posX = inPosX;
            posY = inPosY;
            up = nullptr;
            down = nullptr;
            left = nullptr;
            right = nullptr;
            drawDot = true;
            hasCoin = false;
            calcMidpoint();
        }

        int getWidth()
        {
            return width;
        }

        float getMidpointX()
        {
            return midPointX;
        }
        float getMidpointY()
        {
            return midPointY;
        }

        bool isOccupied()
        {
            return occupied;
        }

        void drawTile()
        {
            //DrawRectangle(posX, posY, width, width, color);
            if(hasCoin)
            {
                coin->DrawCoin();
            }
            if(drawDot)
            {
                DrawCircle(midPointX, midPointY, 10, color);
            }
            if(occupied)
            {
                DrawRectangle(posX, posY, width, width, GRAY);
            }
        }

        void setUp(Tile *inTile)
        {
            up = inTile;
        }
        void setDown(Tile *inTile)
        {
            down = inTile;
        }
        void setLeft(Tile *inTile)
        {
            left = inTile;
        }
        void setRight(Tile *inTile)
        {
            right = inTile;
        }

        Tile *getUp()
        {
            return up;
        }
        Tile *getDown()
        {
            return down;
        }
        Tile *getLeft()
        {
            return left;
        }
        Tile *getRight()
        {
            return right;
        }

        void setColor(Color rayColor)
        {
            color = rayColor;
        }

        void SetAsBarrier()
        {
            occupied = true;
        }

        void TurnOnDot()
        {
            drawDot = true;
        }

        void TurnOffDot()
        {
            drawDot = false;
        }

        void SetCoin(bool isBig)
        {
            coin = new Coin(isBig, {midPointX, midPointY});
            hasCoin = true;
        }

        bool GetHasCoin()
        {
            return hasCoin;
        }

        Coin *GetCoin()
        {
            return coin;
        }

};
#endif