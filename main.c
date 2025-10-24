#include "raylib.h"
#define WHITE CLITERAL(color) {245, 245, 245, 255};

int main(void){

    // resolucao que o programa vai iniciar
    const int screenWidth = 1280;
    const int screenHeight = 960;
    
    //imagem de fundo
    Image fundo = LoadImage("imagem/IMAGEM3.png");
    ImageResize(&fundo, 1280, 960);

    Texture2D background = LoadTexture("imagem/follen.jpeg");
    Texture2D midground = LoadTexture("imagem/follen.jpeg");
    Texture2D foreground = LoadTexture("imagem/follen.jpeg");



    SetTargetFPS(60);//fps set para melhor estabilidade
    GetMousePosition();

    while (!WindowShouldClose()){

        //draw
        BeginDrawing();
            //desenha a saida(draw out)
            DrawTexture(background, 1280, 960, (GetColor(0x052c46ff)));




    }//enquanto o programa estiver aberto
    
    UnloadImage(fundo);
    UnloadTexture(background);

    CloseWindow();//quando for fechada a janela

    return 0;
}//main