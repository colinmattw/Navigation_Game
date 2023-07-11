#ifndef BUTTON2_HPP
#define BUTTON2_HPP
#include "raylib.h"
#include <iostream>
#include <string>

class Button
{
    private:
        int width;
        int height;
        int borderMargin;
        Vector2 pos;
        Color outerColor;
        Color innerColor;
        Color hoverColor;
        Color currentColor;
        Color textColor;
        std::string text;
        int fontSize;

    public:
        Button()
        {
            width = 75;
            height = 50;
            pos = {50,50};
            outerColor = BLUE;
            innerColor = WHITE;
            hoverColor = BLUE;
            currentColor = RAYWHITE;
            text = "Text";
            borderMargin = 5;
            textColor = GRAY;
            fontSize = 20;
        }
        Button(Vector2 inPos, std::string inText)
        {
            width = 75;
            height = 50;
            pos = inPos;
            outerColor = BLUE;
            innerColor = WHITE;
            hoverColor = BLUE;
            currentColor = RAYWHITE;
            text = inText;
            borderMargin = 5;
            textColor = GRAY;
            fontSize = 20;
        }

        //return if buttonn is pressed and change hover color if enabled
        bool isPressed(bool useHoverColor)
        {   
            bool mouseIsOnButton = false;
            if((GetMouseX() < (pos.x + width) && GetMouseX() > pos.x) && 
                (GetMouseY() < (pos.y + height) && GetMouseY() > pos.y))
                {
                    mouseIsOnButton = true;
                    if(useHoverColor)
                    {
                        currentColor = hoverColor;
                    }
                }
            else
            {
                currentColor = innerColor;
            }

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseIsOnButton)
            {   
                return true;
            }
            else
            {
                return false;
            }
        }

        void drawButton()
        {   
            //draw outter rectangle
            DrawRectangle(pos.x, pos.y, width, height, outerColor);

            //draw inner recntangle
            DrawRectangle((pos.x + borderMargin), (pos.y + borderMargin),
            (width - (2*borderMargin)), (height - (2*borderMargin)), currentColor);
            DrawText(text.c_str(), pos.x + 12, pos.y + 15, fontSize, textColor);

        }
};

#endif