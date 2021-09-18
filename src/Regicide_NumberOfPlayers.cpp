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

    if (PC::buttons.pressed(BTN_UP) && this->gamePlay.getNumberOfPlayers() < 4) { 

        this->gamePlay.setNumberOfPlayers(this->gamePlay.getNumberOfPlayers() + 1);

    }         

    if (PC::buttons.pressed(BTN_DOWN) && this->gamePlay.getNumberOfPlayers() > 1) { 

        this->gamePlay.setNumberOfPlayers(this->gamePlay.getNumberOfPlayers() - 1);

    }         

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Game_Init;

    }         


    //this->gamePlay.getNumberOfPlayers()
  

    //  Render the state ..

    PD::drawBitmap(0, 0, Images::Background);
    PD::drawBitmap(24, 1, Images::Title_01);
    PD::drawBitmap(49, 85, Images::NumberOfPlayers_Digits[this->gamePlay.getNumberOfPlayers() - 1]);
    PD::drawBitmap(78, 84, Images::NumberOfPlayers);

}
