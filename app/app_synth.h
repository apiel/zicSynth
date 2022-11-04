#ifndef APP_SYNTH_H_
#define APP_SYNTH_H_

#include <zic_effect_filter.h>
#include <zic_mod_adsr.h>

#include "./app_wavetable.h"

#define APP_SYNTH_WAVE_COUNT 4
#define APP_SYNTH_ENV_COUNT 2
#define APP_SYNTH_PATCHE_COUNT 4

class App_Synth_Patch {
public:
    uint8_t out = 0;
};

class App_Synth {
protected:
    enum {
        NONE,
        OSC_OUT,
        ASDR_OUT,
        FILTER_OUT,
    };

    int16_t oscOut[APP_SYNTH_WAVE_COUNT];
    int16_t adsrOut[APP_SYNTH_ENV_COUNT];
    int16_t filterOut = 0;

public:
    App_Wavetable wavetable[APP_SYNTH_WAVE_COUNT];
    Zic_Effect_Filter filter;
    Zic_Mod_Adsr adsr[APP_SYNTH_ENV_COUNT];

    App_Synth_Patch patches[APP_SYNTH_PATCHE_COUNT] = { OSC_OUT, ASDR_OUT, FILTER_OUT, NONE };

    int16_t sample()
    {
        // Maybe if value to apply envelop or filter is 0.0f, skip it?

        for (uint8_t i = 0; i < APP_SYNTH_WAVE_COUNT; i++) {
            switch (patches[i].out) {
            case OSC_OUT:
                oscOut[0] = wavetable[0].next();
                break;

            case ASDR_OUT:
                adsrOut[0] = adsr[0].next(oscOut[0]);
                break;

            case FILTER_OUT:
                filterOut = filter.next(adsrOut[0]);
                break;

            default:
                break;
            }
        }

        return filterOut;
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