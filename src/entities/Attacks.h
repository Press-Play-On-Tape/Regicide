#pragma once

#include "Attack.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct Attacks {

    private:

        Attack attacks[6];
        uint8_t x;
        uint8_t y;


    public: // Properties

        Attack& getAttack(uint8_t index)        { return this->attacks[index]; }


    public: // Methods

        void launchAttach() {

            for (uint8_t i = 0; i < 6; i++) {

                if (this->attacks[i].getIndex() == 0) {

                    this->attacks[i].setX(random(20, 40));
                    this->attacks[i].setY(random(20, 60));
                    this->attacks[i].setIndex(41); // 6
                    break;

                }

            }

        }

        void update() {

            for (uint8_t i = 0; i < 6; i++) {

                this->attacks[i].update();

            }

        }

};