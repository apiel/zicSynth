#include <APP_SDL/sdl2.h>

#include "../app/app.h"
#include "../app/app_def.h"
#include <app_core_display.h>
#include <app_core_file.h>

UI_Display display;
App app(&display);

void audioCallBack(void* userdata, Uint8* stream, int len)
{
    static union sampleTUNT {
        Uint8 ch[2];
        int16_t sample;
    } sampleDataU;

    for (int i = 0; i < len; i++) {
        sampleDataU.sample = app.sample();
        stream[i] = sampleDataU.ch[0];
        i++;
        stream[i] = sampleDataU.ch[1];

#if CHANNELS == 2
        i++;
        stream[i] = sampleDataU.ch[0];
        i++;
        stream[i] = sampleDataU.ch[1];
#endif
    }
}

int main(int argc, char* args[])
{
    SDL_Log(">>>>>>> Start Zic Synth\n");

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Zic",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_W, SCREEN_H,
        SDL_WINDOW_SHOWN);

    if (window == NULL) {
        fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
    display.init(screenSurface);

    SDL_AudioDeviceID audioDevice = initAudio(audioCallBack);
    if (SDL_getenv("ZIC_SKIP_AUDIO") == NULL && !audioDevice) {
        return 1;
    }

    app.start();
    app.render();
    SDL_UpdateWindowSurface(window);

    while (handleEvent()) {
        if (ui.keysChanged) {
            ui.keysChanged = false;
            app.handleUi(ui.keys);
            SDL_Log("\n%s\n", display.text);
            // SDL_UpdateWindowSurface(window);
        }
        // SDL_Delay(10);
        if (app.rendered) {
            app.rendered = false;
            SDL_UpdateWindowSurface(window);
        }
    }
    app.quit();

    SDL_DestroyWindow(window);
    SDL_CloseAudioDevice(audioDevice);

    SDL_Quit();
    return 0;
}