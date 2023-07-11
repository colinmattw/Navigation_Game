#ifndef GRID_HPP
#define GRID_HPP

#include "raylib.h"
#include "Tile.hpp"
#include "Coin.hpp"
#include <vector>
#include <iostream>
#include <random>

class Grid
{
    private:
        int widthInTiles;
        int heightInTiles;
        int size;
        float topLeftCornerX;
        float topLeftCornerY;
        Tile outOfBounds;

    public:
        std::vector<std::vector<Tile>> grid;
        Grid(int inWidth, int inHeight, int tileSize, float startX, float startY)
        {
            widthInTiles = inWidth;
            heightInTiles = inHeight;
            size = heightInTiles * widthInTiles;
            topLeftCornerX = startX;
            topLeftCornerY = startY;
            outOfBounds = Tile();

            for(int h = 0; h < inHeight; ++h)
            {   
                std::vector<Tile> a;
                for(int k = 0; k < inWidth; ++k)
                {
                    a.push_back(Tile());
                }
                grid.push_back(a);
            }

            float currentX = startX;
            float currentY = startY;
            Color tileColor = (Color){200, 200, 200, 128};
            for(int i = 0; i < inHeight; ++i)
            {
                for(int j = 0; j < inWidth; ++j)
                {
                    grid[j][i] = Tile(tileSize, false, tileColor, currentX, currentY);
                    currentX += tileSize;
                }
                currentX = startX;
                currentY += tileSize;
            }
            linkTiles();
            for (int i = 0; i < 3; ++i)
            {
                SetBarriers(&grid[3][3], 3);
            }
            SpawnCoins(&grid[3][3], 3, 4);
        }

        void linkTiles()
        {
            for (int i = 0; i < heightInTiles; ++i)
            {
                for (int j = 0; j < widthInTiles; ++j)
                {   
                    grid[j][i].setUp(&grid[j][i - 1]);
                    grid[j][i].setDown(&grid[j][i + 1]);
                    grid[j][i].setLeft(&grid[j - 1][i]);
                    grid[j][i].setRight(&grid[j + 1][i]);
                }
            }
            for(int i = 0; i < heightInTiles; ++i)
            {
                //link outOfBounds tile
                grid[i][0].setUp(&outOfBounds);
                grid[widthInTiles-1][i].setRight(&outOfBounds);
                grid[i][heightInTiles-1].setDown(&outOfBounds);
                grid[0][i].setLeft(&outOfBounds);
            }
        }

        void drawGrid()
        {
            for(int i = 0; i < heightInTiles; i++)
            {
                for(int j = 0; j < widthInTiles; j++)
                {
                    grid[i][j].drawTile();
                }
            }
        }
        Tile *GetOutOfBounds()
        {
            return &outOfBounds;
        }

        void SetBarriers(Tile *robot, int amount)
        {   
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist (0,6);
            std::uniform_int_distribution<int> dir (1,4);
            int row;
            int column;
            int count = 1;
            int direction;
            Tile *robotSTart = robot;
            Tile *seed = robotSTart;
            Tile *current;
            while(seed == robotSTart || seed->isOccupied())
            {
                row = dist(mt);
                column = dist(mt);
                seed = &grid[row][column];
            }
            seed->SetAsBarrier();
            current = seed;
            while(count < amount)
            {
                direction = dir(mt);
                switch(direction)
                {
                    case 1:
                        if(current->getUp() != robotSTart && current->getUp() != &outOfBounds
                            && !current->getUp()->isOccupied())
                        {
                            current->getUp()->SetAsBarrier();
                            current = current->getUp();
                            ++count;
                        }
                        break;
                    case 2:
                        if(current->getDown() != robotSTart && current->getDown() != &outOfBounds
                            && !current->getDown()->isOccupied())
                        {
                            current->getDown()->SetAsBarrier();
                            current = current->getDown();
                            ++count;
                        }
                        break;
                    case 3:
                        if(current->getLeft() != robotSTart && current->getLeft() != &outOfBounds
                            && !current->getLeft()->isOccupied())
                        {
                            current->getLeft()->SetAsBarrier();
                            current = current->getLeft();
                            ++count;
                        }
                        break;
                    case 4:
                        if(current->getRight() != robotSTart && current->getRight() != &outOfBounds 
                            && !current->getRight()->isOccupied())
                        {
                            current->getRight()->SetAsBarrier();
                            current = current->getRight();
                            ++count;
                        }
                        break;
                }
            }

        }

        void TurnOnDots()
        {
            for(int i = 0; i < heightInTiles; ++i)
            {
                for(int j = 0; j < widthInTiles; ++j)
                {
                    grid[j][i].TurnOnDot();
                }
            }
        }

        void TurnOffDots()
        {
            for(int i = 0; i < heightInTiles; ++i)
            {
                for(int j = 0; j < widthInTiles; ++j)
                {
                    grid[j][i].TurnOffDot();
                }
            }
        }

        void SpawnCoins(Tile *robotStart, int bigAmount, int smallAmount)
        {   
            int bAmount = 0;
            int sAmount = 0;
            int row;
            int column;
            Tile *prospect;
            bool prospectIsBig;

            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist (0,6);
            std::uniform_int_distribution<int> bigOrSmall (0,1);

            while(bAmount < bigAmount || sAmount < smallAmount)
            {
                row = dist(mt);
                column = dist(mt);
                prospectIsBig = (bool)bigOrSmall(mt);

                prospect = &grid[row][column];
                if(!prospect->isOccupied() && prospect != robotStart && !prospect->GetHasCoin())
                {
                    if(prospectIsBig && bAmount < bigAmount)
                    {
                        prospect->SetCoin(true);
                        ++bAmount;
                    }
                    if(!prospectIsBig && sAmount < smallAmount)
                    {
                        prospect->SetCoin(false);
                        ++sAmount;
                    }
                }
            }
        }
};
#endif