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

    if (PC::buttons.pressed(BTN_RIGHT) && this->gamePlay.getNumberOfPlayers() < 2) { 

        this->gamePlay.setNumberOfPlayers(this->gamePlay.getNumberOfPlayers() + 1);

    }         

    if (PC::buttons.pressed(BTN_LEFT) && this->gamePlay.getNumberOfPlayers() > 1) { 

        this->gamePlay.setNumberOfPlayers(this->gamePlay.getNumberOfPlayers() - 1);

    }         

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Game_Init;

    }         


    //this->gamePlay.getNumberOfPlayers()
  

    //  Render the state ..

    PD::drawBitmap(0, 0, Images::Background);
    PD::drawBitmap(110, 0, Images::Background, NOROT, FLIPH);
    PD::drawBitmap(41, 1, Images::Title_01_Top);
    PD::drawBitmap(24, 113, Images::Title_01_Bot);
    PD::drawBitmap(46, 92, Images::Arrow_Left);
    PD::drawBitmap(56, 86, Images::NumberOfPlayers_Digits[this->gamePlay.getNumberOfPlayers() - 1]);
    PD::drawBitmap(73, 84, Images::NumberOfPlayers);
    PD::drawBitmap(166, 92, Images::Arrow_Right);

}
