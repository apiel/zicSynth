#ifndef APP_SYNTH_H_
#define APP_SYNTH_H_

#include <zic_mod_filter.h>

#include "./app_wavetable.h"

#define APP_SYNTH_WAVE_COUNT 4

class App_Synth {
public:
    App_Wavetable wavetable[APP_SYNTH_WAVE_COUNT];
    Zic_Mod_Filter filter;

    int16_t sample()
    {
        return 0;
    }
};

// the mixer should be done in the part while assigning patches

#endif