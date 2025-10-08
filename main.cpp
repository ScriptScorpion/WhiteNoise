#include <SDL.h>
#include <random>
#define X 1000
#define Y 700
void Draw(SDL_Renderer *renderer, const int posX, const int posY) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution <int> dist(1, 2);
    int red = 255;
    int green = 255;
    int blue = 255;
    SDL_RenderClear(renderer);
    for (int i = 0; i < posY; ++i) {
        for (int j = 0; j < posX; ++j) {
            switch (dist(gen)) {
                case 1: {
                    red = 255;
                    green = 255;
                    blue = 255;
                    break;
                }
                default: {
                    red = 0;
                    green = 0;
                    blue = 0;
                    break;
                }
            }
            SDL_RenderDrawPoint(renderer, j, i); // render, x, y
            SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
        }
    }
    SDL_RenderPresent(renderer);
    
}
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO); 

    SDL_Window* window = SDL_CreateWindow("White Noice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, X, Y, SDL_WINDOW_RESIZABLE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;

    Draw(renderer, X, Y);
    int width = X, heigth = Y;
    while(true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
            else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED){
                heigth = SDL_GetWindowSurface(window)->h;
                width = SDL_GetWindowSurface(window)->w;
                break;

            }
        }
        Draw(renderer, width, heigth);
        SDL_Delay(35);
    }

    return 0;
}
