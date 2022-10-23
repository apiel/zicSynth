#ifndef APP_SYNTH_H_
#define APP_SYNTH_H_

#include <zic_effect_filter.h>

#include "./app_wavetable.h"

#define APP_SYNTH_WAVE_COUNT 4

class App_Synth {
public:
    App_Wavetable wavetable[APP_SYNTH_WAVE_COUNT];
    Zic_Effect_Filter filter;

    int16_t sample()
    {
        return 0;
    }
};

// the mixer should be done in the part while assigning patches

#endif