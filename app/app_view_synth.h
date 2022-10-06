#ifndef APP_VIEW_SYNTH_H_
#define APP_VIEW_SYNTH_H_

#include "./app_view.h"

class App_View_Synth : public App_View {
protected:
public:
    void render(App_Renderer* renderer)
    {
        strcpy(renderer->text, "Hello synth");
    }

    uint8_t update(UiKeys* keys, App_Renderer* renderer)
    {
        return VIEW_NONE;
    }
};

#endif