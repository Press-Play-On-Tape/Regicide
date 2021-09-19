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


        bool thisEnemy_suits[4];


    public: // Properties

        uint8_t getCurrentPlayer()                  { return this->currentPlayer; }
        uint8_t getNumberOfPlayers()                { return this->numberOfPlayers; }
        uint8_t getHealthToDiscard()                { return this->healthToDiscard; }

        uint16_t getCounter()                       { return this->counter; }
        uint8_t getHeartsCounter()                  { return this->heartsCounter; }
        uint8_t getDiamondsCounter()                { return this->diamondsCounter; }
        uint8_t getCardCursor()                     { return this->cardCursor; }

        void setCurrentPlayer(uint8_t val)          { this->currentPlayer = val; }
        void setNumberOfPlayers(uint8_t val)        { this->numberOfPlayers = val; }
        void setHealthToDiscard(uint8_t val)        { this->healthToDiscard = val; }

        void setCounter(uint16_t val)               { this->counter = val; }
        void setHeartsCounter(uint8_t val)          { this->heartsCounter = val; }
        void setDiamondsCounter(uint8_t val)        { this->diamondsCounter = val; }
        void setCardCursor(uint8_t val)             { this->cardCursor = val; }

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

        void init(GameMode gameMode) {

            this->numberOfPlayers = static_cast<uint8_t>(gameMode);
            this->currentPlayer = 0;

            for (uint8_t i = 0; i < 4; i++) {

                this->thisEnemy_suits[i] = false;

            }

        }

};