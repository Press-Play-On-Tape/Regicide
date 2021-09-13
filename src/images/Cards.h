#pragma once

namespace Images {

    #include "cards/Heart.h"
    #include "cards/Diamond.h"
    #include "cards/Club.h"
    #include "cards/Spade.h"

    #include "cards/Heart_Grey.h"
    #include "cards/Diamond_Grey.h"
    #include "cards/Club_Grey.h"
    #include "cards/Spade_Grey.h"
    
    #include "cards/Card_Front_Normal.h"
    #include "cards/Card_Front_Highlight.h"
    #include "cards/Card_Back.h"
    #include "cards/Card_Placeholder.h"

    const uint8_t * const Suits[] = { 
        Spade,
        Club,
        Diamond,
        Heart,
    };

    const uint8_t * const Suits_Grey[] = { 
        Spade_Grey,
        Club_Grey,
        Diamond_Grey,
        Heart_Grey,
    };
    
}