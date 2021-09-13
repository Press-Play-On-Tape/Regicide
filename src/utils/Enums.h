#pragma once

#define _DEBUG
#define _SOUNDS
#define COOKIE_INITIALISED 42

namespace Cards {

    constexpr uint8_t Ace = 0;
    constexpr uint8_t Jack = 10;
    constexpr uint8_t Queen = 11;
    constexpr uint8_t King = 12;
    constexpr uint8_t Joker = 99;
    constexpr uint8_t NoCard = 98;

}

namespace Constants {

    constexpr uint8_t MaxNumberOfCards[] = { 0, 8, 7, 6, 5 };
    constexpr uint8_t CardCursor_Attack = 100;
    constexpr uint8_t CardCursor_Yield = 101;

}

enum class GameMode : uint8_t {
    NoPlayers,
    OnePlayer,
    TwoPlayers,
    ThreePlayers,
    FourPlayers,
};

enum class GameState : uint8_t {
    Splash_Init,
    Splash,
    Title_Init,
    Title,
    Game_Init,
    Game_NewHand,
    Game_Step1_Play,
    Game_Step2_Activate,
    Game_Step3_DealDamage,
    Game_Step4_SufferDamage,
    Game_SwapPlayers_Init,
    Game_SwapPlayers,
    GameOver_Init,
    GameOver
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
    Jokers
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