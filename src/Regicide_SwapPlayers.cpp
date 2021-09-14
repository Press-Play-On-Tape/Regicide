#include "Regicide.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::gameSwapPlayers_Init() {

    this->gameState = GameState::Game_SwapPlayers;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::gameSwapPlayers() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Game_Step1_Play;

    }         


    // Render page ..

    PD::fillScreen(3);
    
    PD::setCursor(7, 14);
    PD::setColor(6);
    PD::print("Swap Players");

}
