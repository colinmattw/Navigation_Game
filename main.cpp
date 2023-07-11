#include "raylib.h"
#include <cmath>
#include <string>
#include "Grid.hpp"
#include <iostream>
#include "Robot2.hpp"
#include <random>
#include "button2.hpp"
#include "DisplayQueue.hpp"
using namespace std;

//init
Grid grid = Grid(7, 7, 80, 430, 20);
Tile *s = &grid.grid[3][3];
Robot robot = Robot(2.0f, s, 12);
DisplayQ dq = DisplayQ();
Color gameOverColor = RED;
Color pathColor = GREEN;
vector<Vector2> pathCoords;

//buttons init
Button upb = Button({10, 530}, (string)"Up");
Button downb = Button({95, 530}, (string)"Down");
Button leftb = Button({180, 530}, (string)"Left");
Button rightb = Button({265, 530}, (string)"Right");
struct
{
    const Vector2 pos = {330, 450};
    Color currentColor = RED;
    Color onColor = GREEN;
    const float radius = 30.0f;
} runButton;

int main(void)
{   
    //init outofbounds reference
    robot.SetOutOfBounds(grid.GetOutOfBounds());
    //screen dimensions init
    const int screenWidth = 1000;
    const int screenHeight = 600;

    //OpenGL context
    InitWindow(screenWidth, screenHeight, "Main");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        //check if "run" button is pressed
        if(CheckCollisionPointCircle(GetMousePosition(), {runButton.pos.x, runButton.pos.y}, runButton.radius))
        {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && runButton.currentColor.isEqual(RED) && robot.getQueue().size() > 0)
            {   
                //turn off path helper dots when "run is enabled"
                grid.TurnOffDots();
                runButton.currentColor = runButton.onColor;
            }
        }

        //only do this is "run" is not enabled
        if(runButton.currentColor.isEqual(RED))
        {
            //push moves onto robot's moveQueue when buttons are clicked
            if(upb.isPressed(true))
            {
                robot.pushMove(1);
                pathCoords = robot.GetPathCoords();
            }
            if(downb.isPressed(true))
            {
                robot.pushMove(2);
                pathCoords = robot.GetPathCoords();
            }
            if(leftb.isPressed(true))
            {
                robot.pushMove(3);
                pathCoords = robot.GetPathCoords();
            }
            if(rightb.isPressed(true))
            {
                robot.pushMove(4);
                pathCoords = robot.GetPathCoords();
            }

            //remove moves from the back of the queue
            if(IsKeyPressed(KEY_A))
            {
                if(robot.getQueue().size() > 0)
                {
                    robot.PopBack();
                    pathCoords = robot.GetPathCoords();
                }
            }

        }

        //your local try and catch
        try
        {
            dq.updateQ(robot.getQueue());
        }   
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        //let the robot start executing moves if "run" is enabled
        if(runButton.currentColor.isEqual(GREEN))
        {   
            robot.execMove();
        }

        //setup framebuffer
        BeginDrawing();
        ClearBackground(RAYWHITE);

        //draw important things
        grid.drawGrid();
        robot.drawRobot();

        dq.drawDisplayQ();

        upb.drawButton();
        downb.drawButton();
        leftb.drawButton();
        rightb.drawButton();

        //draw "run" button
        DrawCircle(runButton.pos.x, runButton.pos.y, runButton.radius, runButton.currentColor);

        //draw arrow
        DrawTriangle({220, 30}, {245, 40}, {245, 20}, RED);

        //draw divider
        DrawRectangle(400, 0, 30, 600, BLACK);

        //draw robotpath except for when "run" is enabled
        if(runButton.currentColor.isEqual(RED))
        {
            pathColor.a = (abs(cos(GetTime() * 2)) + 0.5f) * 170.0f;
            for(int i = 0; i < pathCoords.size(); ++i)
            {
                DrawCircle(pathCoords[i].x, pathCoords[i].y, 10.0f, pathColor);
            }
        }

        //draw game over sign
        gameOverColor.a = (abs(cos(GetTime())) + 1) * 127.5;
        if(robot.GetSpeed() == 0.0f)
        {   
            DrawText("Game Over", 520, 250, 75, gameOverColor);
        }

        //draw score
        DrawText("Score:", 250, 130, 25, GRAY);
        string s1 = to_string(robot.getScore());
        DrawText(s1.c_str(), 340, 130, 25, GRAY);

        DrawFPS(320, 30);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}