#pragma once

#include "Card.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct GamePlay {

    private:

        uint8_t currentPlayer = 0;
        uint8_t numberOfPlayers = 0;
        uint8_t healthToDiscard = 0;

        uint8_t cardCursor = 0;

        uint16_t counter = 0;
        uint8_t heartsCounter = 0;
        uint8_t diamondsCounter = 0;
        uint8_t enemyDiscardCounter = 0;
        uint8_t enemyTavernCounter = 0;
        uint8_t replenish = 2;

        Card prevEnemy;

        bool thisEnemy_suits[4];


    public: // Properties

        uint8_t getCurrentPlayer()                      { return this->currentPlayer; }
        uint8_t getNumberOfPlayers()                    { return this->numberOfPlayers; }
        uint8_t getHealthToDiscard()                    { return this->healthToDiscard; }

        uint16_t getCounter()                           { return this->counter; }
        uint8_t getHeartsCounter()                      { return this->heartsCounter; }
        uint8_t getDiamondsCounter()                    { return this->diamondsCounter; }
        uint8_t getCardCursor()                         { return this->cardCursor; }
        uint8_t getEnemyDiscardCounter()                { return this->enemyDiscardCounter; }
        uint8_t getEnemyTavernCounter()                 { return this->enemyTavernCounter; }
        uint8_t getReplenish()                          { return this->replenish; }

        Card& getPreviousEnemy()                        { return this->prevEnemy; }

        void setCurrentPlayer(uint8_t val)              { this->currentPlayer = val; }
        void setNumberOfPlayers(uint8_t val)            { this->numberOfPlayers = val; }
        void setHealthToDiscard(uint8_t val)            { this->healthToDiscard = val; }

        void setCounter(uint16_t val)                   { this->counter = val; }
        void setHeartsCounter(uint8_t val)              { this->heartsCounter = val; }
        void setDiamondsCounter(uint8_t val)            { this->diamondsCounter = val; }
        void setCardCursor(uint8_t val)                 { this->cardCursor = val; }
        void setEnemyDiscardCounter(uint8_t val)        { this->enemyDiscardCounter = val; }
        void setEnemyTavernCounter(uint8_t val)         { this->enemyTavernCounter = val; }
        void setReplenish(uint8_t val)                  { this->replenish = val; }

        void setPreviousEnemy(Card val)                 { this->prevEnemy = val; }

    public: // Methods

        void decCounter() {

            if (this->counter > 0) this->counter--;

        }

        void incCounter() {

            this->counter++;

        }
        
        void decHeartsCounter() {

            if (this->heartsCounter > 0) this->heartsCounter--;

        }
        
        void decDiamondsCounter() {

            if (this->diamondsCounter > 0) this->diamondsCounter--;

        }

        void decCardCursor() {

            this->cardCursor--;

        }

        void incCardCursor() {

            this->cardCursor++;

        }

        void decEnemyDiscardCounter() {

            if (this->enemyDiscardCounter > 0) this->enemyDiscardCounter--;

        }

        void decEnemyTavernCounter() {

            if (this->enemyTavernCounter > 0) this->enemyTavernCounter--;

        }

        void init(GameMode gameMode) {

            this->numberOfPlayers = static_cast<uint8_t>(gameMode);
            this->currentPlayer = 0;
            this->replenish = 2;

            for (uint8_t i = 0; i < 4; i++) {

                this->thisEnemy_suits[i] = false;

            }

        }

};