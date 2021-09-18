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

        uint8_t currentPlayer = this->gamePlay.getCurrentPlayer();
        Hand &currentHand = this->hands[currentPlayer];

        if (currentHand.getCardsAdded() > 0) {
            dealCounter = (Constants::DealDelay * currentHand.getCardsAdded()) + (Constants::DealDelay - 2);
            this->gameState = GameState::Game_Step0_AddCards;
        }
        else {
            this->gameState = GameState::Game_Step1_Play;
        } 

    }         


    // Render page ..

    PD::drawBitmap(0, 0, Images::Background);
    PD::drawBitmap(24, 1, Images::Title_01);
    PD::drawBitmap(25, 85, Images::SwapPlayers);

}
