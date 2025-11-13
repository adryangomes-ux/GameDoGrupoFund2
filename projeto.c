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
#include <ctype.h>

#define MAX_LINHAS 50
#define MAX_COLUNAS 5
#define MAX_TEXTO 128
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef enum telaAtual {MENU, ESCOLHADIFICULDADE,ESCOLHATIMES} telaAtual;
typedef enum Dificuldade {FACIL=1, MEDIO, DIFICIL} Dificuldade;

typedef struct {
    char time[MAX_TEXTO];
    char pais[MAX_TEXTO];
    char jogador[MAX_TEXTO];
    char destaque[MAX_TEXTO];
    char dica[MAX_TEXTO];
} TimeCSV;

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = (char)tolower(str[i]);
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 960;

    InitWindow(screenWidth, screenHeight, "bad fallen");
    InitAudioDevice();      // Initialize audio device
    //sons e texturas
    Texture2D menu = LoadTexture("imagens/fallen.jpg");
    Sound fxButton = LoadSound("audio/selecao.wav"); 
    Sound acertarPrimeira = LoadSound("audio/grafite.wav");


    //centralizar o texto "times" no eixo x
    int larguraJanela = GetScreenWidth();
    int larguraTexto1 = MeasureText("PRESSIONE ESPAÇO PARA INICIAR", 35);
    int x1 = (larguraJanela - larguraTexto1) / 2;

    //centraliza os textos da tela de escolha de dificuldade
    int larguraTextoDificuldade = MeasureText("ESCOLHA A DIFICULDADE", 60);
    int xDificuldade = (larguraJanela - larguraTextoDificuldade) / 2;
    int larguraTextoFacil = MeasureText("FÁCIL", 40);
    int larguraTextoMedio = MeasureText("MÉDIO", 40);
    int larguraTextoDificil = MeasureText("DIFÍCIL", 40);
    int xFacil = (larguraJanela - larguraTextoFacil) / 2;
    int xMedio = (larguraJanela - larguraTextoMedio) / 2;
    int xDificil = (larguraJanela - larguraTextoDificil) / 2;


    
    //centralizar o titulo do jogo
    int larguraTextoMenu = MeasureText("BAD FALLEN", 75);
    int xMenu = (larguraJanela - larguraTextoMenu) / 2;    
    
    
    telaAtual telaJogo = MENU;
    Dificuldade dificuldade;

    //checa estado do botao
    bool estadoBotao1 = 0; //0 - desativado, 1 - mouse em cima, 2 - apertado
    bool estadoBotaoVoltar = 0;
    bool estadoBotaoFacil = 0;
    bool estadoBotaoMedio = 0;
    bool estadoBotaoDificil = 0;
    bool estadoMenu = false;
    bool acertou = false;
    bool enviar = false;

    Vector2 ponteiroMouse = {0.0f, 0.0f};
    Rectangle botao1 = {300, screenHeight*0.48, 680, 70};
    Rectangle botaoVoltar = {970, 870, 200, 70};
    Rectangle botaoFacil = {xFacil - 43, 230, 200, 70};
    Rectangle botaoMedio = {xMedio - 38, 385, 200, 70};
    Rectangle botaoDificil = {xDificil - 27, 533, 200, 70};


    //Armazenar texto salvo
    int count = 0; //contador
    int contadorTentativa = 0;
    int pos = 0; //posição atual no buffer
    
    TimeCSV timesCode[MAX_TEXTO];//para poder ler o arquivo csv
    
    FILE *arquivo = fopen("arquivos/TimesDicas.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo CSV!\n");
        CloseWindow();
        return 1;
    }//caso der erro
    
    char escritaTimes[MAX_TEXTO] = "\0";
    
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

    // escolhe um time aleatório APÓS carregar o CSV
    int indice = count;
    if (indice <= 0) {
        printf("Nenhuma linha lida do CSV.\n");
        CloseWindow();
        return 1;
    }
    int indiceAleatorio = GetRandomValue(0, indice - 1);
    TimeCSV timeSorteado = timesCode[indiceAleatorio];


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
        if (IsKeyPressed(KEY_SPACE) && estadoMenu == false)
        {
            estadoMenu = true;
            estadoBotao1 = 1;
            PlaySound(fxButton);
            telaJogo = ESCOLHADIFICULDADE;
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
                telaJogo = ESCOLHADIFICULDADE;
            } 
        }
        else estadoBotaoVoltar = 0;
        

        //BOTAO DIFICULDADE FACIL
        if (CheckCollisionPointRec(ponteiroMouse, botaoFacil))
        {
            estadoBotaoFacil = 1;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoBotaoFacil = 2;
                dificuldade = FACIL;
                PlaySound(fxButton);
                telaJogo = ESCOLHATIMES;
            }
            
        }
        else estadoBotaoFacil = 0;

        //BOTAO DIFICULDADE MEDIA
        if (CheckCollisionPointRec(ponteiroMouse, botaoMedio))
        {
            estadoBotaoMedio = 1;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoBotaoMedio = 2;
                dificuldade = MEDIO;
                PlaySound(fxButton);
                telaJogo = ESCOLHATIMES;
            }
            
        }
        else estadoBotaoMedio = 0;

        //BOTAO DIFICULDADE DIFICIL
        if (CheckCollisionPointRec(ponteiroMouse, botaoDificil))
        {
            estadoBotaoDificil = 1;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                estadoBotaoDificil = 2;
                dificuldade = DIFICIL;
                PlaySound(fxButton);
                telaJogo = ESCOLHATIMES;
            }
            
        }
        else estadoBotaoDificil = 0;


        //tela de jogo dos modos
        switch (telaJogo)
        {
        case ESCOLHATIMES:
            int tecla = GetCharPressed();
            
            while (tecla > 0){
                if ((tecla >= 32) && (tecla <=125) && (pos < 22)){
                    escritaTimes[pos] = (char)tecla;
                    pos++;
                    escritaTimes[pos] = '\0';
                }//if 
            tecla = GetCharPressed();
                
            }//capturar as escritas
            
            //apagar com o Backspace
            if (IsKeyPressed(KEY_BACKSPACE)){
                pos--;
                if (pos < 0) pos = 0;
                escritaTimes[pos] = '\0'; 
            }                    
                
                
            if (IsKeyPressed(KEY_ENTER))
            {
                enviar = true;
            }
            
            if (enviar)
            {
                char chuteTemp[MAX_TEXTO];
                strcpy(chuteTemp, escritaTimes);
                toLowerCase(chuteTemp);
                if (_stricmp(chuteTemp, timeSorteado.time) == 0 && contadorTentativa == 0)
                {
                    acertou = true;
                    PlaySound(acertarPrimeira);
                }else{
                    contadorTentativa++;
                }
                enviar = false;

                escritaTimes[0] = '\0';
                pos = 0;
            }

            break;
        
        default:
            break;
        }

        
                    
        
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            Color textoBotao1 = (estadoBotao1 > 0) ? WHITE : RED;
            Color textoBotaoVoltar = (estadoBotaoVoltar > 0) ? WHITE : RED;
            Color textoBotaoFacil = (estadoBotaoFacil > 0) ? WHITE : RED;
            Color textoBotaoMedio = (estadoBotaoMedio > 0) ? WHITE : RED;
            Color textoBotaoDificil = (estadoBotaoDificil > 0) ? WHITE : RED;

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
                DrawText("PRESSIONE ESPAÇO PARA INICIAR", x1, screenHeight*0.5, 35, textoBotao1);

                break;
                    
            case ESCOLHADIFICULDADE:
                ClearBackground(RAYWHITE);
            
                //texto pra selecionar a dificuldade + botao de voltar
                DrawText("ESCOLHA A DIFICULDADE", xDificuldade, 10, 60, RED);
                DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);
                
                //botao das dificuldades
                DrawRectangleRounded((Rectangle)botaoFacil, 2, 3, BLACK);
                DrawRectangleRounded((Rectangle)botaoMedio, 2, 3, BLACK);
                DrawRectangleRounded((Rectangle)botaoDificil, 2, 3, BLACK);

                //texto das dificuldades
                DrawText("FÁCIL", xFacil, 250, 40, textoBotaoFacil);
                DrawText("MÉDIO", xMedio, 400, 40, textoBotaoMedio);
                DrawText("DIFÍCIL", xDificil, 550, 40, textoBotaoDificil);
                break;

            case ESCOLHATIMES:
                switch (dificuldade)
                {
                case FACIL:
                
                if (acertou)
                {
                    DrawText("Parabéns, você acertou de primeira!", 300, 300, 40, RED);
                }
                
                
                if (contadorTentativa == 1)
                {
                    DrawText(timesCode[indiceAleatorio].pais, 80, 600, 40, BLACK);
                }else if (contadorTentativa == 2)
                {
                    DrawText(timesCode[indiceAleatorio].jogador, 80, 650, 40, BLACK);
                }else if (contadorTentativa == 3)
                {
                    DrawText(timesCode[indiceAleatorio].destaque, 80, 700, 40, BLACK);
                }else if (contadorTentativa == 4)
                {
                    DrawText(timesCode[indiceAleatorio].dica, 80, 750, 32, BLACK);
                }
                
                
                
                
                
                

                DrawText(timesCode[indiceAleatorio].time, 300, 300, 60, RED);

                DrawText(TextFormat("Time sorteado: %s", timeSorteado.time), 100, 100, 30, BLACK);
                DrawText("Digite um time:", 20, 10, 40, LIGHTGRAY);
                DrawText(escritaTimes, 300, 10, 40, BLACK);
                DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);
                    break;
                
                case MEDIO:
                if (acertou && contadorTentativa == 0)
                {
                    DrawText("Parabéns, você acertou de primeira!", 300, 300, 40, RED);
                }
                
                DrawText(timesCode[indiceAleatorio].time, 300, 300, 60, RED);
                    
                DrawText(TextFormat("Time sorteado: %s", timeSorteado.time), 100, 100, 30, BLACK);
                DrawText("Digite um time:", 20, 10, 40, LIGHTGRAY);
                DrawText(escritaTimes, 300, 10, 40, BLACK);
                DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);
                    
                break;
                case DIFICIL:
                
                //captura as teclas
                DrawText(TextFormat("%02d", contadorTentativa), 400, 800, 45, LIGHTGRAY);

                if (acertou && contadorTentativa == 0)
                {
                    DrawText("Parabéns, você acertou de primeira!", 300, 300, 40, RED);
                }
                
                DrawText(timesCode[indiceAleatorio].time, 300, 300, 60, RED);
                    
                DrawText(TextFormat("Time sorteado: %s", timeSorteado.time), 100, 100, 30, RED);
                DrawText("Digite um time:", 20, 10, 40, LIGHTGRAY);
                DrawText(escritaTimes, 300, 10, 40, RED);
                DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);

                   break;
                default:
                    break;
                }

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
