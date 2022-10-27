#ifndef APP_SYNTH_H_
#define APP_SYNTH_H_

#include <zic_effect_filter.h>
#include <zic_mod_adsr.h>

#include "./app_wavetable.h"

#define APP_SYNTH_WAVE_COUNT 4
#define APP_SYNTH_ENV_COUNT 2

class App_Synth {
public:
    App_Wavetable wavetable[APP_SYNTH_WAVE_COUNT];
    Zic_Effect_Filter filter;
    Zic_Mod_Adsr adsr[APP_SYNTH_ENV_COUNT];

    int16_t sample()
    {
        // Maybe note play wavetable if envelop is 0.0f
        return adsr[0].next(wavetable[0].next());
        // return wavetable[0].next();
    }
};

// the mixer should be done in the part while assigning patches
//
// osc in lfo mode could be run in one shot, for example for kick design
// therefor would need a way to design custom wavetable :p
// maybe we should think to use linear interpolation for the wavetable to have smoother transitions

// Use Y button to trigger noteOn noteOff
// L1/R1 could be to switch the note to play?? or not :p

// would be great that at the end of a phase of the OSC to trigger a something
// e.g. trigger a random pitch change
// or trigger pitch inc?

#endif