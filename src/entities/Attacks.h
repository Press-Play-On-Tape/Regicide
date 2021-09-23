#pragma once

#include "Attack.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct Attacks {

    private:

        Attack attacks[Constants::AttackMax];
        uint8_t x;
        uint8_t y;

    public: // Properties

        Attack& getAttack(uint8_t index)        { return this->attacks[index]; }


    public: // Methods

        void launchAttach() {

            for (uint8_t i = 0; i < Constants::AttackMax; i++) {

                if (this->attacks[i].getIndex() == 0) {
                    
                    uint8_t j = i % 2;

                    this->attacks[i].setX(30);
                    this->attacks[i].setY(i % 2 == 0 ? 15 : 60);
// printf("%i\n", (uint16_t)this->attacks[i].getY()                   ); 
                    this->attacks[i].setIndex((Constants::AttackLength * 2) - 1); 
                    break;

                }

            }

        }

        void update() {

            for (uint8_t i = 0; i < Constants::AttackMax; i++) {

                this->attacks[i].update();

            }

        }

};