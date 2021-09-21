#pragma once

#define _DEBUG
#define SOUNDS
#define COOKIE_INITIALISED 42

namespace Cards {

    constexpr uint8_t Ace = 0;
    constexpr uint8_t Jack = 10;
    constexpr uint8_t Queen = 11;
    constexpr uint8_t King = 12;
    constexpr uint8_t NoCard = 98;

}

namespace Constants {

    constexpr uint8_t MaxNumberOfCards[] = { 0, 8, 7, 6, 5 };
    constexpr uint8_t CardCursor_Attack = 100;
    constexpr uint8_t CardCursor_Yield = 101;
    constexpr uint8_t CardCursor_Replenish = 102;
    constexpr uint8_t DealDelay = 8;
    constexpr uint8_t CardWidth = 40;
    constexpr uint8_t CardWidth_Half = 20;
    constexpr uint8_t NoSelection = 255;

    constexpr uint8_t AttackMax = 4;
    constexpr uint8_t AttackLength = 2 * 4;
    constexpr uint8_t AttackInterval = 10;

    constexpr uint8_t GameOver_Delay = 176 + 72;

}

enum class GameState : uint8_t {
    Splash_Init,
    Splash,
    Title_Init,
    Title,
    NoOfPlayers_Init,
    NoOfPlayers,
    Game_Init,
    Game_NewHand,
    Game_Step0_AddCards,
    Game_Step1_Play,
    Game_Step2_Activate,
    Game_Step3_DealDamage_Init,
    Game_Step3_DealDamage_DeadEnemy,
    Game_Step4_SufferDamage,
    Game_Step5_EnemyDead,
    Game_SwapPlayers_Init,
    Game_SwapPlayers,
    Game_Over,
    Winner_Init,
    Winner,
};

enum class SoundEffect : uint8_t {
    Deal,
    EnemyDeath,
};

enum class CardSuit : uint8_t {
    Spades,
    Clubs,
    Diamonds,
    Hearts,
};

enum class DeckTypes : uint8_t {
    Castle,
    Tavern,
    Discard
};

enum class ButtonState : uint8_t {
    Enabled,
    Disabled,
    Highlighted
};

enum class Caption : uint8_t {
    AttackingTheEnemy,
    AttackOrYield,
    DiscardPoints,
    EnemyAttacked,
    EnemyDefeated,
    CardAddedToDiscard,
    CardAddedToYourHand,
    CardAddedToTavern,
    CardsAddedToTavern,
    YouDied,
    YouSurvived,
    YouSurvivedThisRound,
    None
};

enum class EnemyKilledType : uint8_t {
    None,
    Tavern,
    Discard,
};

enum class Themes : uint8_t {
    Main,
    Winner
};

enum class SoundEffects : uint8_t {
    Both,
    Music,
    SFX,
    None
};

inline SoundEffects &operator++(SoundEffects &c ) {
    c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) + 1) % 4 );
    return c;
}

inline SoundEffects operator++(SoundEffects &c, int ) {
    SoundEffects result = c;
    ++c;
    return result;
}

inline SoundEffects &operator--(SoundEffects &c ) {
    if (static_cast<uint8_t>(c) > 0) {
        c = static_cast<SoundEffects>( (static_cast<uint8_t>(c) - 1) % 4 );
    }
    else {
        c = static_cast<SoundEffects>( 3 );
    }
    return c;
}

inline SoundEffects operator--(SoundEffects &c, int ) {
    SoundEffects result = c;
    --c;
    return result;
}