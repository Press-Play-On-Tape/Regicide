#include "Regicide.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::winner_Init() {

    this->gameState = GameState::Winner;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::winner() {


    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Splash_Init;

    }         


    // Render page ..

    PD::fillScreen(3);
    
    PD::setCursor(7, 14);
    PD::setColor(6);
    PD::print("You Win!");

}
