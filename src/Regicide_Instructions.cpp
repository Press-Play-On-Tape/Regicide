#include "Regicide.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::instructions_Init() {

    this->gameState = GameState::Instructions;
    this->gamePlay.setCounter(1);

    if (this->instructionFile.openRO(Constants::instructions[this->gamePlay.getCounter() - 1])) {
        this->instructionFile.read(PD::getBuffer(), 2);
        this->instructionFile.read(PD::getBuffer(), (220 * 176 / 2));
    }

}   

void Game::instructions() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::NoOfPlayers_Init;

    }         

    if (PC::buttons.pressed(BTN_LEFT)) { 

        this->gamePlay.decCounter();
        
        if (this->gamePlay.getCounter() == 0) {

            this->gameState = GameState::NoOfPlayers_Init;

        }
        else {
            
            if (this->instructionFile.openRO(Constants::instructions[this->gamePlay.getCounter() - 1])) {
                this->instructionFile.read(PD::getBuffer(), 2);
                this->instructionFile.read(PD::getBuffer(), (220 * 176 / 2));
            }

        }

    }         

    if (PC::buttons.pressed(BTN_RIGHT)) { 

        this->gamePlay.incCounter();
        
        if (this->gamePlay.getCounter() == 16) {

            this->gameState = GameState::NoOfPlayers_Init;

        }
        else {

            if (this->instructionFile.openRO(Constants::instructions[this->gamePlay.getCounter() - 1])) {
                this->instructionFile.read(PD::getBuffer(), 2);
                this->instructionFile.read(PD::getBuffer(), (220 * 176 / 2));
            }

        }

    }         

}
