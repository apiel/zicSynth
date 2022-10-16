#ifndef APP_VIEW_SYNTH_H_
#define APP_VIEW_SYNTH_H_

#include <app_core_view_table.h>
#include <zic_wave_file.h>

#include "./app_synth.h"

#define VIEW_INSTR_ROW 8
#define VIEW_INSTR_COL 4

class App_View_OscField : public App_View_TableField {
protected:
    uint8_t oscId;
    Zic_Wave_File* wave;
    char * filename;

public:
    App_View_OscField(uint8_t _oscId, Zic_Wave_File* _wave, char * _filename)
        : oscId(_oscId)
        , wave(_wave)
        , filename(_filename)
    {
    }

    bool isSelectable(uint8_t row, uint8_t col) override
    {
        return col != 0;
    }

    void render(App_Renderer* renderer, uint8_t row, uint8_t col, uint8_t selectedRow, uint8_t selectedCol)
    {
        uint8_t cursor = 0;
        switch (col) {
        case 0:
            sprintf(renderer->text + strlen(renderer->text), "%d", oscId + 1);
            break;

        case 1:
            cursor = 14;
            sprintf(renderer->text + strlen(renderer->text), "%14s", filename);
            break;

        case 2:
            cursor = 5;
            sprintf(renderer->text + strlen(renderer->text), " %5.1f", wave->getMorph() + 1.0f);
            // sprintf(renderer->text + strlen(renderer->text), " %-5.1f", 256.0f);
            break;

        case 3: {
            cursor = 7;
            float freq = wave->getFrequency();
            sprintf(renderer->text + strlen(renderer->text),
                freq > 999 ? " %f.0Hz" : (freq > 99 ? " %5.1fHz" : (freq > 9 ? " %5.2fHz" : " %5.3fHz")), freq);
            break;
        }
        default:
            break;
        }
        if (selectedRow == row && selectedCol == col) {
            renderer->setCursor(cursor, -cursor);
        }
    }

    uint8_t update(UiKeys* keys, App_Renderer* renderer, uint8_t row, uint8_t col) override
    {
        return VIEW_NONE;
    }
};

class App_View_Synth : public App_View_Table {
protected:
    App_View_OscField osc1Field;
    App_View_OscField osc2Field;
    App_View_OscField osc3Field;
    App_View_OscField osc4Field;

    App_View_TableField* fields[VIEW_INSTR_ROW * VIEW_INSTR_COL] = {
        // clang-format off
        &osc1Field, &osc1Field, &osc1Field, &osc1Field,
        &osc2Field, &osc2Field, &osc2Field, &osc2Field,
        &osc3Field, &osc3Field, &osc3Field, &osc3Field,
        &osc4Field, &osc4Field, &osc4Field, &osc4Field,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
        // clang-format on
    };

public:
    App_View_Synth(App_Synth* _synth)
        : App_View_Table(fields, VIEW_INSTR_ROW, VIEW_INSTR_COL)
        , osc1Field(0, &_synth->wave[0], &_synth->filename[0][0])
        , osc2Field(1, &_synth->wave[1], &_synth->filename[1][0])
        , osc3Field(2, &_synth->wave[2], &_synth->filename[2][0])
        , osc4Field(3, &_synth->wave[3], &_synth->filename[3][0])
    {
        initSelection();
    }

    void initDisplay(App_Renderer* renderer)
    {
        renderer->useColor(0, 4, 0, 1);
        // renderer->useFirstLetterHilighted();
        App_View_Table::initDisplay(renderer);
    }
};

#endif