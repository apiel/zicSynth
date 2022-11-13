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
    uint8_t outPos = 0;
    uint8_t target = 0;
    uint8_t targetPos = 0;
};

class App_Synth {
protected:
    enum {
        NO_OUT,
        OSC_OUT,
        ENV_OUT,
        PITCH_OUT,
    };

    enum {
        OSC_PITCH,
        OSC_MORPH,
        OSC_AMPLITUDE,
        ENV_ATTACK,
        ENV_DECAY,
        ENV_SUSTAN,
        ENV_RELEASE,
        FILTER_INPUT,
        FILTER_CUTOFF,
        FILTER_RESONANCE,
        OUTPUT,
    };

    int16_t oscOut[APP_SYNTH_WAVE_COUNT];
    bool oscOutFree[APP_SYNTH_WAVE_COUNT];

    float envOut[APP_SYNTH_ENV_COUNT];
    bool envOutFree[APP_SYNTH_ENV_COUNT];

    int16_t filterOut = 0;
    int16_t filterInput = 0;

public:
    App_Wavetable wavetable[APP_SYNTH_WAVE_COUNT];
    Zic_Effect_Filter filter;
    Zic_Mod_Adsr adsr[APP_SYNTH_ENV_COUNT];

    App_Synth_Patch patches[APP_SYNTH_PATCHE_COUNT] = {
        { ENV_OUT, 0, OSC_AMPLITUDE, 0 },
        { OSC_OUT, 0, FILTER_INPUT, 0 },
        { NO_OUT },
        { NO_OUT }
    };

    int16_t sample()
    {
        for (int i = 0; i < APP_SYNTH_WAVE_COUNT; i++) {
            oscOutFree[i] = true;
        }

        for (int i = 0; i < APP_SYNTH_ENV_COUNT; i++) {
            envOutFree[i] = true;
        }

        for (uint8_t i = 0; i < APP_SYNTH_WAVE_COUNT; i++) {
            uint8_t outPos = patches[i].outPos;
            switch (patches[i].out) {
            case OSC_OUT: {
                if (oscOutFree[outPos]) {
                    oscOut[outPos] = wavetable[outPos].next();
                    oscOutFree[outPos] = false;
                }
                // then here apply out value to input params?
                break;
            }

            case ENV_OUT: {
                if (envOutFree[outPos]) {
                    envOut[outPos] = adsr[outPos].next();
                    envOutFree[outPos] = false;
                }
                // then here apply out value to input params?
                break;
            }

            default:
                break;
            }
        }

        filterInput = oscOut[0] * envOut[0];
        filterOut = filter.next(filterInput);

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