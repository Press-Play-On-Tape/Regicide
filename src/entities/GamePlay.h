#pragma once

#include "Card.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct GamePlay {

    private:

        uint8_t currentPlayer = 0;
        uint8_t numberOfPlayers = 0;
        uint8_t healthToDiscard = 0;


        bool thisEnemy_suits[4];


    public: // Properties

        uint8_t getCurrentPlayer()                  { return this->currentPlayer; }
        uint8_t getNumberOfPlayers()                { return this->numberOfPlayers; }
        uint8_t getHealthToDiscard()                { return this->healthToDiscard; }

        void setCurrentPlayer(uint8_t val)          { this->currentPlayer = val; }
        void setNumberOfPlayers(uint8_t val)        { this->numberOfPlayers = val; }
        void setHealthToDiscard(uint8_t val)        { this->healthToDiscard = val; }

    public: // Methods

        void init(GameMode gameMode) {

            this->numberOfPlayers = static_cast<uint8_t>(gameMode);
            this->currentPlayer = 0;

            for (uint8_t i = 0; i < 4; i++) {

                this->thisEnemy_suits[i] = false;

            }

        }

};