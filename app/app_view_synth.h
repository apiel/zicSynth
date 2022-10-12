#ifndef APP_VIEW_SYNTH_H_
#define APP_VIEW_SYNTH_H_

#include <app_core_view_table.h>

#define VIEW_INSTR_ROW 8
#define VIEW_INSTR_COL 3

class App_View_SynthRow : public App_View_TableLabeledRow {
public:
    App_View_SynthRow()
        : App_View_TableLabeledRow("1", 0)
    {
    }

    void renderValue(App_Renderer* renderer, uint8_t col)
    {
        // sprintf(renderer->text + strlen(renderer->text), "%-2d", tracks->trackId + 1);
        strcat(renderer->text, "hello12345.wav 256.0 22050Hz");
    }

    uint8_t update(UiKeys* keys, App_Renderer* renderer, uint8_t row, uint8_t col) override
    {
        return VIEW_NONE;
    }
};

class App_View_Synth : public App_View_Table {
protected:
    App_View_SynthRow synthField;

    App_View_TableField* fields[VIEW_INSTR_ROW * VIEW_INSTR_COL] = {
        // clang-format off
        &synthField, &synthField, NULL,
        NULL, NULL, NULL,
        NULL, NULL, NULL,
        NULL, NULL, NULL,
        NULL, NULL, NULL,
        NULL, NULL, NULL,
        NULL, NULL, NULL,
        NULL, NULL, NULL,
        // clang-format on
    };

public:
    App_View_Synth()
        : App_View_Table(fields, VIEW_INSTR_ROW, VIEW_INSTR_COL)
    {
        initSelection();
    }

    void initDisplay(App_Renderer* renderer)
    {
        // renderer->useColoredLabel();
        // renderer->useFirstLetterHilighted();
        App_View_Table::initDisplay(renderer);
    }
};

#endif