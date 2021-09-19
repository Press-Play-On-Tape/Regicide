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
    this->gamePlay.init(static_cast<GameMode>(this->gamePlay.getNumberOfPlayers()));
    this->deck.init(static_cast<GameMode>(this->gamePlay.getNumberOfPlayers()));

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
                        break;
                    
                    case Constants::DealDelay * 7:
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }

                        if (this->gamePlay.getNumberOfPlayers() > 1) {
                            printf("huh\n");dealCounter = (Constants::DealDelay * 9) - 1;}
                        break;
                    
                    case Constants::DealDelay * 8:
                    printf("deal 8\n");
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }
                        break;

                    case Constants::DealDelay * 9:


this->hands[0].getCard(0).init(22);//SJH


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

                    // case 0 ... 10:
                    //     currentHand.markCard(cardCursor);
                    //     break;

                    case Constants::CardCursor_Attack:
                        
                        this->gamePlay.setHealthToDiscard(currentEnemy.getAttack() - currentHand.getShieldValue());
                        this->deck.print();
                        this->gameState = GameState::Game_Step2_Activate;
                        currentHand.setCardsAdded(0);


                        // Set delays .. hearts done first.

                        if (currentHand.getMarkedSuit(CardSuit::Hearts) && currentHand.getEnemyCardSuit() != CardSuit::Hearts && this->deck.getIndex(DeckTypes::Discard) >= 0) {

                            heartsCounter = 20;
printf("Hearts\n");
                        }

                        if (currentHand.getMarkedSuit(CardSuit::Diamonds) && currentHand.getEnemyCardSuit() != CardSuit::Diamonds && this->deck.getIndex(DeckTypes::Tavern) >= 0) {

                            diamondsCounter = 21;

                        }

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

            if (heartsCounter > 0) {

                heartsCounter--;

                if (heartsCounter == 0) {

                    this->deck.shuffleDiscardDeck();

                    for (uint8_t i = 0; i < currentHand.getAttackValue(false); i++) {

                        if (this->deck.getIndex(DeckTypes::Discard) >= 0) {

                            Card card;
                            this->deck.dealCard(DeckTypes::Discard, card);
                            this->deck.addCardToBottom(DeckTypes::Tavern, card);

                        }
                        
                    } 

                }

            }

            // Play diamonds ..

            if (heartsCounter == 0 && diamondsCounter > 0) {

                diamondsCounter--;
                    
                if (diamondsCounter == 0) {

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

            }


            // Progress to next phase?

            if (heartsCounter == 0 && diamondsCounter == 0) {

                dealCounter = (Constants::AttackInterval * ((currentHand.getAttackValue(true) + 1) / 2)) + Constants::AttackLength;
                if (dealCounter > (Constants::AttackInterval * Constants::AttackMax) + Constants::AttackLength) dealCounter = (16 * Constants::AttackMax) + Constants::AttackLength;
                this->gameState = GameState::Game_Step3_DealDamage;

            }

            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step3_DealDamage:

            dealCounter--;

            if ((dealCounter - Constants::AttackLength) % Constants::AttackInterval == 0 && dealCounter > Constants::AttackLength) {

                this->attacks.launchAttach();

            }
            else if (dealCounter == 0) {  

                uint8_t attack = currentHand.getAttackValue(true);
                
                Card prevEnemy;
                EnemyKilledType enemyKilled = EnemyKilledType::None;

                prevEnemy.init(currentEnemy.getCardIndex());
                
                if (attack == currentEnemy.getHealth()) {

                    bool endOfGame = this->changeAttackers(currentEnemy);

                    if (!endOfGame) {

                        enemyKilled = EnemyKilledType::Tavern;
                        dealCounter = 50;
                        this->gameState = GameState::Game_Step5_EnemyDead;

                    }
                    else {
                        this->gameState = GameState::Winner_Init;
                    }

                }
                else if (attack > currentEnemy.getHealth()) {

                    bool endOfGame = this->changeAttackers(currentEnemy);

                    if (!endOfGame) {

                        enemyKilled = EnemyKilledType::Discard;
                        dealCounter = 50;
                        this->gameState = GameState::Game_Step5_EnemyDead;                    

                    }
                    else {
                        this->gameState = GameState::Winner_Init;
                    }   

                }
                else {

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


                // Discard the enemy if it is dead ..

                switch (enemyKilled) {

                    case EnemyKilledType::Discard:
                        this->deck.addCard(DeckTypes::Discard, prevEnemy);
                        this->deck.print();
                        break;

                    case EnemyKilledType::Tavern:
                        this->deck.addCard(DeckTypes::Tavern, prevEnemy);
                        this->deck.print();
                        break;

                    default: break;

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

                    if (PC::buttons.pressed(BTN_UP)) {

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
printf("Swap Players 2\n");

                            // Swpa players if more than one player is playing ..

                            if (this->gamePlay.getNumberOfPlayers() > 1) {

                                this->gameState = GameState::Game_SwapPlayers_Init;

                                currentPlayer++;
                                currentPlayer = currentPlayer % this->gamePlay.getNumberOfPlayers();
                                currentHand.setShieldValue(0);
                                currentHand.clearMarks();

                                this->gamePlay.setCurrentPlayer(currentPlayer);
                                this->cardCursor = 0;

                            }
                            else {

                                currentHand.setShieldValue(0);
                                currentHand.clearMarks();
                                this->gameState = GameState::Game_Step1_Play;
                                this->cardCursor = 0;
                                
                            }

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


    // ---------------------------------------------------------------------------------------------------------------
    // Render screen
    // ---------------------------------------------------------------------------------------------------------------


    PD::fillScreen(3);


    // Upper decks ..

    PD::drawBitmap(9, 1, Images::Banner_Castle);
    this->renderCastleDeck(10, 11, this->deck.getIndex(DeckTypes::Castle) + 1, castleDeck_DisplayCard);

    PD::drawBitmap(84, 1, Images::Banner_Discard);
    this->renderDiscardDeck(85, 11, this->deck.getIndex(DeckTypes::Discard) + 1, heartsCounter == 0);

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

            if (heartsCounter > 0) {

                PD::drawBitmap(168 - (heartsCounter * 4), 11, Images::Card_Back);
                this->renderCaption(Caption::CardsAddedToTavern);

            }

            if (diamondsCounter > 0) {

                PD::drawBitmap(90 + (diamondsCounter / 2), 140 - (diamondsCounter * 6), Images::Card_Back);
                this->renderCaption(Caption::CardAddedToYourHand);

            }

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
