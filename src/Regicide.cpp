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
            this->title();
            break;

        case GameState::Title:
            this->title();
            break;

        case GameState::Game_Init:
            this->game_Init();
            this->game();
            break;

        case GameState::Game_NewHand:
        case GameState::Game_Step0_AddCards:
        case GameState::Game_Step1_Play:
        case GameState::Game_Step2_Activate:
        case GameState::Game_Step3_DealDamage:
        case GameState::Game_Step4_SufferDamage:
        case GameState::Game_Step5_EnemyDead:
            this->game();
            break;

        case GameState::Game_SwapPlayers_Init:
            this->gameSwapPlayers_Init();
            this->gameSwapPlayers();
            break;

        case GameState::Game_SwapPlayers:
            this->gameSwapPlayers();
            break;

        case GameState::GameOver_Init:
            this->gameOver_Init();
            this->gameOver();
            break;

        case GameState::GameOver:
            this->gameOver();
            break;

        case GameState::Winner_Init:
            this->winner_Init();
            this->winner();
            break;

        case GameState::Winner:
            this->winner();
            break;

    }

}
