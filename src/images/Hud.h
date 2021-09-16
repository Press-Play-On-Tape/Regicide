#pragma once

namespace Images {

    #include "hud/Button_Attack.h"
    #include "hud/Button_Attack_Grey.h"
    #include "hud/Button_Attack_Highlight.h"
    #include "hud/Button_Yield.h"
    #include "hud/Button_Yield_Grey.h"
    #include "hud/Button_Yield_Highlight.h"
    #include "hud/Counter.h"
    #include "hud/Counter.h"
    #include "hud/AttackHealth.h"
    #include "hud/Banner_Castle.h"
    #include "hud/Banner_Discard.h"
    #include "hud/Banner_Tavern.h"
    
    #include "hud/smallDigits/Number_Small_00.h"
    #include "hud/smallDigits/Number_Small_01.h"
    #include "hud/smallDigits/Number_Small_02.h"
    #include "hud/smallDigits/Number_Small_03.h"
    #include "hud/smallDigits/Number_Small_04.h"
    #include "hud/smallDigits/Number_Small_05.h"
    #include "hud/smallDigits/Number_Small_06.h"
    #include "hud/smallDigits/Number_Small_07.h"
    #include "hud/smallDigits/Number_Small_08.h"
    #include "hud/smallDigits/Number_Small_09.h"
    
    #include "hud/mediumDigits/Number_Medium_00.h"
    #include "hud/mediumDigits/Number_Medium_01.h"
    #include "hud/mediumDigits/Number_Medium_02.h"
    #include "hud/mediumDigits/Number_Medium_03.h"
    #include "hud/mediumDigits/Number_Medium_04.h"
    #include "hud/mediumDigits/Number_Medium_05.h"
    #include "hud/mediumDigits/Number_Medium_06.h"
    #include "hud/mediumDigits/Number_Medium_07.h"
    #include "hud/mediumDigits/Number_Medium_08.h"
    #include "hud/mediumDigits/Number_Medium_09.h"
    
    #include "hud/largeDigits/Number_Large_00.h"
    #include "hud/largeDigits/Number_Large_01.h"
    #include "hud/largeDigits/Number_Large_02.h"
    #include "hud/largeDigits/Number_Large_03.h"
    #include "hud/largeDigits/Number_Large_04.h"
    #include "hud/largeDigits/Number_Large_05.h"
    #include "hud/largeDigits/Number_Large_06.h"
    #include "hud/largeDigits/Number_Large_07.h"
    #include "hud/largeDigits/Number_Large_08.h"
    #include "hud/largeDigits/Number_Large_09.h"
    #include "hud/largeDigits/Number_Large_10.h"

    #include "hud/Legend_Damage_Grey.h"
    #include "hud/Legend_Damage_Highlight.h"
    #include "hud/Legend_Draw_Grey.h"
    #include "hud/Legend_Draw_Highlight.h"
    #include "hud/Legend_Heal_Grey.h"
    #include "hud/Legend_Heal_Highlight.h"
    #include "hud/Legend_Shield_Grey.h"
    #include "hud/Legend_Shield_Highlight.h"

    const uint8_t * const SmallNumbers[] = { 
        Number_Small_00,
        Number_Small_01,
        Number_Small_02,
        Number_Small_03,
        Number_Small_04,
        Number_Small_05,
        Number_Small_06,
        Number_Small_07,
        Number_Small_08,
        Number_Small_09,
    };

    const uint8_t * const MediumNumbers[] = { 
        Number_Medium_00,
        Number_Medium_01,
        Number_Medium_02,
        Number_Medium_03,
        Number_Medium_04,
        Number_Medium_05,
        Number_Medium_06,
        Number_Medium_07,
        Number_Medium_08,
        Number_Medium_09,
    };

    const uint8_t * const LargeNumbers_Inverted[] = { 
        Number_Large_00,
        Number_Large_01,
        Number_Large_02,
        Number_Large_03,
        Number_Large_04,
        Number_Large_05,
        Number_Large_06,
        Number_Large_07,
        Number_Large_08,
        Number_Large_09,
        Number_Large_10,
    };

    const uint8_t * const Buttons_Attack[] = { 
        Button_Attack,
        Button_Attack_Grey,
        Button_Attack_Highlight
    };

    const uint8_t * const Buttons_Yield[] = { 
        Button_Yield,
        Button_Yield_Grey,
        Button_Yield_Highlight
    };

}