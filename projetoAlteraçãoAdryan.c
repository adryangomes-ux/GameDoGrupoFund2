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

#define MAX_LINHAS 50
#define MAX_COLUNAS 5
#define MAX_TEXTO 128
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef enum telaAtual {MENU, ESCOLHATIMES, ESCOLHAPLAYERS} telaAtual;



typedef struct {
    char time[MAX_TEXTO];
    char pais[MAX_TEXTO];
    char jogador[MAX_TEXTO];
    char destaque[MAX_TEXTO];
    char dica[MAX_TEXTO];
} TimeCSV;








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
    telaAtual telaJogo = MENU;

    //centralizar o titulo do jogo
    int larguraTextoMenu = MeasureText("BAD FALLEN", 75);
    int xMenu = (larguraJanela - larguraTextoMenu) / 2;

    //checa estado do botao
    bool estadoBotao1 = 0; //0 - desativado, 1 - mouse em cima, 2 - apertado

    bool estadoBotaoVoltar = 0;
    //bool botaoApertado = false;
    Vector2 ponteiroMouse = {0.0f, 0.0f};
    Rectangle botao1 = {565, screenHeight*0.45, 150, 70};
    Rectangle botaoVoltar = {970, 870, 200, 70};





    //Armazenar texto salvo
    //int count = 0; //contador
    int pos = 0; //posição atual no buffer
    int count = 0;
    
    TimeCSV timesCode[MAX_TEXTO];//para poder ler o arquivo csv
    char times[MAX_TEXTO] = "\0";
    
    FILE *arquivo = fopen("arquivos/TimesDicas.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo CSV!\n");
        CloseWindow();
        return 1;
    }//caso der erro

    char linha[512];
    fgets(linha, sizeof(linha), arquivo); // Ignora o cabeçalho

    // Lê linha por linha
    while (fgets(linha, sizeof(linha), arquivo) && count < MAX_LINHAS) {
        // Remove quebra de linha
        linha[strcspn(linha, "\r\n")] = 0;

        // Quebra a linha em colunas
        char *token = strtok(linha, ",");
        int coluna = 0;

        while (token != NULL && coluna < MAX_COLUNAS) {
            switch (coluna) {
                case 0: strncpy(timesCode[count].time, token, MAX_TEXTO); break;
                case 1: strncpy(timesCode[count].pais, token, MAX_TEXTO); break;
                case 2: strncpy(timesCode[count].jogador, token, MAX_TEXTO); break;
                case 3: strncpy(timesCode[count].destaque, token, MAX_TEXTO); break;
                case 4: strncpy(timesCode[count].dica, token, MAX_TEXTO); break;
            }
            token = strtok(NULL, ",");
            coluna++;
        }
        count++;
    }

    fclose(arquivo);












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
                    if ((tecla >= 32) && (tecla <=125) && (pos < 22)){
                        times[pos] = (char)tecla;
                        pos++;
                        times[pos] = '\0';
                    }//if 
                    
                    tecla = GetCharPressed();
                    
                }//capturar as escritas
                
                //apagar com o Backspace
                if (IsKeyPressed(KEY_BACKSPACE)){
                    pos--;
                    if (pos < 0) pos = 0;
                    times[pos] = '\0'; 
                }

                int y = 80;
                for (int i = 0; i < count; i++) {
                DrawText(TextFormat("%2d. %s (%s) - %s", i + 1, timesCode[i].time, timesCode[i].pais, timesCode[i].jogador),60, y, 20, LIGHTGRAY);
                y += 25;
                if (y > GetScreenHeight() - 40) break; // Evita ultrapassar a tela
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
