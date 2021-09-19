#pragma once

namespace Images {

    #include "title/Title_01.h"
    #include "title/Title_01_F1.h"
    #include "title/Title_01_F2.h"
    #include "title/Title_01_F3.h"
    #include "title/Title_01_F4.h"
    #include "title/Title_01_F5.h"

    #include "title/Title_02.h"
    #include "title/Background.h"
    #include "title/SwapPlayers.h"
    #include "title/Winner.h"

    #include "title/NumberOfPlayers.h"
    #include "title/NumberOfPlayers_01.h"
    #include "title/NumberOfPlayers_02.h"
    #include "title/NumberOfPlayers_03.h"
    #include "title/NumberOfPlayers_04.h"

    const uint8_t * const Title_01_Highlight[] = { 
        Title_01_F1,
        Title_01_F2,
        Title_01_F3,
        Title_01_F4,
        Title_01_F5
    };

    const uint8_t * const NumberOfPlayers_Digits[] = { 
        NumberOfPlayers_01,
        NumberOfPlayers_02,
        NumberOfPlayers_03,
        NumberOfPlayers_04,
    };

}