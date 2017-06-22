
#pragma uccm default(board) = pca10028

#include<uccm/board.h>
#include<uccm/waitfor.h>

#include <~sudachen/uc_jprint/import.h>
#include <~sudachen/uc_button/import.h>

void button(CrContext *cr)
{
    static ButtonEvent ButtonClick = CLICK_BUTTON_EVENT(0,250);

    CR_SWITCH(cr)
    {
        list_event(&ButtonClick.e);
        for(;;)
        {
            CR_AWAIT(cr,0,&ButtonClick.e);
            #if PRINT_IS_ENABLED
                bool on = isOn_boardLED(1);
                PRINT("button clicked, toggle LED %? -> %?",
                      $s(on?"on":"off"),
                      $s(on?"off":"on"));
            #endif
            toggle_boardLED(1);
        }
    }
}

static CrContext ButtonCr = {button};

void blink(CrContext *cr)
{
    CR_SWITCH(cr) for(;;)
    {
        CR_DELAY(cr,500);
        toggle_boardLED(0);
    }
}

static CrContext BlinkCr = {blink};

int main(void)
{
    setup_board();

    PRINT("Hola amigos!");

    call_cr(&BlinkCr);
    call_cr(&ButtonCr);

    for ( Event *e; (e = wait_event()); complete_event(e) ) {;}
}
