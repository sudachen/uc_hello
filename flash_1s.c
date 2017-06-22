
#pragma uccm default(board) = pca10028

#include <uccm/board.h>
#include <uccm/waitfor.h>

int main(void)
{
    setup_board();

    static RtcEvent Pulse = RTC_REPEAT_EVENT(500);

    for ( Event *e; (e = wait_event()); complete_event(e) )
    {
        if ( e == &Pulse.e )
        {
            toggle_boardLED(0);
        }
    }
}
