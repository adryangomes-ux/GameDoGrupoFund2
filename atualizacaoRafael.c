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
#include <stdio.h>
#include <stdlib.h>
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef enum telaAtual {MENU, ESCOLHATIMES} telaAtual;
typedef enum Dificuldade {FACIL=1, MEDIO, DIFICIL} Dificuldade;

typedef struct
{
    char Times[20];
    char Dicas[50];
    Dificuldade dif; //dif = dificuldade só que curtinho
}PerguntaTimes;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 960;

    InitAudioDevice();      // Initialize audio device
    InitWindow(screenWidth, screenHeight, "bad fallen");
    Texture2D menu = LoadTexture("imagens/fallen.jpg");
    Sound fxButton = LoadSound("audio/selecao.wav"); 

    //separado para arquivo csv
    FILE *arqTimes = fopen("TimeseDicas.csv", "wb");



    //centralizar o texto "times" no eixo x
    int larguraJanela = GetScreenWidth();
    int larguraTexto1 = MeasureText("TIMES", 35);
    int x1 = (larguraJanela - larguraTexto1) / 2;

    //centralizar o texto "players" no eixo x;
    int larguraTexto2 = MeasureText("PLAYERS", 35);
    int x2 = (larguraJanela - larguraTexto2) / 2;
    telaAtual telaJogo = MENU;

    //centralizar o titulo do jogo
    int larguraTextoMenu = MeasureText("BAD FALLEN", 75);
    int xMenu = (larguraJanela - larguraTextoMenu) / 2;    

    //checa estado do botao
    bool estadoBotao1 = 0; //0 - desativado, 1 - mouse em cima, 2 - apertado
    bool estadoBotao2 = 0;
    bool estadoBotaoVoltar = 0;
    
    Vector2 ponteiroMouse = {0.0f, 0.0f};
    Rectangle botao1 = {565, screenHeight*0.45, 150, 70};
    Rectangle botao2 = {540, screenHeight* 0.58, 200, 70};
    Rectangle botaoVoltar = {970, 870, 200, 70};

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        ponteiroMouse = GetMousePosition();

        
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // --- BOTÃO 1 (TIMES) ---
        if (CheckCollisionPointRec(ponteiroMouse, botao1))
        {
            estadoBotao1 = 1;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoBotao1 = 2;
                PlaySound(fxButton);
                telaJogo = ESCOLHATIMES; // muda pra tela dos times
            }
        }
        else estadoBotao1 = 0;
        
        //botao de voltar pro menu
        if (CheckCollisionPointRec(ponteiroMouse, botaoVoltar))
        {
            estadoBotaoVoltar = 1;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoBotaoVoltar = 2;
                PlaySound(fxButton);
                telaJogo = MENU;
            } 
        }
        else estadoBotaoVoltar = 0;

        //tela de jogo dos modos
        switch (telaJogo)
        {
        case ESCOLHATIMES:
            
            break;
        
        default:
            break;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            Color textoBotao1 = (estadoBotao1 > 0) ? WHITE : RED;
            Color textoBotao2 = (estadoBotao2 > 0) ? WHITE : RED;
            Color textoBotaoVoltar = (estadoBotaoVoltar > 0) ? WHITE : RED;
            ClearBackground(RAYWHITE);

            switch (telaJogo)
            {
            case MENU:
                //faz a imagem cobrir a janela toda
                DrawTexturePro(menu,
                            (Rectangle){ 0, 0, menu.width, menu.height },
                            (Rectangle){ 0, 0, screenWidth, screenHeight },
                            (Vector2){ 0, 0 }, 0.0f, WHITE);

                //retangulo redondo pra ficar em volta do texto do menu
                DrawRectangleRounded((Rectangle)botao1, 2, 3, BLACK);
                DrawRectangleRounded((Rectangle)botao2, 2, 3, BLACK);

                //texto do menu
                DrawText("BAD FALLEN", xMenu, screenHeight*0.25, 75, RED);
                DrawText("TIMES", x1, screenHeight*0.4723, 35, textoBotao1);
                DrawText("PLAYERS", x2, screenHeight*0.6, 35, textoBotao2);
                break;
            
            case ESCOLHATIMES:
                ClearBackground(RAYWHITE);//muda background pra branco
                DrawText("Digite um time: ", 30, 40, 45, LIGHTGRAY);
                DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);    
                break;

            default:
                break;
            
            }//switch
            DrawFPS(0,1);

            EndDrawing();
        //----------------------------------------------------------------------------------
    }//while
        // De-Initialization
        //--------------------------------------------------------------------------------------
        UnloadSound(fxButton);
        UnloadTexture(menu);
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
        
        return 0;
        
}//make
