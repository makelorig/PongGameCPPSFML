#include <iostream>
#define random(min,max) min+rand()%(max-min+1)
#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>
using namespace std;
using namespace sf;


int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    RenderWindow window(VideoMode(1550, 800), "ThePongVideoGame");

    window.setFramerateLimit(45);

    RectangleShape leftStick(Vector2f(20, 180));
    RectangleShape rightStick(Vector2f(20, 180));

    CircleShape ball(25);

    RectangleShape wall(Vector2f(25, 1800));

    Font textFont;
    textFont.loadFromFile("Text/bit5x5.ttf");

    Text leftMessage, rightMessage;
    leftMessage.setFont(textFont);
    leftMessage.setCharacterSize(64);
    rightMessage.setFont(textFont);
    rightMessage.setCharacterSize(64);

    Text winMessage;
    winMessage.setFont(textFont);
    winMessage.setCharacterSize(64);

    const int MAXBALLSPEED = 20;
    const int SPEEDUP = 1;
    int ballGoPosY = 200;
    int ballGoPosX = 200;
    int BALLSPEED = 10;

    int DirectX = 1;
    int DirectY = 1;


    const int DOWNBORDER = 625;
    const int UPBORDER = 20;

    int leftGoPosY = 150;
    int rightGoPosY = 150;

    const int LPX = 25;
    const int RPX = 1500;

    const int RAPIDSPEED = 30;

    int rScore = 0;
    int lScore = 0;

    window.clear();
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }


        if (rScore == 5) {
            window.clear();
            winMessage.setPosition(400, 300);
            winMessage.setString("Right Player Win!!!");
            window.draw(winMessage);
            window.display();
            Sleep(2000);
            window.close();
        }
        if (lScore == 5) {
            window.clear();
            winMessage.setPosition(400, 300);
            winMessage.setString("Left Player Win!!!");
            window.draw(winMessage);
            window.display();
            Sleep(2000);
            window.close();
        }
        if (ballGoPosY < 0)DirectY = 0;
        if (ballGoPosY > (800 - 50))DirectY = 1;
        if (ballGoPosX < (LPX + 50) && ballGoPosY>leftGoPosY && ballGoPosY < (leftGoPosY + 175)) { 
            DirectX = 1;
            if (BALLSPEED <= MAXBALLSPEED)BALLSPEED += SPEEDUP;
        }
        if (ballGoPosX > (RPX - 50) && ballGoPosY > rightGoPosY && ballGoPosY < (rightGoPosY + 175)) { 
            DirectX = 0; 
            if (BALLSPEED <= MAXBALLSPEED)BALLSPEED += SPEEDUP;
        }


        ((DirectX == 1) ? ballGoPosX += BALLSPEED : ballGoPosX -= BALLSPEED);
        ((DirectY == 1) ? ballGoPosY -= BALLSPEED : ballGoPosY += BALLSPEED);

        if (ballGoPosX > 1500) {
            lScore++;
            ballGoPosY = 400;
            ballGoPosX = 600;
            DirectX = 1;
            DirectY = 1;
            BALLSPEED = 10;
        }
        else if (ballGoPosX < 0)
        {
            rScore++;
            ballGoPosY = 400;
            ballGoPosX = 600;
            DirectX = 1;
            DirectY = 1;
            BALLSPEED = 10;
        }


        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (leftGoPosY > UPBORDER) leftGoPosY -= RAPIDSPEED;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            if (leftGoPosY < DOWNBORDER) leftGoPosY += RAPIDSPEED;
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (rightGoPosY > UPBORDER) rightGoPosY -= RAPIDSPEED;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (rightGoPosY < DOWNBORDER) rightGoPosY += RAPIDSPEED;
        }


        leftStick.setPosition(LPX, leftGoPosY);
        rightStick.setPosition(RPX, rightGoPosY);
        ball.setPosition(ballGoPosX, ballGoPosY);
        leftMessage.setPosition(600, 20);
        rightMessage.setPosition(825, 20);

        wall.setPosition(725, 0);

        leftMessage.setString(to_string(lScore));
        rightMessage.setString(to_string(rScore));

        window.clear();

        //window.draw(backG);
        window.draw(ball);
        window.draw(wall);
        window.draw(leftStick);
        window.draw(rightStick);
        window.draw(leftMessage);
        window.draw(rightMessage);
        window.display();
    }
    return 0;
}