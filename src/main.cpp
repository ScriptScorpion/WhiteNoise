#include <SDL2/SDL.h>
#include <random>
#include <cstdint>
#include <cmath> // for tanh

#define X 1000
#define Y 700

const int SAMPLE_RATE = 44100;
const int VOLUME = 21000;
 
void AudioCallback(void* userdata, uint8_t* stream, int len) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution <double> dist(1.0, 2.0);
 
    int16_t* buffer = (int16_t*)stream;
    int samples = len / sizeof(int16_t);
    
    for (int i = 0; i < samples; i++) {
        double sample = dist(gen);
        sample = tanh(sample / VOLUME) * VOLUME * 2; // make sound louder
        buffer[i] = (int16_t)sample;

    }
}
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
    int width = X, heigth = Y;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDL_Window* window = SDL_CreateWindow("White Noice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, X, Y, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    SDL_Event event;
    SDL_AudioSpec desired, obtained;

    desired.freq = SAMPLE_RATE;
    desired.format = AUDIO_S16SYS; // 16-bit format
    desired.channels = 1;   // Mono
    desired.samples = 2048; // size of the buffer in sample
    desired.callback = AudioCallback;
    desired.userdata = NULL; 

    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, 0);
    Draw(renderer, X, Y);
    SDL_PauseAudioDevice(device, 0); // play audio

    while(true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)) {
                SDL_PauseAudioDevice(device, 1); // stop audio
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_CloseAudioDevice(device);
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
