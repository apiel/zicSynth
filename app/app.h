#ifndef APP_H_
#define APP_H_

#include "./app_def.h"
#include "./app_synth.h"
#include "./app_view_synth.h"
#include <app_core_display.h>
#include <app_core_renderer.h>

class App {
public:
    App_Synth synth;

    App_Display* display;
    UiKeys keys;

    App_View_Synth synthView;

    bool rendered = false;

    App(App_Display* _display)
        : display(_display)
        , synthView(&synth)
    {
    }

    int16_t sample()
    {
        return synth.sample();
    }

    void render()
    {
        if (display->ready()) {
            // TODO find a better place way to reset cursor
            display->reset();
            synthView.render(display);
            display->drawText();
            rendered = true;
        }
    }

    void handleUi(uint8_t keysBin)
    {
        keys.Up = (keysBin >> UI_KEY_UP) & 1;
        keys.Down = (keysBin >> UI_KEY_DOWN) & 1;
        keys.Left = (keysBin >> UI_KEY_LEFT) & 1;
        keys.Right = (keysBin >> UI_KEY_RIGHT) & 1;
        keys.Edit = (keysBin >> UI_KEY_EDIT) & 1;
        keys.Menu = (keysBin >> UI_KEY_MENU) & 1;
        // SDL_Log("%d%d%d%d%d%d\n", keys.Up, keys.Down, keys.Left, keys.Right, keys.A, keys.Y);

        // if (keys.Menu && keys.Edit) {
        //     tracks.togglePlay();
        // } else if (menuView.update(&keys, display) != VIEW_NONE) {
        //     render();
        // } else if (menuView.getView()->update(&keys, display) != VIEW_NONE) {
        //     render();
        // }



        if (synthView.update(&keys, display) != VIEW_NONE) {
            render();
        }
    }

    void quit()
    {
        // App_Renderer renderer;
        // for (uint8_t i; i < APP_MENU_SIZE; i++) {
        //     if (menu[i].view) {
        //         renderer.reset();
        //         renderer.startRow = 0;
        //         menu[i].view->snapshot(&renderer);
        //     }
        // }
    }

    void start()
    {
        // for (uint8_t i; i < APP_MENU_SIZE; i++) {
        //     if (menu[i].view) {
        //         menu[i].view->loadSnapshot();
        //     }
        // }
    }
};

#endif