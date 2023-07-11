#ifndef ROBOT2_HPP
#define ROBOT2_HPP

#include <iostream>
#include "Tile.hpp"
#include "raylib.h"
#include <deque>
#include "Grid.hpp"
#include <string>
using namespace std;

class Robot
{
    private:

        Tile *currentTile;
        Tile *targetTile;
        float currentX;
        float currentY;
        std::deque<int> moveQueue;
        float speed;
        int maxQsize;
        Tile *outOfBounds;
        int score;

    public: 
        Robot()
        {
            currentTile = nullptr;
            targetTile = nullptr;
            speed = 1.0f;
            currentX = 0;
            currentY = 0;
            maxQsize = 10;
            score = 0;
        }

        Robot(float inSpeed, Tile *startTile, int inMaxQSize)
        {
            speed = inSpeed;
            currentTile = startTile;
            targetTile = nullptr;
            currentX = currentTile->getMidpointX();
            currentY = currentTile->getMidpointY();
            maxQsize = inMaxQSize;
            score = 0;
        }

        //pushMove
        void pushMove(int inMove)
        {
            if(moveQueue.size() < maxQsize)
            {   
                if(moveQueue.size() == 0)
                {
                    moveQueue.push_back(inMove);
                    setTarget();
                }
                else
                {
                    moveQueue.push_back(inMove);
                }
            }
        }

        void drawRobot()
        {
            DrawCircle(currentX, currentY, 25.0f, GRAY);
        }

        //set the robot's target to front move in the movequeue
        void setTarget()
        {   
            if(!moveQueue.empty())
            {
                switch(moveQueue.front())
                {
                    case 1:
                        targetTile = currentTile->getUp();
                        break;
                    case 2:
                        targetTile = currentTile->getDown();
                        break;
                    case 3:
                        targetTile = currentTile->getLeft();
                        break;
                    case 4:
                        targetTile = currentTile->getRight();
                        break;
                }
            }
        }

        //execute and pop moves from the movequeue
        void execMove()
        {   
            if(!moveQueue.empty())
            {   
                //stop if target is out of bounds or run into barrier
                if(targetTile == outOfBounds || targetTile->isOccupied())
                {
                    SetSpeed(0.0f);
                }
                //check if robot collected any coins
                if(targetTile->GetHasCoin())
                {
                    if(CheckCollisionCircles({currentX, currentY}, 25.0f, {targetTile->GetCoin()->GetPos()},
                    targetTile->GetCoin()->GetRadius()))
                    {
                        if(targetTile->GetCoin()->GetIsBigCoin() && !targetTile->GetCoin()->GetIsCollected())
                        {
                            score += 2;
                        }
                        if(!targetTile->GetCoin()->GetIsBigCoin() && !targetTile->GetCoin()->GetIsCollected())
                        {
                            ++score;
                        }
                        targetTile->GetCoin()->CollectCoin();
                    }
                }
                //check if robot has arrived at target tile
                if(currentX == targetTile->getMidpointX() && currentY == targetTile->getMidpointY())
                {   
                    currentTile = targetTile;
                    moveQueue.pop_front();
                    //cout << "moved popped" << endl;
                    setTarget();
                }
                if(moveQueue.front() == 1)
                {
                    currentY -= speed;
                    //cout << "moving up" << endl;
                }
                if(moveQueue.front() == 2)
                {
                    currentY += speed;
                    //cout << "moving dowwn" << endl;
                }
                if(moveQueue.front() == 3)
                {
                    currentX -= speed;
                    //cout << "moving left" << endl;
                }
                if(moveQueue.front() == 4)
                {
                    currentX += speed;
                    //cout << "moving right" << endl;
                }
            }
            else
            {
                //cout << "Done moving" << endl;
            }
        }

        //put the coordinates of tiles in robot's path for drawing later
        std::vector<Vector2> GetPathCoords()
        {
            std::deque<int> temp = moveQueue;
            std::vector<Vector2> coords;
            Tile *current = currentTile;
            for(int i = 0; i < moveQueue.size(); ++i)
            {
                switch(temp.front())
                {
                    case 1:
                        if(current->getUp() != outOfBounds && !current->getUp()->isOccupied())
                        {
                            coords.push_back({current->getUp()->getMidpointX(), current->getUp()->getMidpointY()});
                            current = current->getUp();
                        }
                        else
                        {
                            i = moveQueue.size();
                        }
                        break;

                    case 2:
                        if(current->getDown() != outOfBounds && !current->getDown()->isOccupied())
                        {
                            coords.push_back({current->getDown()->getMidpointX(), current->getDown()->getMidpointY()});
                            current = current->getDown();
                        }
                        else
                        {
                            i = moveQueue.size();
                        }
                        break;

                    case 3:
                        if(current->getLeft() != outOfBounds && !current->getLeft()->isOccupied())
                        {
                            coords.push_back({current->getLeft()->getMidpointX(), current->getLeft()->getMidpointY()});
                            current = current->getLeft();
                        }
                        else
                        {
                            i = moveQueue.size();
                        }
                        break;

                    case 4:
                        if(current->getRight() != outOfBounds && !current->getRight()->isOccupied())
                        {
                            coords.push_back({current->getRight()->getMidpointX(), current->getRight()->getMidpointY()});
                            current = current->getRight();
                        }
                        else
                        {
                            i = moveQueue.size();
                        }
                        
                        break;
                }
                temp.pop_front();
            }
            return coords;
        }

        Tile *getTarget()
        {
            return targetTile;
        }

        Tile *getCurrentTile()
        {
            return currentTile;
        }

        void popMove()
        {
            moveQueue.pop_front();
            //cout << "move popped" << endl;
        }

        void PopBack()
        {
            moveQueue.pop_back();
        }

        float getCurrentX()
        {
            return currentX;
        }
        float getCurrentY()
        {
            return currentY;
        }
        
        std::deque<int> getQueue()
        {
            return moveQueue;
        }

        void setCurrentTile(Tile *tile)
        {
            currentTile = tile;
        }

        void SetSpeed(float inSpeed)
        {
            speed = inSpeed;
        }

        void SetOutOfBounds(Tile *t)
        {
            outOfBounds = t;
        }

        float GetSpeed()
        {
            return speed;
        }

        int getScore()
        {
            return score;
        }
};
#endif