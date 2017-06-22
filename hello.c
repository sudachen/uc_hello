
#pragma uccm default(board) = pca10028

#include<uccm/board.h>
#include<uccm/waitfor.h>

#include <~sudachen/uc_jprint/import.h>
#include <~sudachen/uc_button/import.h>

int main(void)
{
    setup_board();

    PRINT("Hola amigos!");

    static RtcEvent Pulse = RTC_REPEAT_EVENT(500);
    list_event(&Pulse.e);
    static ButtonEvent ButtonClick = CLICK_BUTTON_EVENT(0,250);
    list_event(&ButtonClick.e);

    for ( Event *e; (e = wait_event()); complete_event(e) )
    {
        if ( e == &Pulse.e )
        {
            toggle_boardLED(0);
        }
        else if ( e == &ButtonClick.e )
        {            
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
