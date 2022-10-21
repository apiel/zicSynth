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
    App_Wavetable* wavetable;

public:
    App_View_OscField(uint8_t _oscId, App_Wavetable* _wavetable)
        : oscId(_oscId)
        , wavetable(_wavetable)
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
            sprintf(renderer->text + strlen(renderer->text), "%14s", wavetable->filename);
            break;

        case 2:
            cursor = 5;
            sprintf(renderer->text + strlen(renderer->text), " %5.1f", wavetable->getMorph() + 1.0f);
            // sprintf(renderer->text + strlen(renderer->text), " %-5.1f", 256.0f);
            break;

        case 3: {
            cursor = 7;
            float freq = wavetable->getFrequency();
            sprintf(renderer->text + strlen(renderer->text),
                freq >= 1000 ? " %f.0Hz" : (freq >= 100 ? " %5.1fHz" : (freq >= 10 ? " %5.2fHz" : " %5.3fHz")), freq);
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
        switch (col) {
        case 1:
            return VIEW_CHANGED;

        case 2: {
            float morph = wavetable->getMorph();
            wavetable->morph(morph + (getDirection(keys) * 0.1f));
            return VIEW_CHANGED;
        }
        case 3: {
            float freq = wavetable->getFrequency();
            float step = freq < 10.0 ? 0.001 : (freq < 100.0 ? 0.01 : 0.1);
            wavetable->setFrequency(freq + (getDirection(keys) * step));
            return VIEW_CHANGED;
        }
        default:
            break;
        }
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
        , osc1Field(0, &_synth->wavetable[0])
        , osc2Field(1, &_synth->wavetable[1])
        , osc3Field(2, &_synth->wavetable[2])
        , osc4Field(3, &_synth->wavetable[3])
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