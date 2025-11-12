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
#include <string.h>
#define MAX(a, b) ((a)>(b)? (a) : (b))
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef enum telaAtual {MENU, ESCOLHATIMES, ESCOLHAPLAYERS} telaAtual;

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
    //bool botaoApertado = false;
    
    Vector2 ponteiroMouse = {0.0f, 0.0f};
    Rectangle botao1 = {565, screenHeight*0.45, 150, 70};
    Rectangle botao2 = {540, screenHeight* 0.58, 200, 70};
    Rectangle botaoVoltar = {970, 870, 200, 70};

    //Armazenar texto salvo
    char times[21] = "\0";
    int posChar = 0; //posição atual no buffer

    //------------------------------------------------------------------------//

    SetTargetFPS(60);               // Set our game to run at 144 frames-per-second
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

        // --- BOTÃO 2 (PLAYERS) ---
        if (CheckCollisionPointRec(ponteiroMouse, botao2))
        {
            estadoBotao2 = 1;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoBotao2 = 2;
                PlaySound(fxButton);
                telaJogo = ESCOLHAPLAYERS; // muda pra tela dos players
            }
        }
        else estadoBotao2 = 0;
        
        //botao de voltar
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



        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            Color textoBotao1 = (estadoBotao1 > 0) ? WHITE : RED;
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


                //texto do menu
                DrawText("BAD FALLEN", xMenu, screenHeight*0.25, 75, RED);
                DrawText("TIMES", x1, screenHeight*0.4723, 35, textoBotao1);
                break;
            
            case ESCOLHATIMES:
                ClearBackground(RAYWHITE);//muda background pra branco






                //captura as teclas
                int tecla = GetCharPressed();

                while (tecla > 0){
                    if ((tecla >= 32) && (tecla <=125) && (posChar < 22)){
                        times[posChar] = (char)tecla;
                        posChar++;
                        times[posChar] = '\0';
                    }//if 
                    
                    tecla = GetCharPressed();
                    
                }//capturar as escritas
                
                //apagar com o Backspace
                if (IsKeyPressed(KEY_BACKSPACE)){
                    posChar--;
                    if (posChar < 0) posChar = 0;
                    times[posChar] = '\0'; 
                }
                
                
                
                DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                DrawText("Digite um time: ", 30, 40, 45, LIGHTGRAY);
                DrawText(times, 338, 40, 45, RED);  
                DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);  
                break;
                
                case ESCOLHAPLAYERS:
                ClearBackground(RAYWHITE);//muda background pra branco
                DrawText("Digite um jogador: ", 30, 40, 45, LIGHTGRAY);//desenha o texto na posicao fornecida
                DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);//desenha um retangulo arredondado na posicao fornecida
                DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);//desenha o texto na posicao fornecida    
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
