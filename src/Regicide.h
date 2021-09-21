#pragma once

#include "Pokitto.h"
#include <LibAudio>
#include <LibSchedule>
#include "entities/Entities.h"
#include "images/Images.h"
#include "utils/Enums.h"
#include "utils/GameCookie.h"
#include "music/Music.h"

using PC=Pokitto::Core;
using PD=Pokitto::Display;
using PB=Pokitto::Buttons;


class Game {

    private:

        SplashScreenVariables splashScreenVariables;
        GameState gameState = GameState::Splash;
        GameState nextGameState;
        GamePlay gamePlay;
        GameCookie *cookie;
        Deck deck;
        Hand hands[4];
        Attacks attacks;
        EnemyKilledType enemyKilled = EnemyKilledType::None;
        uint8_t nextCounter = 0;

        File mainThemeFile;      

    public:

        void setup(GameCookie *cookie);
        void loop();

    private:

        void splashScreen();
        void game_Init();
        void game();
        void title_Init();
        void title();
        void numberOfPlayers_Init();
        void numberOfPlayers();
        void winner_Init();
        void winner();
        void gameSwapPlayers_Init();
        void gameSwapPlayers();
        bool changeAttackers(Card& currentEnemy);
        void discardPlayersCards(Hand &currentHand);
        bool setCardCursor(Hand &currentHand);

        void playTheme(Themes theme);
        void muteTheme();
        void playSoundEffect(SoundEffect soundEffect);
        
        void renderCard_Side(int16_t x, int16_t y);
        void renderCard(int16_t x, int16_t y, Card &card, bool highlight, bool logo);
        void renderPlayerHand(uint8_t playerIdx, int16_t x, int16_t y, uint8_t selecteIndex, uint8_t cardsToSuppress);
        void renderCastleDeck(int16_t x, int16_t y, uint8_t numberOfCards, bool displayTopCard, bool shakeTopCard);
        void renderTavernDeck(int16_t x, int16_t y, uint8_t numberOfCards);
        void renderDiscardDeck(int16_t x, int16_t y, uint8_t numberOfCards, bool displayTopCard);
        void renderAttackButton(ButtonState state);
        void renderYieldButton(ButtonState state);
        void renderReplenishButton(ButtonState state, Hand &currentHand);
        void renderLegend(Hand &currentHand, Card &currentEnemy);
        void renderCardCount(int16_t x, int16_t y, uint8_t numberOfCards);
        void renderCaption(Caption caption1);
        void renderCaption(Caption caption1, Caption caption2);
        void renderScreen(Hand &currentHand, Card &currentEnemy);

};

