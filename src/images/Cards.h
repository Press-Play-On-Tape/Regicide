#pragma once

namespace Images {

    #include "cards/Hearts_Coloured.h"
    #include "cards/Diamonds_Coloured.h"
    #include "cards/Clubs_Coloured.h"
    #include "cards/Spades_Coloured.h"

    #include "cards/Hearts_Disabled.h"
    #include "cards/Diamonds_Disabled.h"
    #include "cards/Clubs_Disabled.h"
    #include "cards/Spades_Disabled.h"
    
    #include "cards/Card_Front_Normal.h"
    #include "cards/Card_Front_Highlight.h"
    #include "cards/Card_Back.h"
    #include "cards/Card_Placeholder.h"

    #include "cards/Jack_Clubs.h"
    #include "cards/Jack_Spades.h"
    #include "cards/Jack_Diamonds.h"
    #include "cards/Jack_Hearts.h"
    
    const uint8_t * const Suits_Coloured[] = { 
        Spades_Coloured,
        Clubs_Coloured,
        Diamonds_Coloured,
        Hearts_Coloured,
    };

    const uint8_t * const Suits_Disabled[] = { 
        Spades_Disabled,
        Clubs_Disabled,
        Diamonds_Disabled,
        Hearts_Disabled,
    };

    const uint8_t * const Jacks[] = { 
        Jack_Spades,
        Jack_Clubs,
        Jack_Diamonds,
        Jack_Hearts,
    };

}