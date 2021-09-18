#include "Regicide.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title_Init() {

    this->gameState = GameState::Title;
    this->playTheme();

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::title() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::NoOfPlayers_Init;

    }         


    // Render page ..

    PD::drawBitmap(0, 0, Images::Background);
    PD::drawBitmap(24, 1, Images::Title_01);
    PD::drawBitmap(27, 84, Images::Title_02);

}
