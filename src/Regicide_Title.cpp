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
    PD::drawBitmap(27, 83, Images::Title_02);


    uint16_t frameCount = PC::frameCount % 96;

    switch (frameCount) {

        case 0 ... 9:
            PD::drawBitmap(24, 1, Images::Title_01_Highlight[frameCount / 2]);
            break;

        default:
            PD::drawBitmap(24, 1, Images::Title_01);
            break;

    }

}
