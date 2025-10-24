#include "raylib.h"

int main(void){

    // resolucao que o programa vai iniciar
    const int screenWidth = 1280;
    const int screenHeight = 960;
    
    //nome da janela gerada
    InitWindow(screenWidth,screenHeight, "Projeto");
    
    
    //imagem de fundo
    Image background1 = LoadImage("imagem/follen.jpeg");
    ImageResize(&background1, screenWidth, screenHeight);
    
    Texture2D background = LoadTexture("Imagem/follen.jpeg");
    
    
    SetTargetFPS(60);//fps set para melhor estabilidade
    //GetMousePosition();

    while (!WindowShouldClose()){

        //draw
        BeginDrawing();
            //desenha a saida(draw out)
            ClearBackground(RAYWHITE);
            DrawText("PAU GELADO", 720,320,20,BLACK);
            DrawTexture(background,0,0,RAYWHITE);
            
            EndDrawing();
            
            
        }//enquanto o programa estiver aberto
        
        UnloadImage(background1);
        UnloadTexture(background);
        
    CloseWindow();//quando for fechada a janela

    return 0;
}//main
