#include "Regicide.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::gameOver_Init() {

    this->gameState = GameState::GameOver;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::gameOver() {

    // Handle player actions ..

    if (PC::buttons.pressed(BTN_A)) { 

        this->gameState = GameState::Game_Init;

    }         


    // Render page ..

    PD::setCursor(0, 0);
    PD::setColor(6);
    PD::print("You Died. Game Over!");

}
