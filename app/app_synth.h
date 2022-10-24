#ifndef APP_SYNTH_H_
#define APP_SYNTH_H_

#include <zic_effect_filter.h>
#include <zic_mod_adsr.h>

#include "./app_wavetable.h"

#define APP_SYNTH_WAVE_COUNT 4

class App_Synth {
public:
    App_Wavetable wavetable[APP_SYNTH_WAVE_COUNT];
    Zic_Effect_Filter filter;
    Zic_Mod_Adsr adsr;

    int16_t sample()
    {
        return 0;
    }
};

// the mixer should be done in the part while assigning patches
//
// osc in lfo mode could be run in one shot, for example for kick design
// therefor would need a way to design custom wavetable :p
// maybe we should think to use linear interpolation for the wavetable to have smoother transitions

// Use Y button to trigger noteOn noteOff
// L1/R1 could be to switch the note to play?? or not :p

#endif