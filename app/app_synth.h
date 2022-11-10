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
    uint8_t sign = 0;
    uint8_t to = 0;
};

class App_Synth {
protected:
    enum {
        NO_OUT,
        OSC_OUT,
        ASDR_OUT,
        FILTER_OUT,
    };

    enum {
        NO_VALUE,
        // OSC_VALUE,
        PITCH_VALUE,
        MORPH_VALUE,
        // ASDR_VALUE,
        ATTACK_VALUE,
        SUSTAN_VALUE,
        DECAY_VALUE,
        RELEASE_VALUE,
        // FILTER_VALUE,
        FILTER_CUTOFF_VALUE,
        FILTER_RESONANCE_VALUE,
    };

    enum {
        NO_SIGN,
        ADD_TO,
        SUBSTRACT_FROM,
        MULTIPLY_BY,
        DIVIDE_BY,
    };

    int16_t oscOut[APP_SYNTH_WAVE_COUNT];
    float adsrOut[APP_SYNTH_ENV_COUNT];
    int16_t filterOut = 0;

public:
    App_Wavetable wavetable[APP_SYNTH_WAVE_COUNT];
    Zic_Effect_Filter filter;
    Zic_Mod_Adsr adsr[APP_SYNTH_ENV_COUNT];

    App_Synth_Patch patches[APP_SYNTH_PATCHE_COUNT] = {
        { OSC_OUT, NO_SIGN, NO_VALUE },
        { ASDR_OUT, MULTIPLY_BY, OSC_VALUE },
        { FILTER_OUT, NO_SIGN, NO_VALUE }, // But how does it know what come in?
        { NO_OUT, NO_SIGN, NO_VALUE }
    };

    int16_t sample()
    {
        // Maybe if value to apply envelop or filter is 0.0f, skip it?

        for (uint8_t i = 0; i < APP_SYNTH_WAVE_COUNT; i++) {
            switch (patches[i].out) {
            case OSC_OUT:
                oscOut[0] = wavetable[0].next();
                break;

            case ASDR_OUT:
                adsrOut[0] = adsr[0].next();
                break;

            case FILTER_OUT:
                filterOut = filter.next(oscOut[0] * adsrOut[0]);
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