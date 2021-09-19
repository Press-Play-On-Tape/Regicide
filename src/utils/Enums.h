#pragma once

#define DEBUG
#define _SOUNDS
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
    constexpr uint8_t DealDelay = 8;
    constexpr uint8_t CardWidth = 40;
    constexpr uint8_t CardWidth_Half = 20;
    constexpr uint8_t NoSelection = 255;

    constexpr uint8_t AttackMax = 4;
    constexpr uint8_t AttackLength = 7 * 3;
    constexpr uint8_t AttackInterval = 15;

}

enum class GameMode : uint8_t {
    NoPlayers,
    OnePlayer,
    TwoPlayers,
};

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
    Game_Step3_DealDamage,
    Game_Step4_SufferDamage,
    Game_Step5_EnemyDead,
    Game_SwapPlayers_Init,
    Game_SwapPlayers,
    GameOver_Init,
    GameOver,
    Winner_Init,
    Winner,
};

enum class SoundEffect : uint8_t {
    Tone_00,
    Tone_01,
    Tone_02,
    Tone_03,
    Tone_04,
    Tone_05,
    Tone_06,
    Tone_07,
    Tone_08,
    Tone_09,
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
