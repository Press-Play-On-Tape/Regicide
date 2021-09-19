#pragma once

namespace Images {

    #include "title/Title_01_Top.h"
    #include "title/Title_01_Bot.h"
    #include "title/Title_01_F1_Top.h"
    #include "title/Title_01_F2_Top.h"
    #include "title/Title_01_F2_Bot.h"
    #include "title/Title_01_F3_Top.h"
    #include "title/Title_01_F3_Bot.h"
    #include "title/Title_01_F4_Top.h"
    #include "title/Title_01_F4_Bot.h"
    #include "title/Title_01_F5_Bot.h"

    #include "title/Title_02.h"
    #include "title/Background.h"
    #include "title/SwapPlayers.h"
    #include "title/Winner.h"

    #include "title/NumberOfPlayers.h"
    #include "title/NumberOfPlayers_01.h"
    #include "title/NumberOfPlayers_02.h"
    #include "title/NumberOfPlayers_03.h"
    #include "title/NumberOfPlayers_04.h"

    const uint8_t * const Title_01_Tops[] = { 
        Title_01_F1_Top,
        Title_01_F2_Top,
        Title_01_F3_Top,
        Title_01_F4_Top,
        Title_01_Top
    };

    const uint8_t * const Title_01_Bots[] = { 
        Title_01_Bot,
        Title_01_F2_Bot,
        Title_01_F3_Bot,
        Title_01_F4_Bot,
        Title_01_F5_Bot
    };

    const uint8_t * const NumberOfPlayers_Digits[] = { 
        NumberOfPlayers_01,
        NumberOfPlayers_02,
        NumberOfPlayers_03,
        NumberOfPlayers_04,
    };

}