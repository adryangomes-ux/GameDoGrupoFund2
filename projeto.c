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
*   Web version   of the program is generated in the same folder as .c file
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
#include "times.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef enum telaAtual {MENU, ESCOLHADIFICULDADE,ESCOLHATIMES} telaAtual;
typedef enum Dificuldade {FACIL=1, MEDIO, DIFICIL} Dificuldade;


void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++)
    str[i] = (char)tolower(str[i]);
}        

int main(void){
    //Armazenar texto salvo
    int count = 0; //contador
    int contadorTentativa = 0;
    int pos = 0; //posição atual no buffer
    int opcao;
    
    TimesCSV timesCode[MAX_LINHAS];//para poder ler o arquivo csv
    
    FILE *arquivoBin = fopen("arquivos/save.dat", "rb");
    FILE *arquivo;
    if (arquivoBin != NULL)
    {        
        
        
        char linha[512];
        fgets(linha, sizeof(linha), arquivoBin); // Ignora o cabeçalho
        
        // Lê linha por linha
        while (fgets(linha, sizeof(linha), arquivoBin) && count < MAX_LINHAS) {
            // Remove quebra de linha
            linha[strcspn(linha, "\r\n")] = 0;
            
            // Quebra a linha em colunas
            char *token = strtok(linha, ",");
            int coluna = 0;
            
            while (token != NULL && coluna < MAX_COLUNAS) {
                switch (coluna) {
                    case 1: strncpy(timesCode[count].pais, token, MAX_TEXTO); fread(&timesCode, sizeof(TimesCSV), 1, arquivo); break;
                    case 0: strncpy(timesCode[count].time, token, MAX_TEXTO); fread(&timesCode, sizeof(TimesCSV), 1, arquivo); break;
                    case 2: strncpy(timesCode[count].jogador, token, MAX_TEXTO); fread(&timesCode, sizeof(TimesCSV), 1, arquivo); break;
                    case 3: strncpy(timesCode[count].destaque, token, MAX_TEXTO); fread(&timesCode, sizeof(TimesCSV), 1, arquivo); break;
                    case 4: strncpy(timesCode[count].dica, token, MAX_TEXTO); fread(&timesCode, sizeof(TimesCSV), 1, arquivo); break;
                }
                token = strtok(NULL, ",");
                coluna++;
            }
            count++;
        }
        
        fclose(arquivoBin);
        
        
    }else{
        printf("Bem-vindo!");
        arquivo = fopen("arquivos/TimesDicas.csv", "r");
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

    }
    char escritaTimes[MAX_TEXTO] = "\0";
    
        
        // escolhe um time aleatório APÓS carregar o CSV
        int indice = count;
        if (indice <= 0) {
            printf("Nenhuma linha lida do CSV.\n");
            CloseWindow();
            return 1;
        }
        
        int indiceAleatorio = GetRandomValue(0, indice - 1);//gera um valor aleatorio para settar o time
        TimesCSV timeSorteado = timesCode[indiceAleatorio];
        //--------------------------------------------------------------------------------------
        
        
        
           do {//vai fazer enquanto
            printf("\n==== MENU ====\n");
            printf("1 - Inserir\n");
            printf("2 - Listar\n");
            printf("3 - Pesquisar\n");
            printf("4 - Editar\n");
            printf("5 - Excluir\n");
            printf("0 - Sair para o jogo\n");
            printf("Escolha: ");
            scanf("%d", &opcao);
            //getchar();
            
            switch (opcao) {
                case 1: inserir(timesCode, &count); break;
                case 2: listar(timesCode, count); break;
                case 3: pesquisar(timesCode, count); break;
                case 4: editar(timesCode, count); break;
                case 5: excluir(timesCode, &count); break;
            }
            
        } while (opcao != 0);//for diferente de zero
        
        SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
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
    Sound lesgo = LoadSound("audio/okletsgo.wav");
    SetSoundVolume(lesgo, 0.25f);
    Texture2D telaDif = LoadTexture("imagens/ancient/ancient1.png");
    Texture2D telaFacil = LoadTexture("imagens/dust2/dust3.png");
    Texture2D telaMedio = LoadTexture("imagens/anubis/anubis2.png");
    Texture2D telaHard = LoadTexture("imagens/golden/golden3.png");

    //centralizar o texto "times" no eixo x
    int larguraJanela = GetScreenWidth();
    int larguraTexto1 = MeasureText("PRESSIONE ESPAÇO PARA INICIAR", 35);
    int perdedor = MeasureText("VOCE É PESSIMO",60);
    int x1 = (larguraJanela - larguraTexto1) / 2;
    int xPerdedor = ((larguraJanela - perdedor) / 2) - 120;
    
    
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
    bool estadoBotaoDificuldade = 0;
    
    //outras variaveis booleanas
    bool estadoMenu = false;
    bool acertou = false;
    bool enviar = false;

    Vector2 ponteiroMouse = {0.0f, 0.0f};
    Rectangle botao1 = {300, screenHeight*0.48, 680, 70};
    Rectangle botaoVoltar = {970, 870, 200, 70};
    Rectangle botaoFacil = {xFacil - 43, 230, 200, 70};
    Rectangle botaoMedio = {xMedio - 38, 385, 200, 70};
    Rectangle botaoDificil = {xDificil - 27, 533, 200, 70};
    
    

    
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
            telaJogo = ESCOLHADIFICULDADE;
            PlaySound(lesgo);
        }
        else estadoBotao1 = 0;        
        
        
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
            case ESCOLHADIFICULDADE:
    
                //botao de voltar pro menu quando se está na tela de dificuldades
                if (CheckCollisionPointRec(ponteiroMouse, botaoVoltar))
                {
                    estadoBotaoDificuldade = 1;
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        estadoBotaoDificuldade = 2;
                        PlaySound(fxButton);
                        estadoMenu = false;
                        telaJogo = MENU;
                    }
                }
                else estadoBotaoDificuldade = 0;

                break;

            case ESCOLHATIMES:
            
            if(!acertou){

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
    
                    if (strcasecmp(chuteTemp, timeSorteado.time) == 0 && contadorTentativa == 0){
                        acertou = true;
                        PlaySound(acertarPrimeira);
                    }else if(strcasecmp(chuteTemp, timeSorteado.time) != 0){
                        contadorTentativa++;
                    }
    
                    if (strcasecmp(chuteTemp, timeSorteado.time) == 0 && contadorTentativa > 0)
                    {
                        acertou = true;
                    }
    
    
                    enviar = false;
                    
                    escritaTimes[0] = '\0';
                    pos = 0;
                }
            }
                  

            //botao de voltar pra tela de dificuldades
            if (CheckCollisionPointRec(ponteiroMouse, botaoVoltar))
            {
                estadoBotaoVoltar = 1;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    estadoBotaoVoltar = 2;
                    PlaySound(fxButton);
                    telaJogo = ESCOLHADIFICULDADE;
                    escritaTimes[0] = '\0';
                    pos = 0;
                } 
            }
            else estadoBotaoVoltar = 0;

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
        Color textoBotaoDificuldade = (estadoBotaoDificuldade > 0) ? WHITE : RED;

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
                    
                    DrawTexturePro(telaDif,
                    (Rectangle){ 0, 0, telaDif.width, telaDif.height },
                    (Rectangle){ 0, 0, screenWidth, screenHeight },
                    (Vector2){ 0, 0 }, 0.0f, WHITE);
                    
                    //texto pra selecionar a dificuldade + botao de voltar
                    DrawText("ESCOLHA A DIFICULDADE", xDificuldade, 10, 60, RED);
                    DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                    DrawText("VOLTAR", 996, 890, 35, textoBotaoDificuldade);
                    
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

                        DrawTexturePro(telaFacil,
                        (Rectangle){ 0, 0, telaFacil.width, telaFacil.height },
                        (Rectangle){ 0, 0, screenWidth, screenHeight },
                        (Vector2){ 0, 0 }, 0.0f, WHITE);

                        DrawText(TextFormat("%02d", contadorTentativa), 400, 800, 45, LIGHTGRAY);//desenha quantidade de tentativas
                        
                        if (acertou && contadorTentativa == 0)
                        {
                            DrawText("Parabéns, você acertou de primeira!", 300, 300, 40, RED);
                        }else if (acertou && contadorTentativa > 0)
                        {
                            DrawText("Parabéns, você acertou!", 300, 300, 40, RED);
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
                        }else if(contadorTentativa == 5 && acertou == false){
                            DrawText("VOCE É PESSIMO...",xPerdedor,300,80,BLUE);
                         
                            // int horario = GetTime();

                       //     if (horario > 5){
                        //    DrawText("VOCE É MUITO PESSIMO...",xPerdedor,400,80,BLUE);
                            
                          //  estadoMenu = false;
                          //  telaJogo = MENU;
                           //// contadorTentativa = 0;
                           // }
                            
                }//if para voltar ao menu


                DrawText(TextFormat("Time sorteado: %s", timeSorteado.time), 100, 100, 30, BLACK);
                DrawText("Digite um time:", 20, 10, 40, LIGHTGRAY);
                DrawText(escritaTimes, 300, 10, 40, BLACK);
                DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);
                    break;
                
                case MEDIO:

                DrawTexturePro(telaMedio,
                        (Rectangle){ 0, 0, telaMedio.width, telaMedio.height },
                        (Rectangle){ 0, 0, screenWidth, screenHeight },
                        (Vector2){ 0, 0 }, 0.0f, WHITE);

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
                
                DrawTexturePro(telaHard,
                        (Rectangle){ 0, 0, telaHard.width, telaHard.height },
                        (Rectangle){ 0, 0, screenWidth, screenHeight },
                        (Vector2){ 0, 0 }, 0.0f, WHITE);

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
        UnloadSound(acertarPrimeira);
        UnloadTexture(menu);
        fwrite(&timesCode, sizeof(TimesCSV), 1, arquivoBin);
        arquivo = fopen("arquivos/save.dat","wb");
        fclose(arquivoBin);
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
        
        return 0;
        
}//make
