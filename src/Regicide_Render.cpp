#include "Regicide.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ---------------------------------------------------------------------------------------------------------------
// Render screen
// ---------------------------------------------------------------------------------------------------------------

void Game::renderScreen(Hand &currentHand, Card &currentEnemy, bool displayCastleDeckTopCard) {


    PD::fillScreen(3);


    // Upper decks ..

    PD::drawBitmap(9, 1, Images::Banner_Castle);
    this->renderCastleDeck(10, 11, this->deck.getIndex(DeckTypes::Castle) + 1, displayCastleDeckTopCard);

    PD::drawBitmap(84, 1, Images::Banner_Discard);
    this->renderDiscardDeck(85, 11, this->deck.getIndex(DeckTypes::Discard) + 1, this->gamePlay.getHeartsCounter() == 0);

    uint8_t attack = currentEnemy.getAttack() - currentHand.getShieldValue();
    PD::drawBitmap(11, 89, Images::AttackHealth);

    {
        uint8_t digits[3] = {};
        uint8_t x = 51;

        extractDigits(digits, attack);

        for (uint8_t i = 0; i < 2; ++i) {
            PD::drawBitmap(x, 89, Images::MediumNumbers[digits[i]]);
            x = x - 5;
        }

        x = 51;
        extractDigits(digits, currentEnemy.getHealth());

        for (uint8_t i = 0; i < 2; ++i) {
            PD::drawBitmap(x, 98, Images::MediumNumbers[digits[i]]);
            x = x - 5;
        }

    }    




    // Player hand ..

    PD::setCursor(0, 110);
    PD::setColor(1, 14);

    switch (this->gameState) {

        case GameState::Game_Step1_Play:
        case GameState::Game_Step4_SufferDamage:
            this->renderPlayerHand(this->gamePlay.getCurrentPlayer(), 1, 140, this->gamePlay.getCardCursor(), currentHand.getCardsAdded());
            break;
            
        case GameState::Game_Step2_Activate:
            if (this->gamePlay.getDiamondsCounter() == 0) {
                this->renderPlayerHand(this->gamePlay.getCurrentPlayer(), 1, 140, Constants::NoSelection, currentHand.getCardsAdded());
            }
            break;

        default:
            this->renderPlayerHand(this->gamePlay.getCurrentPlayer(), 1, 140, Constants::NoSelection, currentHand.getCardsAdded());
            break;

    }


    // Player number (two players only) ..

    if (this->gamePlay.getNumberOfPlayers() > 1) {
        PD::drawBitmap(1, 166, Images::Player);
        PD::drawBitmap(35, 167, Images::MediumNumbers[this->gamePlay.getCurrentPlayer() + 1]);
    }


    // Render background ..

    for (uint8_t y = 0; y < 176; y = y + 32) {

        PD::drawBitmap(147, y, Images::RightSidePanel);

    }

    PD::drawBitmap(159, 1, Images::Banner_Tavern);
    this->renderTavernDeck(160, 11, this->deck.getIndex(DeckTypes::Tavern) + 1);



    // If the players is at risk of dying, flash the health ..

    attack = currentHand.getAttackValue(false);
    if (currentHand.getHealth() < currentEnemy.getAttack() && this->gameState == GameState::Game_Step1_Play && PC::frameCount % 32 < 16) {

        PD::setColor(8);
        PD::fillRect(159, 96, 49, 7);

    }

    PD::drawBitmap(162, 88, Images::AttackHealth);

    {
        uint8_t digits[3] = {};
        uint8_t x = 202;

        extractDigits(digits, attack);

        for (uint8_t i = 0; i < 2; ++i) {
            PD::drawBitmap(x, 88, Images::MediumNumbers[digits[i]]);
            x = x - 5;
        }

        x = 202;
        extractDigits(digits, currentHand.getHealth());

        for (uint8_t i = 0; i < 2; ++i) {
            PD::drawBitmap(x, 97, Images::MediumNumbers[digits[i]]);
            x = x - 5;
        }

    }    

    this->renderLegend(currentHand);

    switch (this->gameState) {

        case GameState::Game_Step0_AddCards:
            this->renderCaption(Caption::CardAddedToYourHand);
            this->renderAttackButton(ButtonState::Disabled);
            this->renderYieldButton(ButtonState::Disabled);

            break;


        // ---------------------------------------------------------------------------------------------------------

        case GameState::Game_Step1_Play:

            this->renderCaption(Caption::AttackOrYield);
            this->renderAttackButton(this->gamePlay.getCardCursor() == Constants::CardCursor_Attack ? ButtonState::Highlighted : (currentHand.isValidAttack() ? ButtonState::Enabled : ButtonState::Disabled));
            this->renderYieldButton(this->gamePlay.getCardCursor() == Constants::CardCursor_Yield ? ButtonState::Highlighted : ButtonState::Enabled);

            break;


        // ---------------------------------------------------------------------------------------------------------

        case GameState::Game_Step2_Activate:

            if (this->gamePlay.getHeartsCounter() > 0) {

                PD::drawBitmap(168 - (this->gamePlay.getHeartsCounter() * 4), 11, Images::Card_Back);
                this->renderCaption(Caption::CardsAddedToTavern);

            }

            if (this->gamePlay.getHeartsCounter() == 0 && this->gamePlay.getDiamondsCounter() > 0) {

                PD::drawBitmap(70 + (this->gamePlay.getDiamondsCounter() * 4), 140 - (this->gamePlay.getDiamondsCounter() * 6), Images::Card_Back);
                this->renderCaption(Caption::CardAddedToYourHand);

                this->renderPlayerHand(this->gamePlay.getCurrentPlayer(), 1, 140, Constants::NoSelection, currentHand.getCardsAdded());

            }

            this->renderAttackButton(ButtonState::Disabled);
            this->renderYieldButton(ButtonState::Disabled);

            break;


        // ---------------------------------------------------------------------------------------------------------

        case GameState::Game_Step3_DealDamage:
            {        
                uint8_t attack = currentHand.getAttackValue();
                Card currentEnemy = this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle));

                if (this->gamePlay.getCounter() > 0) {

                    this->renderCaption(Caption::AttackingTheEnemy);

                    for (uint8_t i = 0; i < Constants::AttackMax; i++) {

                        if (this->attacks.getAttack(i).getIndex() > 0) {

                            Attack &attack = this->attacks.getAttack(i);
                            PD::drawBitmap(attack.getX(), attack.getY(), Images::Explosion[attack.getIndex() / (Constants::AttackLength / 7)]);

                        }

                    }

                }
                else {

                    if (attack == currentEnemy.getHealth()) {
                        this->renderCaption(Caption::EnemyDefeated, Caption::CardAddedToTavern);
                    }
                    else if (attack > currentEnemy.getHealth()) {
                        this->renderCaption(Caption::EnemyDefeated, Caption::CardAddedToDiscard);
                    }
                    else {
                        this->renderCaption(Caption::EnemyAttacked);
                    }

                }

            }

            this->renderAttackButton(ButtonState::Disabled);
            this->renderYieldButton(ButtonState::Disabled);

            break;


        // ---------------------------------------------------------------------------------------------------------

        case GameState::Game_Step4_SufferDamage:
            {        
                PD::setColor(2, 14);
                PD::setCursor(0, 120);

                //Card currentEnemy = this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle));
                uint8_t attack = currentEnemy.getAttack() - currentHand.getShieldValue();

                switch (this->gamePlay.getCounter()) {

                    case 0:
                        {
                            this->renderCaption(Caption::YouSurvivedThisRound, Caption::DiscardPoints);

                            uint8_t digits[3] = {};
                            uint8_t x = 46;

                            extractDigits(digits, this->gamePlay.getHealthToDiscard());

                            for (uint8_t i = 0; i < 2; ++i) {
                                PD::drawBitmap(x, 127, Images::MediumNumbers[digits[i]]);
                                x = x - 5;
                            }

                        }  

                        break;

                    default:

                        switch (this->gamePlay.getHealthToDiscard()) {

                            case 0:
                                this->renderCaption(Caption::YouSurvivedThisRound);
                                break;

                            default:
                                this->renderCaption(Caption::YouDied);
                                break;

                        }

                }

            }

            this->renderAttackButton(ButtonState::Disabled);
            this->renderYieldButton(ButtonState::Disabled);

            break;


        // ---------------------------------------------------------------------------------------------------------

        case GameState::Game_Step5_EnemyDead:
            this->renderCaption(Caption::EnemyDefeated);
            break;


        // ---------------------------------------------------------------------------------------------------------

        case GameState::Game_Over:
            this->renderCaption(Caption::YouDied);
            PD::setColor(8);
            PD::fillRect(0, 0, 220, 176 - this->gamePlay.getCounter());
            PD::drawBitmap(0, 176 - this->gamePlay.getCounter(), Images::Blood);
            PD::drawBitmap(41, 64 - this->gamePlay.getCounter(), Images::YouDiedText);
            break;


        // ---------------------------------------------------------------------------------------------------------

        default:

            this->renderAttackButton(ButtonState::Disabled);
            this->renderYieldButton(ButtonState::Disabled);
            break;

    }

}