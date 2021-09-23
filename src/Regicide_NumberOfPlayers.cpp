#include "Regicide.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::numberOfPlayers_Init() { 

    this->gameState = GameState::NoOfPlayers;
    this->gamePlay.setNumberOfPlayers(1);

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::numberOfPlayers() { 

    if (PC::buttons.pressed(BTN_RIGHT)) {

        this->gamePlay.incSelectorIndex();

    }         

    if (PC::buttons.pressed(BTN_LEFT)) {

        this->gamePlay.decSelectorIndex();

    }         

    if (PC::buttons.pressed(BTN_A)) { 

        switch (this->gamePlay.getSelectorIndex()) {

            case 0:
                this->gameState = GameState::Instructions_Init;
                break;


            case 1 ... 2:
                this->gamePlay.setNumberOfPlayers(this->gamePlay.getSelectorIndex());
                this->gameState = GameState::Game_Init;
                break;

        }

    }         

    if (PC::buttons.pressed(BTN_B)) { 

        this->gameState = GameState::Title;

    }    
  

    //  Render the state ..

    PD::drawBitmap(0, 0, Images::Background);
    PD::drawBitmap(110, 0, Images::Background, NOROT, FLIPH);
    PD::drawBitmap(41, 1, Images::Title_01_Top);
    PD::drawBitmap(24, 113, Images::Title_01_Bot);
    PD::drawBitmap(36, 92, Images::Arrow_Left);

    switch (this->gamePlay.getSelectorIndex()) {

        case 0:
            PD::drawBitmap(48, 86, Images::HowToPlay);
            break;


        case 1 ... 2:
            PD::drawBitmap(73, 84, Images::NumberOfPlayers);
            PD::drawBitmap(56, 86, Images::NumberOfPlayers_Digits[this->gamePlay.getSelectorIndex() - 1]);
            break;

    }

    PD::drawBitmap(176, 92, Images::Arrow_Right);

}
