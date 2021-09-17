#include "Regicide.h"
#include "images/images.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game_Init() {

    this->gameState = GameState::Game_NewHand;
    this->gamePlay.init(GameMode::TwoPlayers);
    this->deck.init(GameMode::TwoPlayers);

    this->deck.print();

    uint16_t dealCounter = 0;

    for (uint8_t i = 0; i < 4; i++) {

        this->hands[i].init(i, Constants::MaxNumberOfCards[static_cast<uint8_t>(GameMode::TwoPlayers)]);
        
    }


    // Update the players hands with the enemeny suit ..

    for (uint8_t i = 0; i < 4; i++) {

        this->hands[i].setEnemyCardSuit(this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle)).getSuit());
        
    }

// Card card;
// for (uint8_t i = 0; i < 11; i++) {
// this->deck.dealCard(DeckTypes::Tavern, card);
// this->hands[0].addCard(card);
// }
// this->gameState = GameState::Game_Step1_Play;

}   


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void Game::game() {

    bool castleDeck_DisplayCard = true;
    uint8_t currentPlayer = this->gamePlay.getCurrentPlayer();
    Hand& currentHand = this->hands[currentPlayer];
    Card &currentEnemy = this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle));

    switch (this->gameState) {

        case GameState::Game_NewHand:
            {
                if (dealCounter <= (Constants::DealDelay * 9)) dealCounter++;
                Card card;
                uint8_t currentPlayer = this->gamePlay.getCurrentPlayer();

                switch (dealCounter) {
                    
                    case Constants::DealDelay * 2:
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern, card);
                            this->hands[i].addCard(card);
                        }
                        break;
                    
                    case Constants::DealDelay * 3:
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }
                        break;
                    
                    case Constants::DealDelay * 4:
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }
                        break;
                    
                    case Constants::DealDelay * 5:
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }
                        break;
                    
                    case Constants::DealDelay * 6:
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }

                        if ( this->gamePlay.getNumberOfPlayers() > 2) dealCounter = (Constants::DealDelay * 9) - 1;
                        break;
                    
                    case Constants::DealDelay * 7:
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }

                        if ( this->gamePlay.getNumberOfPlayers() > 3) dealCounter = (Constants::DealDelay * 9) - 1;
                        break;
                    
                    case Constants::DealDelay * 8:
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }
                        break;

                    case Constants::DealDelay * 9:
                        this->gameState = GameState::Game_Step1_Play;
                        break;

                }

            }
            break;

        // ------------------------------------------------------------------------------------------------------------

        case GameState::Game_Step0_AddCards:

            if (dealCounter % Constants::DealDelay == 0) {

                currentHand.decCardsAdded();

            }

            dealCounter--;

            if (dealCounter == 0) {

                this->gameState = GameState::Game_Step1_Play;
            }

            break;


        // ------------------------------------------------------------------------------------------------------------

        case GameState::Game_Step1_Play:

            if (PC::buttons.pressed(BTN_LEFT)) {

                if (cardCursor == 0) {

                    bool isValidAttack = currentHand.isValidAttack();

                    cardCursor = isValidAttack ? Constants::CardCursor_Attack : Constants::CardCursor_Yield;

                }
                else if (cardCursor > 0 && cardCursor <= currentHand.getCardIndex()) {

                    cardCursor--;

                }
                else if (cardCursor >= Constants::CardCursor_Attack) {

                    cardCursor = currentHand.getCardIndex();

                }

            }

            if (PC::buttons.pressed(BTN_RIGHT)) {

                if (cardCursor >= Constants::CardCursor_Attack) {

                    cardCursor = 0;

                }
                else if (cardCursor < currentHand.getCardIndex()) {

                    cardCursor++;

                }
                else {

                    bool isValidAttack = currentHand.isValidAttack();

                    cardCursor = isValidAttack ? Constants::CardCursor_Attack : Constants::CardCursor_Yield;

                }

            }

            if (PC::buttons.pressed(BTN_UP) && cardCursor < 10) {

                if (!currentHand.isMarked(cardCursor)) {

                    currentHand.markCard(cardCursor);

                }

            }

            if (PC::buttons.pressed(BTN_UP) && cardCursor == Constants::CardCursor_Yield) {

                bool isValidAttack = currentHand.isValidAttack();

                if (isValidAttack) {

                    cardCursor = Constants::CardCursor_Attack;

                }

            }

            if (PC::buttons.pressed(BTN_DOWN) && cardCursor < 10) {

                if (currentHand.isMarked(cardCursor)) {

                    currentHand.markCard(cardCursor);
                    
                }

            }

            if (PC::buttons.pressed(BTN_DOWN) && cardCursor == Constants::CardCursor_Attack) {

                cardCursor = Constants::CardCursor_Yield;

            }

            if (PC::buttons.pressed(BTN_A)) {

                switch (cardCursor) {

                    case 0 ... 10:
                        currentHand.markCard(cardCursor);
                        break;

                    case Constants::CardCursor_Attack:
                        
                        this->gamePlay.setHealthToDiscard(currentEnemy.getAttack() - currentHand.getShieldValue());
                        this->deck.print();
                        this->gameState = GameState::Game_Step2_Activate;
                        currentHand.setCardsAdded(0);


                        // If the player has played a shield save it for the life of the current enemy ..

                        if (currentHand.getMarkedSuit(CardSuit::Spades)) {
                            this->deck.setShield(true);
                        }

                        break;

                    case Constants::CardCursor_Yield:
                        dealCounter = 0;
                        currentHand.clearMarks();
                        currentHand.setCardsAdded(0);
                        this->cardCursor = 0;
                        this->gamePlay.setHealthToDiscard(currentEnemy.getAttack());
                        this->gameState = GameState::Game_Step4_SufferDamage;
                        break;


                }

            }
            
            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step2_Activate:

            // Play hearts ..

            if (currentHand.getMarkedSuit(CardSuit::Hearts) && currentHand.getEnemyCardSuit() != CardSuit::Hearts) {

                this->deck.shuffleDiscardDeck();

                for (uint8_t i = 0; i < currentHand.getAttackValue(false); i++) {

                    if (this->deck.getIndex(DeckTypes::Discard) >= 0) {

                        Card card;
                        this->deck.dealCard(DeckTypes::Discard, card);
                        this->deck.addCardToBottom(DeckTypes::Tavern, card);

                    }
                    
                } 

            }

            // Play diamonds ..

            if (currentHand.getMarkedSuit(CardSuit::Diamonds) && currentHand.getEnemyCardSuit() != CardSuit::Diamonds) {

                uint8_t playerIdx = currentPlayer;

                for (uint8_t i = 0; i < currentHand.getAttackValue(false); i++) {
// printf("Add Cards %i Tav: %i player %i, curIdx %i, max %i, Extras: %i >> ", i, this->deck.getIndex(DeckTypes::Tavern), playerIdx, this->hands[playerIdx].getCardIndex(), this->hands[playerIdx].getMaxNumberOfCards() , (playerIdx == this->gamePlay.getCurrentPlayer() ? currentHand.getMarkedCardCount() : 0));

                    if (this->deck.getIndex(DeckTypes::Tavern) >= 0 && this->hands[playerIdx].getCardIndex() + 1 < this->hands[playerIdx].getMaxNumberOfCards() + (playerIdx == this->gamePlay.getCurrentPlayer() ? currentHand.getMarkedCardCount() : 0)) {
//CHECK: if player has max cards do we just skip them and include next player or not?  Assume just skip.
                        Card card;
                        this->deck.dealCard(DeckTypes::Tavern, card);
// printf("card ");                        
// card.print();
// printf("\n");
                        this->hands[playerIdx].addCard(card);
                        if (playerIdx != this->gamePlay.getCurrentPlayer()) {
                            this->hands[playerIdx].incCardsAdded();
                        }

                    }
//                     else {
// printf("skip\n");                        
//                     }

                    playerIdx++;
                    playerIdx = playerIdx % this->gamePlay.getNumberOfPlayers();
                    
                } 

            }

            dealCounter = (Constants::AttackInterval * ((currentHand.getAttackValue(true) + 1) / 2)) + Constants::AttackLength;
            if (dealCounter > (Constants::AttackInterval * Constants::AttackMax) + Constants::AttackLength) dealCounter = (16 * Constants::AttackMax) + Constants::AttackLength;
            this->gameState = GameState::Game_Step3_DealDamage;

            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step3_DealDamage:

            dealCounter--;

            if ((dealCounter - Constants::AttackLength) % Constants::AttackInterval == 0 && dealCounter > Constants::AttackLength) {
// printf("%i\n", dealCounter);

                this->attacks.launchAttach();

                // for (uint8_t i = 0; i < Constants::AttackMax; i++) {
                //     printf("{%i = %i) ", i, (uint16_t)this->attacks.getAttack(i).getIndex());
                // }
                // printf("\n");

            }
            else if (dealCounter == 0) {  
// printf("Move to ?\n");
                uint8_t attack = currentHand.getAttackValue(true);
                //Card &currentEnemy = this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle));

                if (attack == currentEnemy.getHealth()) {

                    bool endOfGame = this->changeAttackers(currentEnemy);

                    if (!endOfGame) {
                        this->deck.addCard(DeckTypes::Tavern, currentEnemy);
                        dealCounter = 50;
// printf("Move to 5a\n");
                        this->gameState = GameState::Game_Step5_EnemyDead;

                    }
                    else {
// printf("Move to Winner\n");
                        this->gameState = GameState::Winner_Init;
                    }

                }
                else if (attack > currentEnemy.getHealth()) {

                    bool endOfGame = this->changeAttackers(currentEnemy);

                    if (!endOfGame) {

                        this->deck.addCard(DeckTypes::Discard, currentEnemy);
                        dealCounter = 50;
// printf("Move to 5b\n");
                        this->gameState = GameState::Game_Step5_EnemyDead;                    

                    }
                    else {
// printf("Move to Winner\n");
                        this->gameState = GameState::Winner_Init;
                    }   

                }
                else {
// printf("Move to 4\n");

                    currentEnemy.print();
                    currentEnemy.setHealth(currentEnemy.getHealth() - attack);
                    dealCounter = 0;

                    if (this->gamePlay.getHealthToDiscard() == 0) {

                        this->gameState = GameState::Game_SwapPlayers_Init;                    

                    }
                    else {

                        this->gameState = GameState::Game_Step4_SufferDamage;                    

                    }

                }


                // Discard players cards ..

                for (uint8_t i = currentHand.getCardIndex() + 1; i > 0; i--) {

                    if (currentHand.isMarked(i - 1)) {

                        Card& card = currentHand.getCard(i - 1);
                        this->deck.addCard(DeckTypes::Discard, card);
                        currentHand.removeCard(i - 1);

                    }

                }

                currentHand.clearMarks();
                cardCursor = 0;

            }
            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step4_SufferDamage:

            switch (dealCounter) {

                case  0:
                    if (PC::buttons.pressed(BTN_LEFT)) {

                        if (cardCursor > 0 && cardCursor <= currentHand.getCardIndex()) {

                            cardCursor--;

                        }

                    }

                    if (PC::buttons.pressed(BTN_RIGHT)) {

                        if (cardCursor < currentHand.getCardIndex()) {

                            cardCursor++;

                        }

                    }

                    if (PC::buttons.pressed(BTN_A)) {

                        Card card = currentHand.getCard(cardCursor);
                        currentHand.removeCard(cardCursor);
                        this->deck.addCard(DeckTypes::Discard, card);

                        int8_t pointsToDiscard = this->gamePlay.getHealthToDiscard() - card.getHealthPoints();
                        if (pointsToDiscard < 0) pointsToDiscard = 0;
                        this->gamePlay.setHealthToDiscard(pointsToDiscard);

                        if (pointsToDiscard == 0 || currentHand.getCardIndex() == -1) {

                            dealCounter = 50;

                        }
                        else {

                            if (cardCursor > currentHand.getCardIndex()) {
                                cardCursor = currentHand.getCardIndex();
                            }

                        }

                    }

                    break;

                default:

                    dealCounter--;

                    if (dealCounter == 0) {

                        int8_t pointsToDiscard = this->gamePlay.getHealthToDiscard();

                        if (pointsToDiscard == 0) { 

                            this->gameState = GameState::Game_SwapPlayers_Init;

                            currentPlayer++;
                            currentPlayer = currentPlayer % this->gamePlay.getNumberOfPlayers();
                            currentHand.setShieldValue(0);
                            currentHand.clearMarks();

                            this->gamePlay.setCurrentPlayer(currentPlayer);
                            this->cardCursor = 0;

                        }
                        else if (currentHand.getCardIndex() == -1) {

                            this->gameState = GameState::GameOver_Init;

                        }

                    }

                    break;

            }

            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step5_EnemyDead:

            dealCounter--;

            switch (dealCounter) {

                case 0:
                    this->gameState = GameState::Game_Step1_Play;
                    break;

                default:
                    castleDeck_DisplayCard = false;
                    break;

            }

            break;

    }


