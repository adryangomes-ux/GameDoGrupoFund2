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
#include "exportar.h"
#include "cores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

typedef enum telaAtual {MENU, ESCOLHADIFICULDADE,ESCOLHATIMES} telaAtual;
typedef enum Dificuldade {FACIL=4, MEDIO, DIFICIL,CREDITOS,CREDITOSBADENDING} Dificuldade;

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
    int capacidade = 10;//usado para vetor dinamico timesCode

    TimesCSV *timesCode = malloc(sizeof(TimesCSV) * capacidade);//para poder ler o arquivo csv
    
    FILE *arquivoBin = fopen("arquivos/save.dat", "rb");
    FILE *arquivo;

    if (arquivoBin != NULL){         
        printf(AZUL "--Hello Wordl--\nObrigado por jogar\nNovamente" RESET);
                capacidade *= 2;
                timesCode = realloc(timesCode, sizeof(TimesCSV) * capacidade);
                if (!timesCode) { 
                    perror("Erro ao realocar"); 
                    exit(1);
                 }

        while (fread(&timesCode[count], sizeof(TimesCSV), 1, arquivoBin) == 1) {
            count++;
            if (count >= capacidade) {
                capacidade *= 2;
                TimesCSV *novo = realloc(timesCode, sizeof(TimesCSV) * capacidade);
                if (!novo) { perror("Erro ao realocar memória"); free(timesCode); fclose(arquivoBin); exit(1); }
                timesCode = novo;
            }
        }

                fclose(arquivoBin);

    }else{
        printf(AZUL "---BEM VINDO!---\nDESEJAMOS BOA SORTE\nPARA VOCE NO JOGO " RESET);


        arquivo = fopen("arquivos/TimesDicas.csv", "r");
        if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo CSV!\n");
                CloseWindow();
                return 1;
            }//caso der erro
            
            
        char linha[512];
        fgets(linha, sizeof(linha), arquivo); // Ignora o cabeçalho
        
        // Lê linha por linha
        while (fgets(linha, sizeof(linha), arquivo)) {
            if (count >= capacidade) {
                capacidade *= 2;
                timesCode = realloc(timesCode, sizeof(TimesCSV) * capacidade);
                if (!timesCode) { perror("Erro de realocação"); exit(1); }
            }

            linha[strcspn(linha, "\r\n")] = 0; // remove \n ou \r

            char *token = strtok(linha, ",");
            int coluna = 0;
            while (token != NULL && coluna < 5) {
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
        
        //--------------------------------------------------------------------------------------
        
        
        
        do {//vai fazer enquanto
            printf(VERMELHO "\n==== MENU ====\n" RESET);
            printf(CIANO "1 - Inserir\n" RESET);
            printf(CIANO "2 - Listar\n" RESET);
            printf(CIANO "3 - Pesquisar\n" RESET);
            printf(CIANO "4 - Editar\n" RESET);
            printf(CIANO "5 - Excluir\n" RESET);
            printf(CIANO "6 - Exportar em CSV\n" RESET);
            printf(CIANO "0 - Sair para o jogo\n" RESET);
            printf( VERDE "Escolha: " RESET);
            scanf("%d", &opcao);
            setbuf(stdin,NULL);
        
            switch (opcao) {
                case 1: timesCode = inserir(timesCode, &count, &capacidade); break;
                case 2: listar(timesCode, count); break;
                case 3: pesquisar(timesCode, count); break;
                case 4: editar(timesCode, count); break;
                case 5: excluir(timesCode, &count); break;
                case 6: ExportarCSV(timesCode, count); break;
                
            }
        
        } while (opcao != 0);//for diferente de zero
        
        // Initialization
        //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 960;

    InitWindow(screenWidth, screenHeight, "bad fallen");
    InitAudioDevice();      // Initialize audio device
    //sons e texturas
    Texture2D telaDif = LoadTexture("imagens/ancient/ancient1.png");
    Texture2D telaFacil = LoadTexture("imagens/dust2/dust3.png");
    Texture2D telaMedio = LoadTexture("imagens/anubis/anubis2.png");
    Texture2D telaHard = LoadTexture("imagens/golden/golden3.png");
    Texture2D telaCreditos = LoadTexture("imagens/bdfallen2.jpg");
    Texture2D telaPerdedor = LoadTexture("imagens/bdfallen.jpg");
    Music musicaFundo = LoadMusicStream("audio/infspawn.wav");
    Sound fxButton = LoadSound("audio/selecao.wav");
    Sound clickMouseLeftBoton = LoadSound("audio/usp.wav");
    Sound acertarPrimeira = LoadSound("audio/grafite.wav");
    Sound lesgo = LoadSound("audio/okletsgo.wav");
    SetSoundVolume(lesgo, 0.25f);
    PlayMusicStream(musicaFundo);
    SetMusicVolume(musicaFundo, 0.5f);

    Texture2D backgrounds[4];
    backgrounds[0] = LoadTexture("imagens/fallen.jpg");
    backgrounds[1] = LoadTexture("imagens/bdfallen.jpg");
    backgrounds[2] = LoadTexture("imagens/bdfallen2.jpg");
    backgrounds[3] = LoadTexture("imagens/bdfallen3.jpg");
    int currentBgIndex = 0;


    //centralizar o texto "times" no eixo x
    int larguraJanela = GetScreenWidth();
    int larguraTexto1 = MeasureText("PRESSIONE ESPAÇO PARA INICIAR", 35);
    int perdedor = MeasureText("VOCE É PESSIMO",60);
    int x1 = (larguraJanela - larguraTexto1) / 2;
    int xPerdedor = ((larguraJanela - perdedor) / 2) - 120;
    int xGanhador = ((larguraJanela - perdedor) / 2) - 120;

    
    
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
    Rectangle btnTrocarFundoRect = { 50, screenHeight - 100, 200, 50 };//botão de trocar o background do menu
    
    
    
    int indiceAleatorio = GetRandomValue(0, count - 1);//gera um valor aleatorio para settar o time
    TimesCSV timeSorteado = timesCode[indiceAleatorio];
    SetTargetFPS(60);// Set our game to run at 60 frames-per-second
    
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update - tudo que fica constantemente atualizando
        ponteiroMouse = GetMousePosition();
        
        UpdateMusicStream(musicaFundo);

        
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        Vector2 mousePoint = GetMousePosition();
        bool mouseOverTrocarFundo = CheckCollisionPointRec(mousePoint, btnTrocarFundoRect);

            if (telaJogo == MENU && mouseOverTrocarFundo)
            {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                currentBgIndex++;
                if (currentBgIndex >= 4)
                {
                    currentBgIndex = 0;
                }
            }
            }

        // --- BOTÃO 1 (TIMES) ---
        if (IsKeyPressed(KEY_SPACE) && estadoMenu == false)
        {
            estadoMenu = true;
            estadoBotao1 = 1;
            telaJogo = ESCOLHADIFICULDADE;
            PlaySound(lesgo);
        }
        else estadoBotao1 = 0;   
        // ----BOTAO PARA SAIR O SOM DO CLICK ---------
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                PlaySound(clickMouseLeftBoton);
            }     
        
        
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

                int tecla = GetCharPressed();//captura tecla por tecla
                
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
                
                
                if (IsKeyPressed(KEY_ENTER)){
                    enviar = true;
                }
                
                if (enviar){

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
        
        switch (telaJogo){
                case MENU:
                Texture2D textureAtual = backgrounds[currentBgIndex];
                DrawTexturePro(textureAtual,
                (Rectangle){ 0, 0, (float)textureAtual.width, (float)textureAtual.height },
                (Rectangle){ 0, 0, (float)screenWidth, (float)screenHeight },
                (Vector2){ 0, 0 }, 0.0f, WHITE);

                    
                    //retangulo redondo pra ficar em volta do texto do menu
                    DrawRectangleRounded((Rectangle)botao1, 2, 3, BLACK);
                    
                    //texto do menu
                    DrawText("BAD FALLEN", xMenu, screenHeight*0.25, 75, RED);
                    DrawText("PRESSIONE ESPAÇO PARA INICIAR", x1, screenHeight*0.5, 35, textoBotao1);

                    Color corBotaoFundo = mouseOverTrocarFundo ? DARKGRAY : BLACK;
                    DrawRectangleRounded(btnTrocarFundoRect, 0.3, 4, corBotaoFundo);
                    DrawText("Trocar Fundo", (int)btnTrocarFundoRect.x + 30, (int)btnTrocarFundoRect.y + 15, 20, WHITE);

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
                                        case FACIL: {

                                        DrawTexturePro(telaFacil,
                                        (Rectangle){ 0, 0, telaFacil.width, telaFacil.height },
                                        (Rectangle){ 0, 0, screenWidth, screenHeight },
                                        (Vector2){ 0, 0 }, 0.0f, WHITE);

                                        DrawText(TextFormat("%02d", contadorTentativa), 400, 800, 45, LIGHTGRAY);//desenha quantidade de tentativas
                                        
                                        if (acertou && contadorTentativa == 0){
                                            
                                            if(acertou){ dificuldade = CREDITOS;}
                                        }else if (acertou && contadorTentativa > 0){//caso não for de primeira
                                          
                                            if(acertou){ dificuldade = CREDITOS;}
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
                                            
                                            if(contadorTentativa == 5){ dificuldade = CREDITOSBADENDING;}
                                    }//if para voltar ao menu


                                    //DrawText(TextFormat("Time sorteado: %s", timeSorteado.time), 100, 100, 30, BLACK); HACK DE VER O TIME SORTEADO
                                    DrawText("Digite um time:", 20, 10, 40, LIGHTGRAY);
                                    DrawText(escritaTimes, 300, 10, 40, BLACK);
                                    DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                                    DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);
                                        break;
                                    }//case FACIL

                                    case MEDIO: 

                                    DrawTexturePro(telaMedio,
                                            (Rectangle){ 0, 0, telaMedio.width, telaMedio.height },
                                            (Rectangle){ 0, 0, screenWidth, screenHeight },
                                            (Vector2){ 0, 0 }, 0.0f, WHITE);


                                        if (acertou && contadorTentativa == 0){
                                            
                                            if(acertou){ dificuldade = CREDITOS;}
                                        }else if (acertou && contadorTentativa > 0){//caso não for de primeira
                                            
                                            if(acertou){ dificuldade = CREDITOS;}
                                        }
                                        

                                        
                                        if (contadorTentativa == 1){
                                            DrawText(timesCode[indiceAleatorio].pais, 80, 600, 40, BLACK);
                                        }else if (contadorTentativa == 2){
                                            DrawText(timesCode[indiceAleatorio].jogador, 80, 650, 40, BLACK);
                                        }else if (contadorTentativa == 3){
                                            DrawText(timesCode[indiceAleatorio].destaque, 80, 700, 40, BLACK);
                                        }else if (contadorTentativa == 4 && acertou == false){
                                            
                                            if(contadorTentativa == 4){ dificuldade = CREDITOSBADENDING;}
                                        }//caso perda
                                        

                                        
                                        //DrawText(TextFormat("Time sorteado: %s", timeSorteado.time), 100, 100, 30, BLACK);
                                        DrawText("Digite um time:", 20, 10, 40, LIGHTGRAY);
                                        DrawText(escritaTimes, 300, 10, 40, BLACK);
                                        DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                                        DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);
                                        
                                        break;

                            //-----------------------------------------------------------------------*-----------------
                                    case DIFICIL: {
                                    
                                    DrawTexturePro(telaHard,
                                            (Rectangle){ 0, 0, telaHard.width, telaHard.height },
                                            (Rectangle){ 0, 0, screenWidth, screenHeight },
                                            (Vector2){ 0, 0 }, 0.0f, WHITE);

                                    //captura as teclas
                                    DrawText(TextFormat("%02d", contadorTentativa), 400, 800, 45, LIGHTGRAY);
                                        if (acertou && contadorTentativa == 0){
                                           
                                            if(acertou){ dificuldade = CREDITOS;}
                                        }else if (acertou && contadorTentativa > 0){//caso não for de primeira
                    
                                            if(acertou){ dificuldade = CREDITOS;}
                                        }
                                        
                                        if (contadorTentativa == 1){
                                            DrawText(timesCode[indiceAleatorio].pais, 80, 600, 40, BLACK);
                                        }else if (contadorTentativa == 2){
                                            DrawText(timesCode[indiceAleatorio].jogador, 80, 650, 40, BLACK);
                                        }else if (contadorTentativa == 3 && acertou == false){
                                            
                                            if(contadorTentativa == 3){ dificuldade = CREDITOSBADENDING;}
                                        } 


                                    //DrawText(TextFormat("Time sorteado: %s", timeSorteado.time), 100, 100, 30, RED);
                                    DrawText("Digite um time:", 20, 10, 40, LIGHTGRAY);
                                    DrawText(escritaTimes, 300, 10, 40, RED);
                                    DrawRectangleRounded((Rectangle)botaoVoltar, 2, 3, BLACK);
                                    DrawText("VOLTAR", 996, 890, 35, textoBotaoVoltar);

                                    break;
                                    }//case dificil

                                    case CREDITOS:
                                            DrawTexturePro(telaCreditos,
                                            (Rectangle){ 0, 0, telaHard.width, telaHard.height },
                                            (Rectangle){ 0, 0, screenWidth, screenHeight },
                                            (Vector2){ 0, 0 }, 0.0f, WHITE);


                                        if (acertou && contadorTentativa == 0){
                                            DrawText("Parabéns!!\nvocê acertou de primeira!", xGanhador, 180, 80, RED);
                                            DrawText("Obrigado por Jogar!", xGanhador, 700, 80, GREEN);
                                        }else if (acertou && contadorTentativa > 0){//caso não for de primeira
                                            DrawText("Parabéns, você acertou!", xGanhador, 180, 80, RED);
                                            DrawText("Obrigado por Jogar!", xGanhador, 700, 80, GREEN);
                                        }

                                    break;
                                    case CREDITOSBADENDING:
                                            DrawTexturePro(telaPerdedor,
                                            (Rectangle){ 0, 0, telaHard.width, telaHard.height },
                                            (Rectangle){ 0, 0, screenWidth, screenHeight },
                                            (Vector2){ 0, 0 }, 0.0f, WHITE);

                                    DrawText("VOCE É RUIM DE MAIS...",xPerdedor,180,80,BLUE);
                                    DrawText("Mesmo assim obrigado \npor jogar",xPerdedor,700,80,BLUE);
                                    break;
                        }//fecha escolha times
                            default:
                                break;
                            }
            //switch
            DrawFPS(0,1);
            EndDrawing();
    }//while

        //-------------------------------------------
        //Salva os arquivos em binário
        //-------------------------------------------
        arquivoBin = fopen("arquivos/save.dat", "wb");
        fwrite(timesCode, sizeof(TimesCSV), count, arquivoBin);
        fclose(arquivoBin);

        //
        // De-Initialization
        //--------------------------------------------------------------------------------------
        UnloadSound(fxButton);
        UnloadMusicStream(musicaFundo);
        UnloadSound(acertarPrimeira);
        UnloadTexture(telaDif);
        UnloadTexture(telaFacil);
        UnloadTexture(telaMedio);
        UnloadTexture(telaHard);
        UnloadTexture(telaCreditos);
        UnloadTexture(telaPerdedor);
        for (int i = 0; i < 4; i++) {
            UnloadTexture(backgrounds[i]);
        }
        CloseWindow();        // Close window and OpenGL context
        //--------------------------------------------------------------------------------------
        
        return 0;
}//make