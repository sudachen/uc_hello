
#pragma uccm default(board) = pca10028

#include <uccm/board.h>
#include <uccm/waitfor.h>

void flash1s_1(CrContext *cr)
{
    static RtcEvent Pulse = RTC_REPEAT_EVENT(500);

    CR_SWITCH(cr)
    {
        list_event(&Pulse.e);
        for (;;)
        {
            CR_AWAIT(cr,0,&Pulse.e);
            toggle_boardLED(0);
        }
    }
}

static CrContext Flash1sCr1 = {flash1s_1};

void flash1s_2(CrContext *cr)
{
    CR_SWITCH(cr)
    {
        for (;;)
        {
            CR_DELAY(cr,500);
            toggle_boardLED(1);
        }
    }
}

static CrContext Flash1sCr2 = {flash1s_2};

int main(void)
{
    setup_board();
    call_cr(&Flash1sCr1);
    call_cr(&Flash1sCr2);

    for ( Event *e; (e = wait_event()); complete_event(e) ) {;}
}
