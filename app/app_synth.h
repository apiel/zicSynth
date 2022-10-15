#ifndef APP_SYNTH_H_
#define APP_SYNTH_H_

#include <zic_mod_filter.h>
#include <zic_wave_file.h>
#include <app_core_file.h>

#define APP_SYNTH_WAVE_COUNT 4
#define APP_WAVETABLES_FOLDER "wavetables"

class App_Synth {
public:
    Zic_Wave_File wave[APP_SYNTH_WAVE_COUNT];
    Zic_Mod_Filter filter;
    char filename[256] = "";

    App_Synth()
    {
        firstFile(filename, APP_WAVETABLES_FOLDER);
        for (int i = 0; i < APP_SYNTH_WAVE_COUNT; i++) {
            char filepath[270];
            snprintf(filepath, 270, "%s/%s", APP_WAVETABLES_FOLDER, filename);
            wave[i].open(filepath, true);
        }
    }

    int16_t sample()
    {
        return 0;
    }
};

#endif