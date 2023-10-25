#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "Character.h"
#include "Character.cpp"

using namespace std;

int main(void)
{
    InitWindow(1600, 900, "Raylib - Part 2");
    SetTargetFPS(30);
    int target = 0;
    int timer = 0;
    int generations = 1;
    bool hit = true;
    int aliveBCount = 10;

    Character characters[10];
    for (int i = 0; i < 10; i++)
    {
        if(i<5)
            characters[i] = Character((float)(rand() % 1400 + 100), (float)(rand() % 700 + 100),0);
        else
            characters[i] = Character((float)(rand() % 1400 + 100), (float)(rand() % 700 + 100),1);
    }
    Food foods[50];
    for (int i = 0; i < 50; i++)
    {
        foods[i].location = (Vector2){ (float)(rand() % 1400 + 100), (float)(rand() % 700 + 100) };
        foods[i].isCollected = false;
    }

    Image imgH = LoadImage("Resources/bunny.png");
    Texture2D textureH = LoadTextureFromImage(imgH);
    Rectangle rectangleH = { 0,0,textureH.width,textureH.height };
    Vector2 centerH = (Vector2){ textureH.width / 15,textureH.height / 15 };

    Image imgT = LoadImage("tortoise.png");
    Texture2D textureT = LoadTextureFromImage(imgT);
    Rectangle rectangleT = { 0,0,textureT.width,textureT.height };
    Vector2 centerT = (Vector2){ textureT.width / 8,textureT.height / 8 };

    Image imgM = LoadImage("mutant.png");
    Texture2D textureM = LoadTextureFromImage(imgM);
    Rectangle rectangleM = { 0,0,textureM.width,textureM.height };
    Vector2 centerM = (Vector2){ textureM.width/4,textureM.height/4 };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        if (aliveBCount <= 0)
        {
            DrawText("WINNER!", 630, 230, 80, BLACK);
            if (characters[0].type == 0)
            {
                DrawCircle(characters[0].location.x, characters[0].location.y, characters[0].grab, Fade(PINK, 0.3f));
                DrawCircleLines(characters[0].location.x, characters[0].location.y, characters[0].grab, Fade(PINK, 0.9f));
                DrawTexturePro(textureH, rectangleH, (Rectangle){characters[0].location.x,characters[0].location.y,rectangleH.width / 7.5f,rectangleH.height / 7.5f }, centerH, characters[0].angle, WHITE);
                characters[0].seek();
                characters[0].update();
                DrawTexturePro(textureH, rectangleH, (Rectangle ){ 450,330,rectangleH.width,rectangleH.height}, (Vector2){0,0}, 0, WHITE);
                DrawText("HARE", 830, 360, 60, PINK);
                std::string txt = "Speed: " + std::to_string((int)characters[0].maxspeed);
                DrawText(txt.c_str(), 800, 440, 40, PINK);
                txt = "Grab Range: " + std::to_string((int)characters[0].grab);
                DrawText(txt.c_str(), 800, 485, 40, PINK);
                float rTime = 2 / characters[0].rechargeRate;
                DrawText(TextFormat("Recharge Time: %.2f", rTime), 800, 530, 40, PINK);
            } else if (characters[0].type == 1)
            {
                DrawCircleLines(characters[0].location.x, characters[0].location.y, characters[0].vision, Fade(GREEN, 0.9f));
                DrawTexturePro(textureT, rectangleT, (Rectangle){ characters[0].location.x,characters[0].location.y,rectangleT.width / 4.0f,rectangleT.height / 4.0f }, centerT, characters[0].angle, WHITE);
                characters[0].seek();
                characters[0].update();
                DrawTexturePro(textureT, rectangleT, (Rectangle){ 500,360,rectangleT.width * 2.0f,rectangleT.height *2.0f}, (Vector2){ 0,0 }, 0, WHITE);
                DrawText("TORTOISE", 760, 400, 60, GREEN);
                std::string txt = "Speed: " + std::to_string((int)characters[0].maxspeed);
                DrawText(txt.c_str(), 760, 480, 40, GREEN);
                txt = "Vision Range: " + std::to_string((int)characters[0].vision);
                DrawText(txt.c_str(), 760, 525, 40, GREEN);
            }
            else {
                DrawCircleLines(characters[0].location.x, characters[0].location.y, characters[0].vision, Fade(YELLOW, 0.9f));
                DrawCircle(characters[0].location.x, characters[0].location.y, (characters[0].recharge / 60) * characters[0].grab, Fade(YELLOW, 0.3f));
                DrawTexturePro(textureM, rectangleM, (Rectangle){ characters[0].location.x,characters[0].location.y,rectangleM.width / 2.0f,rectangleM.height / 2.0f }, centerM, characters[0].angle, WHITE);
                characters[0].seek();
                characters[0].update();
                DrawTexturePro(textureM, rectangleM, (Rectangle){ 450,330,rectangleM.width * 3.5f,rectangleM.height *3.5f }, (Vector2){ 0,0 }, 0, WHITE);
                DrawText("MUTANT", 830, 360, 60, YELLOW);
                std::string txt = "Speed: " + std::to_string((int)characters[0].maxspeed);
                DrawText(txt.c_str(), 800, 440, 40, YELLOW);
                txt = "Grab Range: " + std::to_string((int)characters[0].grab);
                DrawText(txt.c_str(), 800, 485, 40, YELLOW);
                txt = "Vision Range: " + std::to_string((int)characters[0].vision);
                DrawText(txt.c_str(), 800, 530, 40, YELLOW);
            }
        }
        else {
            if (timer < 90)
            {
                for (int i = 0; i < aliveBCount; i++)
                {
                    if (characters[i].alive)
                    {
                        if (characters[i].alive && characters[i].type == 0)
                        {
                            DrawCircle(characters[i].location.x, characters[i].location.y, (characters[i].recharge / 60) * characters[i].grab, Fade(PINK, 0.3f));
                            DrawCircleLines(characters[i].location.x, characters[i].location.y, characters[i].grab, Fade(PINK, 0.9f));
                            DrawTexturePro(textureH, rectangleH, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleH.width / 7.5f,rectangleH.height / 7.5f }, centerH, characters[i].angle, WHITE);
                        }

                        if (characters[i].alive && characters[i].type == 1)
                        {
                            DrawCircleLines(characters[i].location.x, characters[i].location.y, characters[i].vision, Fade(GREEN, 0.9f));
                            DrawTexturePro(textureT, rectangleT, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleT.width / 4.0f,rectangleT.height / 4.0f }, centerT, characters[i].angle, WHITE);
                        }
                        if (characters[i].alive && characters[i].type == 2)
                        {
                            DrawCircle(characters[i].location.x, characters[i].location.y, (characters[i].recharge / 60) * characters[i].grab, Fade(YELLOW, 0.3f));
                            DrawCircleLines(characters[i].location.x, characters[i].location.y, characters[i].vision, Fade(YELLOW, 0.9f));
                            DrawTexturePro(textureM, rectangleM, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleM.width / 2.0f,rectangleM.height / 2.0f }, centerM, characters[i].angle, WHITE);
                        }
                        if (characters[i].mutated)
                        {
                            if (timer % 2 == 0)
                            {
                                DrawTexturePro(textureM, rectangleM, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleM.width / 2.0f,rectangleM.height / 2.0f }, centerM, characters[i].angle, YELLOW);
                            }
                            else {
                                DrawTexturePro(textureM, rectangleM, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleM.width / 2.0f,rectangleM.height / 2.0f }, centerM, characters[i].angle, WHITE);
                            }
                        }
                        if (characters[i].promoted)
                        {
                            if (timer % 2 == 0)
                            {
                                if(characters[i].type == 0)
                                    DrawTexturePro(textureH, rectangleH, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleH.width / 7.5f,rectangleH.height / 7.5f }, centerH, characters[i].angle, BLUE);
                                else if (characters[i].type == 1)
                                    DrawTexturePro(textureT, rectangleT, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleT.width / 4.0f,rectangleT.height / 4.0f }, centerT, characters[i].angle, BLUE);
                                else
                                    DrawTexturePro(textureM, rectangleM, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleM.width / 2.0f,rectangleM.height / 2.0f }, centerM, characters[i].angle, BLUE);
                            }
                            else {
                                if (characters[i].type == 0)
                                    DrawTexturePro(textureH, rectangleH, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleH.width / 7.5f,rectangleH.height / 7.5f }, centerH, characters[i].angle, WHITE);
                                else if (characters[i].type == 1)
                                    DrawTexturePro(textureT, rectangleT, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleT.width / 4.0f,rectangleT.height / 4.0f }, centerT, characters[i].angle, WHITE);
                                else
                                    DrawTexturePro(textureM, rectangleM, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleM.width / 2.0f,rectangleM.height / 2.0f }, centerM, characters[i].angle, WHITE);
                            }
                        }
                    }
                }
                DrawText(TextFormat("Generation: %02i", generations), 500, 400, 80, BLUE);
            }
            else {
                ClearBackground(WHITE);
                for (int i = 0; i < 50; i++)
                {
                    if (!foods[i].isCollected)
                        DrawCircle(foods[i].location.x, foods[i].location.y, 5, RED);
                }

                for (int i = 0; i < aliveBCount; i++)
                {

                    if (characters[i].alive && characters[i].type == 0)
                    {
                        DrawCircle(characters[i].location.x, characters[i].location.y, (characters[i].recharge / 60) * characters[i].grab, Fade(PINK, 0.3f));
                        DrawCircleLines(characters[i].location.x, characters[i].location.y, characters[i].grab, Fade(PINK, 0.9f));
                        DrawTexturePro(textureH, rectangleH, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleH.width / 7.5f,rectangleH.height / 7.5f }, centerH, characters[i].angle, WHITE);
                        DrawTexturePro(textureH, rectangleH, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleH.width / 7.5f,rectangleH.height / 7.5f }, centerH, characters[i].angle, Fade(RED, characters[i].food / 10));
                        characters[i].seek();
                        characters[i].update();
                        for (int j = 0; j < 50; j++)
                        {
                            float deltaX = characters[i].location.x - foods[j].location.x;
                            float deltaY = characters[i].location.y - foods[j].location.y;
                            if (sqrtf((deltaX * deltaX) + (deltaY * deltaY)) <= characters[i].grab && characters[i].recharge >= 60 && !foods[j].isCollected)
                            {
                                foods[j].isCollected = true;
                                characters[i].recharge = 0;
                                characters[i].food++;
                            }

                        }
                        if (characters[i].recharge < 60)
                        {
                            characters[i].recharge += characters[i].rechargeRate;
                            if (characters[i].recharge > 60)
                                characters[i].recharge = 60;
                        }
                    }

                    if (characters[i].alive && characters[i].type == 1)
                    {
                        DrawCircleLines(characters[i].location.x, characters[i].location.y, characters[i].vision, Fade(GREEN, 0.9f));
                        DrawTexturePro(textureT, rectangleT, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleT.width / 4.0f,rectangleT.height / 4.0f }, centerT, characters[i].angle, WHITE);
                        DrawTexturePro(textureT, rectangleT, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleT.width / 4.0f,rectangleT.height / 4.0f }, centerT, characters[i].angle, Fade(GREEN, characters[i].food / 10));
                        characters[i].update(foods);
                        for (int j = 0; j < 50; j++)
                        {
                            float deltaX = characters[i].location.x - foods[j].location.x;
                            float deltaY = characters[i].location.y - foods[j].location.y;
                            if (sqrtf((deltaX * deltaX) + (deltaY * deltaY)) <= characters[i].grab && !foods[j].isCollected)
                            {
                                foods[j].isCollected = true;
                                characters[i].food++;
                            }

                        }
                        if (characters[i].recharge < 60)
                            characters[i].recharge += characters[i].rechargeRate;
                    }
                    if (characters[i].alive && characters[i].type == 2)
                    {
                        DrawCircleLines(characters[i].location.x, characters[i].location.y, characters[i].vision, Fade(YELLOW, 0.9f));
                        DrawCircle(characters[i].location.x, characters[i].location.y, (characters[i].recharge / 60) * characters[i].grab, Fade(YELLOW, 0.3f));
                        DrawTexturePro(textureM, rectangleM, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleM.width / 2.0f,rectangleM.height / 2.0f }, centerM, characters[i].angle, WHITE);
                        DrawTexturePro(textureM, rectangleM, (Rectangle){ characters[i].location.x,characters[i].location.y,rectangleM.width / 2.0f,rectangleM.height / 2.0f }, centerM, characters[i].angle, Fade(YELLOW, characters[i].food / 10));
                        characters[i].update(foods);
                        for (int j = 0; j < 50; j++)
                        {
                            float deltaX = characters[i].location.x - foods[j].location.x;
                            float deltaY = characters[i].location.y - foods[j].location.y;
                            if (sqrtf((deltaX * deltaX) + (deltaY * deltaY)) <= characters[i].grab && !foods[j].isCollected)
                            {
                                foods[j].isCollected = true;
                                characters[i].food++;
                            }

                        }
                        if (characters[i].recharge < 60)
                            characters[i].recharge += characters[i].rechargeRate;
                    }
                    std::string txt = std::to_string((int)characters[i].food);
                    DrawText(txt.c_str(), characters[i].location.x + 15, characters[i].location.y + 15, 20, BLACK);
                }
            }
            timer++;

            if (timer >= 390)
            {
                timer = 0;
                for (int i = 0; i < aliveBCount - 1; i++)
                {
                    for (int j = 0; j < aliveBCount - i - 1; j++)
                    {
                        if (characters[j + 1].food > characters[j].food)
                        {
                            Character temp = characters[j];
                            characters[j] = characters[j + 1];
                            characters[j + 1] = temp;
                        }
                    }
                }

                aliveBCount--;
                characters[aliveBCount].alive = false;

                for (int i = 0; i < aliveBCount; i++)
                {
                    characters[i].food = 0;
                    characters[i].mutated = false;
                    characters[i].promoted = true;
                    if (i == 0)
                    {
                        characters[i].maxspeed *= 1.5;
                        characters[i].maxforce *= 1.5;
                        characters[i].rechargeRate *= 1.5;
                        characters[i].vision *= 1.5;
                        characters[i].grab *= 1.5;
                    } else if (i == 1)
                    {
                        characters[i].maxspeed *= 1.25f;
                        characters[i].maxforce *= 1.25f;
                        characters[i].rechargeRate *= 1.25f;
                        characters[i].vision *= 1.25;
                        characters[i].grab *= 1.25;

                    } else if (i == 2)
                    {
                        characters[i].maxspeed *= 1.2f;
                        characters[i].maxforce *= 1.2f;
                        characters[i].rechargeRate *= 1.2f;
                        characters[i].vision *= 1.2;
                        characters[i].grab *= 1.2;

                    } else if (i == 3)
                    {
                        characters[i].maxspeed *= 1.1f;
                        characters[i].maxforce *= 1.1f;
                        characters[i].rechargeRate *= 1.1f;
                        characters[i].vision *= 1.1;
                        characters[i].grab *= 1.1;
                    }
                    else {
                        characters[i].promoted = false;
                    }
                }

                for (int i = 0; i < aliveBCount; i++)
                {
                    for (int j = 0; j < aliveBCount; j++)
                    {
                        if (characters[i].type == 0 && characters[j].type == 1 && characters[i].alive && characters[j].alive)
                        {
                            float deltaX = characters[i].location.x - characters[j].location.x;
                            float deltaY = characters[i].location.y - characters[j].location.y;
                            if (sqrtf((deltaX * deltaX) + (deltaY * deltaY)) <= 100)
                            {
                                Character temp = Character(characters[i].location.x, characters[i].location.y, 2, characters[i], characters[j]);
                                characters[i] = temp;
                                characters[j].alive = false;
                                aliveBCount--;
                                for (int k = j; k < 9; k++)
                                {
                                    characters[k] = characters[k + 1];
                                }
                            }
                        }
                    }
                }

                for (int i = 0; i < 50; i++)
                {
                    foods[i].location = (Vector2){(float)(rand() % 1550 + 25), (float)(rand() % 850 + 25) };
                    foods[i].isCollected = false;
                }
                generations++;
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}