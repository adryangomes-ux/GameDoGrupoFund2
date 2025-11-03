/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute 'raylib_compile_execute' script
*   Note that compiled executable is placed in the same folder as .c file
*
*   To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
*   Web version of the program is generated in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2013-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 960;

    InitWindow(screenWidth, screenHeight, "bad fallen");
    Texture2D menu = LoadTexture("fallen.jpg");
    
    //centralizar o texto "times" no eixo x
    int larguraJanela = GetScreenWidth();
    int larguraTexto1 = MeasureText("TIMES", 35);
    int x1 = (larguraJanela - larguraTexto1) / 2;

    //centralizar o texto "players" no eixo x;
    int larguraTexto2 = MeasureText("PLAYERS", 35);
    int x2 = (larguraJanela - larguraTexto2) / 2;

    SetTargetFPS(144);               // Set our game to run at 144 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            //faz a imagem cobrir a janela toda
            DrawTexturePro(menu,
                           (Rectangle){ 0, 0, menu.width, menu.height },
                           (Rectangle){ 0, 0, screenWidth, screenHeight },
                           (Vector2){ 0, 0 }, 0.0f, WHITE);

            //retangulo redondo pra ficar em volta do texto do menu
            DrawRectangleRounded((Rectangle){565, screenHeight*0.45, 150, 70}, 2, 3, BLACK);
            DrawRectangleRounded((Rectangle){565, screenHeight* 0.55, 200, 70}, 2, 3, BLACK);

            //texto do menu
            DrawText("BAD FALLEN", 430, screenHeight*0.25, 75, RED);
            DrawText("TIMES", x1, screenHeight*0.4723, 35, RED);
            DrawText("PLAYERS", x2, screenHeight*0.6, 35, RED);


            EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(menu);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}