#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include <LibSchedule>
#include "entities/Entities.h"
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/GameCookie.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        SplashScreenVariables splashScreenVariables;
        GameState gameState = GameState::Splash;
        GamePlay gamePlay;
        GameCookie *cookie;
        Deck deck;
        Hand hands[4];




        uint16_t dealCounter = 0;
        uint8_t cardCursor = 0;



    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen();
        void game_Init();
        void game();
        void title_Init();
        void title();
        void gameOver_Init();
        void gameOver();
        void gameSwapPlayers_Init();
        void gameSwapPlayers();

        void playTheme();
        void muteTheme();
        void playSoundEffect(SoundEffect soundEffect);
        
        void renderCard(int16_t x, int16_t y, Card &card, bool highlight);
        void renderPlayerHand(uint8_t playerIdx, int16_t x, int16_t y, uint8_t selecteIndex);
        void renderCastleDeck(int16_t x, int16_t y);
        void renderTavernDeck(int16_t x, int16_t y);
        void renderDiscardDeck(int16_t x, int16_t y);
        void renderAttackButton(ButtonState state);
        void renderYieldButton(ButtonState state);


};

