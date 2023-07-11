#ifndef DISPLAYQUEUE_HPP
#define DISPLAYQUEUE_HPP
#include "raylib.h"
#include <deque>

class DisplayQ
{
    private:
        int width;
        int height;
        int spacing;
        Vector2 pos;
        Color color;
        std::deque<int> q;

    public:
        DisplayQ()
        {
            width = 200;
            height = 30;
            spacing = 10;
            pos = {20, 20};
            color = LIGHTGRAY;
        }

        DisplayQ(int inWidth, int inHeight, int spacing, Vector2 inPos, Color color)
        {
            width = inWidth;
            height = inHeight;
            pos = inPos;
        }

        void drawDisplayQ()
        {
            Vector2 currentPos = pos;
            std::deque<int> tempQ = q;
            for(int i = 0; i < q.size(); i++)
            {    
                DrawRectangle(currentPos.x, currentPos.y, width, height, color);
                if(tempQ.front() == 1)
                {
                    DrawText("Up", currentPos.x, currentPos.y, 20, DARKGRAY);
                }
                if(tempQ.front() == 2)
                {
                    DrawText("Down", currentPos.x, currentPos.y, 20, DARKGRAY);
                }
                if(tempQ.front() == 3)
                {
                    DrawText("Left", currentPos.x, currentPos.y, 20, DARKGRAY);
                }
                if(tempQ.front() == 4)
                {
                    DrawText("Right", currentPos.x, currentPos.y, 20, DARKGRAY);
                }
                tempQ.pop_front();
                currentPos.y += (spacing + height);
            }
        }

        void updateQ(std::deque<int> inQ)
        {
            q = inQ;
        }

        int getFront()
        {
            return q.front();
        }

};


#endif