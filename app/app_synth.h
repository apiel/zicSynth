#ifndef APP_SYNTH_H_
#define APP_SYNTH_H_

#include <app_core_file.h>
#include <zic_mod_filter.h>
#include <zic_wave_file.h>

#define APP_SYNTH_WAVE_COUNT 4
#define APP_WAVETABLES_FOLDER "wavetables"

class App_Synth {
public:
    Zic_Wave_File wave[APP_SYNTH_WAVE_COUNT];
    Zic_Mod_Filter filter;
    char filename[APP_SYNTH_WAVE_COUNT][256] = { "", "", "", "" };

    App_Synth()
    {
        for (int i = 0; i < APP_SYNTH_WAVE_COUNT; i++) {
            char filepath[270];
            firstFile(filename[i], APP_WAVETABLES_FOLDER);
            snprintf(filepath, 270, "%s/%s", APP_WAVETABLES_FOLDER, filename[i]);
            wave[i].open(filepath, true);
        }
    }

    int16_t sample()
    {
        return 0;
    }
};

#endif