#include "Regicide.h"
//#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::setup(GameCookie *cookie) {

    this->cookie = cookie;

}

void Game::loop() {

    PD::clear();
    PC::buttons.pollButtons();

    switch (this->gameState) {

        case GameState::Splash:
            this->splashScreen();
            break;

        case GameState::Title_Init:
            this->title_Init();
            [[fallthrough]]

        case GameState::Title:
            this->title();
            break;

        case GameState::Instructions_Init:
            this->instructions_Init();
            [[fallthrough]]

        case GameState::Instructions:
            this->instructions();
            break;

        case GameState::NoOfPlayers_Init:
            this->numberOfPlayers_Init();
            [[fallthrough]]

        case GameState::NoOfPlayers:
            this->numberOfPlayers();
            break;

        case GameState::Game_Init:
            this->game_Init();
            [[fallthrough]]

        case GameState::Game_NewHand:
        case GameState::Game_Step0_AddCards:
        case GameState::Game_Step1_Play:
        case GameState::Game_Step2_Activate:
        case GameState::Game_Step3_DealDamage_Init:
        case GameState::Game_Step3_DealDamage_DeadEnemy:
        case GameState::Game_Step4_SufferDamage:
        case GameState::Game_Step5_EnemyDead:
        case GameState::Game_Over:
            this->game();
            break;

        case GameState::Game_SwapPlayers_Init:
            this->gameSwapPlayers_Init();
            [[fallthrough]]

        case GameState::Game_SwapPlayers:
            this->gameSwapPlayers();
            break;

        case GameState::Winner_Init:
            this->winner_Init();
            [[fallthrough]]

        case GameState::Winner:
            this->winner();
            break;

    }

}
