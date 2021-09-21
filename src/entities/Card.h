#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct Card {

    private:

        uint8_t cardIndex;
        uint8_t attack;
        uint8_t health;

        bool shield = false;
        uint8_t shieldVal = 0;

    public: // Properties

        uint8_t getCardIndex()              { return this->cardIndex; }
        uint8_t getAttack()                 { return this->attack; }
        uint8_t getHealth()                 { return this->health; }

        bool getShield()                    { return this->shield; }
        uint8_t getShieldVal()              { return this->shieldVal; }
        
        void setCardIndex(uint8_t val)      { this->cardIndex = val; }
        void setAttack(uint8_t val)         { this->attack = val; }
        void setHealth(uint8_t val)         { this->health = val; }

        void setShield(bool val)            { this->shield = val; }
        void setShieldVal(uint8_t val)      { this->shieldVal = val; }

    public: // Methods 

        void init(uint8_t cardIndex) {

            this->cardIndex = cardIndex;

        }

        void init(uint8_t cardIndex, uint8_t attack, uint8_t health) {

            this->cardIndex = cardIndex;
            this->attack = attack;
            this->health = health;

            this->shield = false;
            this->shieldVal = 0;

        }

        CardSuit getSuit() {

            return static_cast<CardSuit>(this->cardIndex / 13);
        
        }

        uint8_t getNumber() {

            return this->cardIndex % 13;
        
        }

        uint8_t getHealthPoints() {

            switch (this->cardIndex % 13) {

                case 0 ... 9:
                    return (this->cardIndex % 13) + 1;

                case Cards::Jack:
                    return 10;

                case Cards::Queen:
                    return 15;

                case Cards::King:
                    return 20;

            }

            return 0;

        }

        void print() {

            #ifdef DEBUG

                if (this->cardIndex == Cards::NoCard) {
                    
                    printf("-- ");

                }
                else {
                        
                    switch (this->cardIndex % 13) {

                        case 0:    
                            printf("A");
                            break;

                        case 1 ... 8:    
                            printf("%i", (this->cardIndex % 13) + 1);
                            break;

                        case 9:    
                            printf("T");
                            break;

                        case 10:    
                            printf("J");
                            break;

                        case 11:    
                            printf("Q");
                            break;

                        case 12:    
                            printf("K");
                            break;
                    
                    }

                    switch (this->cardIndex / 13) {

                        case 0:    
                            printf("S");
                            break;

                        case 1:    
                            printf("C");
                            break;

                        case 2:    
                            printf("D");
                            break;

                        case 3:    
                            printf("H");
                            break;
                    
                    }
                    
                    printf(" ");

                }
                
            #endif

        }

};