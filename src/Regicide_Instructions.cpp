#include "Regicide.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::instructions_Init() {

    this->gameState = GameState::Instructions;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::instructions() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::NoOfPlayers_Init;

    }         


    // Render page ..

    PD::fillScreen(13);
    PD::setColor(1);
    PD::fillRect(0, 0, 220, 20);

    PD::drawBitmap(0, 12, Images::Mountains);
    PD::drawBitmap(110, 12, Images::Mountains, NOROT, FLIPH);

    PD::setColor(8);
    PD::drawFastVLine(6, 0, 176);
    PD::drawFastVLine(8, 0, 176);
    PD::fillRect(10, 0, 25, 176);
    PD::drawFastVLine(34, 0, 176);
    PD::drawFastVLine(36, 0, 176);

}
