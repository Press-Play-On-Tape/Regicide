#pragma once

namespace Images {

    #include "title/Title_01.h"
    #include "title/Title_02.h"
    #include "title/Background.h"
    #include "title/SwapPlayers.h"

    #include "title/NumberOfPlayers.h"
    #include "title/NumberOfPlayers_01.h"
    #include "title/NumberOfPlayers_02.h"
    #include "title/NumberOfPlayers_03.h"
    #include "title/NumberOfPlayers_04.h"

    const uint8_t * const NumberOfPlayers_Digits[] = { 
        NumberOfPlayers_01,
        NumberOfPlayers_02,
        NumberOfPlayers_03,
        NumberOfPlayers_04,
    };

}