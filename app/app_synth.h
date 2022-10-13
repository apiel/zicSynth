#ifndef APP_SYNTH_H_
#define APP_SYNTH_H_

#include <zic_mod_filter.h>
#include <zic_wave_file.h>

#define APP_SYNTH_WAVE_COUNT 4

class App_Synth {
public:
    Zic_Wave_File wave[APP_SYNTH_WAVE_COUNT];
    Zic_Mod_Filter filter;

    int16_t sample()
    {
        return 0;
    }
};

#endif