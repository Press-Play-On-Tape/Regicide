#pragma once

#include "Card.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct Hand {

    private:

        #define HAND_SIZE 15

        Card cards[HAND_SIZE];
        bool mark[HAND_SIZE];

        uint8_t playerNumber;
        int8_t cardIndex;
        uint8_t maxNumberOfCards;
        uint8_t shieldValue;

        bool suits[4];
        CardSuit enemyCardSuit;
        uint8_t cardsAdded;


    public: // properties

        int8_t getCardIndex()                       { return this->cardIndex; }
        uint8_t getMaxNumberOfCards()               { return this->maxNumberOfCards; }
        CardSuit getEnemyCardSuit()                 { return this->enemyCardSuit; }
        uint8_t getShieldValue()                    { return this->shieldValue; }
        uint8_t getCardsAdded()                     { return this->cardsAdded; }

        void setCardIndex(int8_t val)               { this->cardIndex = val; }
        void setMaxNumberOfCards(uint8_t val)       { this->maxNumberOfCards = val; }
        void setEnemyCardSuit(CardSuit val)         { this->enemyCardSuit = val; }
        void setShieldValue(uint8_t val)            { this->shieldValue = val; }
        void setCardsAdded(uint8_t val)             { this->cardsAdded = val; }

    public:

        void init(uint8_t playerNumber, uint8_t maxNumberOfCards) {

            this->cardIndex = -1;
            this->maxNumberOfCards = maxNumberOfCards;
            this->playerNumber = playerNumber;
            this->enemyCardSuit = CardSuit::Clubs;
            this->shieldValue = 0;
            this->cardsAdded = 0;

            for (uint8_t i = 0; i < HAND_SIZE; i++) {

                this->cards[i].init(Cards::NoCard);
                this->mark[i] = false;

            }

            for (uint8_t i = 0; i < 4; i++) {

                this->suits[i] = false;

            }

        }

        Card& getCard(uint8_t index) {

            return cards[index];

        }

        void markCard(uint8_t index) {

            this->mark[index] = !this->mark[index];

            for (uint8_t i = 0; i < 4; i++) {
                this->suits[i] = false;
            }

            for (uint8_t i = 0; i <= this->cardIndex; i++) {
                
                if (this->mark[i]) {

                    CardSuit suit = this->cards[i].getSuit();

                    if (suit != enemyCardSuit) {
                        this->suits[static_cast<uint8_t>(suit)] = true;
                    }

                }

            }


            // Save shield value ..

            this->shieldValue = 0;

            if (isValidAttack()) {

                if ((this->enemyCardSuit != CardSuit::Spades && this->getMarkedSuit(CardSuit::Spades))) {
                    this->shieldValue = this->getAttackValue(false);
                }

            }

        }

        bool isMarked(uint8_t index) {

            return this->mark[index];

        }

        void clearMarks() {

            for (uint8_t i = 0; i < HAND_SIZE; i++) {

                this->mark[i] = false;

            }

            for (uint8_t i = 0; i < 4; i++) {

                this->suits[i] = false;

            }

        }

        void addCard(Card &card) {

            this->cardIndex++;
            this->cards[cardIndex].init(card.getCardIndex());

        }

        bool getMarkedSuit(CardSuit suit) {

            return this->suits[static_cast<uint8_t>(suit)];

        }

        uint8_t getMarkedCardCount() {

            uint8_t count = 0;
                
            for (uint8_t i = 0; i < HAND_SIZE; i++) {

                if (this->mark[i]) {

                    count++;

                }

            }

            return count;

        }

        uint8_t getAttackValue() {

            return getAttackValue(true);

        }

        uint8_t getAttackValue(bool doublePoints) {

            bool hasClub = false;

            
            // Do we have any clubs ?

            if (this->enemyCardSuit != CardSuit::Clubs) {
                    
                for (uint8_t i = 0; i < this->maxNumberOfCards; i++) {

                    if (this->mark[i] && this->cards[i].getSuit() == CardSuit::Clubs) {

                        hasClub = true;
                        break;

                    }

                }

            }


            // Calculate attack value ..

            uint8_t val = 0;

            for (uint8_t i = 0; i < this->maxNumberOfCards; i++) {

                if (this->mark[i]) {

                    switch (this->cards[i].getNumber()) {

                        case 0 ... 9:

                            val = val + this->cards[i].getNumber() + 1;
                            if (doublePoints && hasClub) val = val + this->cards[i].getNumber() + 1;
                            break;

                        case Cards::Jack:

                            val = val + 10;
                            if (doublePoints && hasClub) val = val + 10;
                            break;

                        case Cards::Queen:

                            val = val + 15;
                            if (doublePoints && hasClub) val = val + 15;
                            break;

                        case Cards::King:

                            val = val + 20;
                            if (doublePoints && hasClub) val = val + 20;
                            break;
                        
                    }

                }

            }

            return val;

        }

        bool isValidAttack() {

            uint8_t cardsSelected[14];
            bool valid = false;


            // Clear out values ..

            for (uint8_t i = 0; i < 14; i++) {
                cardsSelected[i] = 0;
            }

            for (uint8_t i = 0; i < this->maxNumberOfCards; i++) {

                if (this->mark[i]) {
                    
                    Card &card = this->cards[i];

                    switch (card.getNumber()) {

                        case Cards::Ace ... Cards::King:
                            cardsSelected[card.getNumber()]++;
                            break;

                    }

                }

            }


            // How many different card types are there?

            uint8_t count = 0;
            uint8_t countIdx = 0;

            for (uint8_t i = 0; i < 14; i++) {

                if (cardsSelected[i] > 0) {

                    count++;
                    countIdx = i;

                }

            }

            switch (count) {
                
                case 0:
                    return false;

                case 1:
                    return (cardsSelected[countIdx] * (countIdx + 1) <= 10) || (cardsSelected[countIdx] == 1 && countIdx >= 10);

                case 2:
                    return (cardsSelected[0] > 0 && cardsSelected[countIdx] == 1 && countIdx < 13);

                default:
                    return false;

            }

            return false;

        }

        void removeCard(uint8_t index) {

            for (uint8_t i = index; i <= this->cardIndex; i++) {

                this->cards[i].init(this->cards[i + 1].getCardIndex());
                this->mark[i] = this->mark[i+ 1];

            }

            this->cards[this->cardIndex].init(Cards::NoCard);
            this->cardIndex--;

        }

        uint8_t getHealth() {

            uint8_t health = 0;

            for (uint8_t i = 0; i <= this->cardIndex; i++) {

                health = health + this->cards[i].getHealthPoints();

            }

            return health;

        }

        void incCardsAdded() {

            this->cardsAdded++;
            
        }

        void decCardsAdded() {

            this->cardsAdded--;
            
        }

        void print() {

            #ifdef DEBUG
                
                printf("Player: %i, ", this->playerNumber);

                for (uint8_t i = 0; i < this->cardIndex; i++) {

                    if (this->mark[i]) printf("*");
                    this->cards[i].print();

                }

                printf("\n");

            #endif

        }

};