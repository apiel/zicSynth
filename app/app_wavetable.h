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

    App_Wavetable* setNext(int8_t direction = 0)
    {
        // TODO if direction > 1 then should jump to next letter
        direction = range(direction, -1,  1);
        nextFile(filename, APP_WAVETABLES_FOLDER, filename, direction);
        open(filename, true);
        return this;
    }
};

#endif