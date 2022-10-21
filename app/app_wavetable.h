#ifndef APP_WAVETABLE_H_
#define APP_WAVETABLE_H_

#include <app_core_file.h>
#include <zic_wave_file.h>

#define APP_WAVETABLES_FOLDER "wavetables"

class App_Wavetable : public Zic_Wave_File {
public:
    char filename[256] = "";

    App_Wavetable()
    {
        char filepath[270];
        firstFile(filename, APP_WAVETABLES_FOLDER);
        snprintf(filepath, 270, "%s/%s", APP_WAVETABLES_FOLDER, filename);
        open(filepath, true);
    }
};

#endif