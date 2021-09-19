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

    PD::drawBitmap(0, 0, Images::Background);
    PD::drawBitmap(110, 0, Images::Background, NOROT, FLIPH);

    uint16_t frameCount = PC::frameCount % 96;

    switch (frameCount) {

        case 0 ... 9:
            PD::drawBitmap(41, 1, Images::Title_01_Tops[frameCount / 2]);
            PD::drawBitmap(24, 113, Images::Title_01_Bots[frameCount / 2]);
            break;

        default:
            PD::drawBitmap(41, 1, Images::Title_01_Top);
            PD::drawBitmap(24, 113, Images::Title_01_Bot);
            break;

    }

    PD::drawBitmap(25, 85, Images::Winner);

}
