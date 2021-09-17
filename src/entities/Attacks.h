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

            const uint8_t x[] = { 10, 20 };
            const uint8_t y[] = { 20, 35 };

            for (uint8_t i = 0; i < Constants::AttackMax; i++) {

                if (this->attacks[i].getIndex() == 0) {
                    
                    uint8_t j = i % 2;

                    this->attacks[i].setX(x[j] + random(-5, 5));
                    this->attacks[i].setY(y[j] + random(-5, 5));
                    this->attacks[i].setIndex(Constants::AttackLength - 1); 
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