//TODO if player kills enemy and plays again then adding two lots of cards to other player's deck should add not replace.






    PD::fillScreen(3);


    // Upper decks ..

    PD::drawBitmap(4, 1, Images::Banner_Castle);
    this->renderCastleDeck(5, 11, this->deck.getIndex(DeckTypes::Castle) + 1, castleDeck_DisplayCard);

    PD::drawBitmap(84, 1, Images::Banner_Discard);
    this->renderDiscardDeck(85, 11, this->deck.getIndex(DeckTypes::Discard) + 1);

    uint8_t attack = currentEnemy.getAttack() - currentHand.getShieldValue();
    PD::drawBitmap(5, 89, Images::AttackHealth);

    {
        uint8_t digits[3] = {};
        uint8_t x = 48;

        extractDigits(digits, attack);

        for (uint8_t i = 0; i < 2; ++i) {
            PD::drawBitmap(x, 89, Images::MediumNumbers[digits[i]]);
            x = x - 5;
        }

        x = 48;
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
            this->renderPlayerHand(currentPlayer, 1, 140, cardCursor, currentHand.getCardsAdded());
            break;
            
        default:
            this->renderPlayerHand(currentPlayer, 1, 140, Constants::NoSelection, currentHand.getCardsAdded());
            break;

    }

    PD::drawBitmap(1, 166, Images::Player);
    PD::drawBitmap(35, 167, Images::MediumNumbers[this->gamePlay.getCurrentPlayer() + 1]);



    // Render background ..

    for (uint8_t y = 0; y < 176; y = y + 32) {

        PD::drawBitmap(147, y, Images::RightSidePanel);

    }

    PD::drawBitmap(159, 1, Images::Banner_Tavern);
    this->renderTavernDeck(160, 11, this->deck.getIndex(DeckTypes::Tavern) + 1);

    attack = currentHand.getAttackValue(false);

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

        case GameState::Game_Step1_Play:

            this->renderCaption(Caption::AttackOrYield);
            this->renderAttackButton(cardCursor == Constants::CardCursor_Attack ? ButtonState::Highlighted : (currentHand.isValidAttack() ? ButtonState::Enabled : ButtonState::Disabled));
            this->renderYieldButton(cardCursor == Constants::CardCursor_Yield ? ButtonState::Highlighted : ButtonState::Enabled);

            break;

        case GameState::Game_Step2_Activate:

            this->renderAttackButton(ButtonState::Disabled);
            this->renderYieldButton(ButtonState::Disabled);

            break;

        case GameState::Game_Step3_DealDamage:
            {        
                uint8_t attack = currentHand.getAttackValue();
                Card currentEnemy = this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle));

                if (dealCounter > 0) {

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

        case GameState::Game_Step4_SufferDamage:
            {        
                PD::setColor(2, 14);
                PD::setCursor(0, 120);

                //Card currentEnemy = this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle));
                uint8_t attack = currentEnemy.getAttack() - currentHand.getShieldValue();

                switch (dealCounter) {

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

        case GameState::Game_Step5_EnemyDead:
            this->renderCaption(Caption::EnemyDefeated);
            break;

        default:

            this->renderAttackButton(ButtonState::Disabled);
            this->renderYieldButton(ButtonState::Disabled);
            break;

    }

    this->attacks.update();
    
}
