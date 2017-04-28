
#pragma uccm default(board) = pca10040

#include <~sudachen/uc_jprint/import.h>
#include <~sudachen/uc_waitfor/import.h>
#include <~sudachen/uc_button/import.h>

int main(void)
{
    setup_board();

    PRINT("Hola amigos!");

    static RtcEvent Pulse = RTC_REPEAT_EVENT(500);
    list_event(&Pulse.e);
    static ButtonEvent ToggleLED2 = CLICK_BUTTON_EVENT(BOARD_BUTTON_BUTTON1,250);
    list_event(&ToggleLED2.e);

    for ( Event *e; (e = wait_forEvent()); complete_event(e) )
    {
        if ( e == &Pulse.e )
        {
            toggle_boardLED_LED1();
        }
        else if ( e == &ToggleLED2.e )
        {
            bool on = isOn_boardLED_LED2();
            PRINT("button BUTTON1 clicked, toggle LED2 %? -> %?", $s(on?"on":"off"), $s(on?"off":"on"));
            toggle_boardLED_LED2();
        }
    }
}
