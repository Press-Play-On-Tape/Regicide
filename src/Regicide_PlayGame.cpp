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
    this->gamePlay.init(this->gamePlay.getNumberOfPlayers());
    this->deck.init(this->gamePlay.getNumberOfPlayers());

    this->deck.print();

    //uint16_t dealCounter = 0;

    for (uint8_t i = 0; i < 4; i++) {

        this->hands[i].init(i, Constants::MaxNumberOfCards[this->gamePlay.getNumberOfPlayers()]);
        
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

// this->hands[0].removeCard(2);
// this->hands[0].removeCard(2);
// this->hands[0].removeCard(2);this->hands[0].removeCard(2);this->hands[0].removeCard(2);
// this->hands[0].removeCard(2);
// this->hands[0].removeCard(2);

// deck.print();
// Card card;
// for (uint8_t i = 0; i < 10; i++) {
// this->deck.dealCard(DeckTypes::Castle, card);
// }
// deck.print();
// deck.getCard(DeckTypes::Castle, 0).setAttack(5);
// deck.getCard(DeckTypes::Castle, 0).setHealth(5);
// deck.getCard(DeckTypes::Castle, 1).setAttack(5);
// deck.getCard(DeckTypes::Castle, 1).setHealth(5);

// Card card;
// for (uint8_t i = 0; i < 3; i++) {
// this->deck.dealCard(DeckTypes::Castle, card);
// }


// deck.getCard(DeckTypes::Castle, 11).init(23);

// this->hands[0].getCard(0).init(7);//SJH 8 Clubs




deck.print();
Card card;
for (uint8_t i = 0; i < 30; i++) {
this->deck.dealCard(DeckTypes::Tavern, card);
this->deck.addCard(DeckTypes::Discard, card);
}
deck.print();
}   

void Game::game() {

    uint8_t currentPlayer = this->gamePlay.getCurrentPlayer();
    Hand& currentHand = this->hands[currentPlayer];
    Card &currentEnemy = this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle));

    switch (this->gameState) {

        case GameState::Game_NewHand:
            {
                if (this->gamePlay.getCounter() <= (Constants::DealDelay * 10)) this->gamePlay.incCounter();
                Card card;
                uint8_t currentPlayer = this->gamePlay.getCurrentPlayer();

                switch (this->gamePlay.getCounter()) {
                    
                    case Constants::DealDelay * 2:
                    
                        this->playSoundEffect(SoundEffect::Deal);
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

                        this->playSoundEffect(SoundEffect::Deal);
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

                        this->playSoundEffect(SoundEffect::Deal);
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

                        break;
                    
                    case Constants::DealDelay * 8:
                        
                        this->playSoundEffect(SoundEffect::Deal);
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }

                        if (this->gamePlay.getNumberOfPlayers() > 1) {
                            this->gamePlay.setCounter((Constants::DealDelay * 10) - 1);
                        }

                        break;
                    
                    case Constants::DealDelay * 9:
                        
                        for (uint8_t i = 0; i < this->gamePlay.getNumberOfPlayers(); i++) {
                            this->deck.dealCard(DeckTypes::Tavern,card);
                            this->hands[i].addCard(card);
                        }
                        
                        break;

                    case Constants::DealDelay * 10:


// this->hands[0].getCard(0).init(2);//SJH 3 
// this->hands[0].getCard(1).init(15);//SJH 3 
// this->hands[0].getCard(2).init(28);//SJH 3 
// this->hands[0].getCard(3).init(41);//SJH 3 

// this->hands[0].getCard(0).init(22);//SJH 10 Spades
// this->hands[0].getCard(0).init(9);//SJH 10 Clubs
// this->hands[0].getCard(0).init(32);//SJH Diamond
// this->hands[0].getCard(1).init(17);//SJH 5 Spades
// this->hands[0].getCard(2).init(18);//SJH 6 Spades
// this->hands[0].getCard(0).init(0);//SJH
// this->hands[0].getCard(1).init(0);//SJH
// this->hands[0].getCard(2).init(0);//SJH
// this->hands[0].getCard(3).init(0);//SJH
// this->hands[0].getCard(4).init(0);//SJH
// this->hands[0].getCard(5).init(0);//SJH
// this->hands[0].getCard(6).init(0);//SJH
// this->deck.getCard(DeckTypes::Castle, 11).init(23);//SJH J Spades
// this->hands[0].getCard(7).init(17);//SJH
// this->hands[0].removeCard(7);
// this->hands[0].removeCard(6);
// this->hands[0].removeCard(5);
// this->hands[0].removeCard(4);
// this->hands[0].removeCard(3);
// this->hands[0].removeCard(2);
// this->hands[0].removeCard(7);
// this->hands[1].removeCard(7);


// this->hands[0].getCard(0).init(7);//SJH 8 Clubs
// this->hands[0].getCard(1).init(21);//SJH 9 Spades
this->hands[0].getCard(1).init(23);//SJH J Spades
// this->hands[0].removeCard(7);
// this->hands[0].removeCard(6);
// this->hands[0].removeCard(5);
// this->hands[0].removeCard(4);
// this->hands[0].removeCard(3);
// this->hands[0].removeCard(2);
// this->gamePlay.setReplenish(0);
    // Card &currentEnemy = this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle));




// this->hands[0].getCard(0).init(47);//SJH Heart 9
// this->hands[0].getCard(1).init(42);//SJH Heart 4
// this->hands[0].getCard(2).init(44);//SJH Heart 6
// this->hands[0].getCard(3).init(30);//SJH Diamond
// this->hands[0].getCard(4).init(10);//SJH Diamond
// this->hands[0].setCardIndex(4);
// Card &currentEnemy = this->deck.getCard(DeckTypes::Castle, this->deck.getIndex(DeckTypes::Castle));

this->hands[0].getCard(0).init(28);//SJH Heart 4
this->hands[0].getCard(1).init(8);//SJH Heart 4
this->hands[0].getCard(2).init(29);//SJH Heart 4


                        this->gameState = GameState::Game_Step1_Play;
                        this->deck.print();
                        break;

                }

            }
            break;

        // ------------------------------------------------------------------------------------------------------------

        case GameState::Game_Step0_AddCards:

            this->gamePlay.decDiamondsCounter();
                
            if (this->gamePlay.getDiamondsCounter() == 0) {

                while (currentHand.getCardsAdded() > 0) {

                    currentHand.decCardsAdded();

                    if (currentHand.getCardsAdded() == 0) {

                        this->gameState = GameState::Game_Step1_Play;
                        break;

                    }

                }

            }

            break;


        // ------------------------------------------------------------------------------------------------------------

        case GameState::Game_Step1_Play:
    
            if (PC::buttons.pressed(BTN_LEFT)) {

                if (this->gamePlay.getCardCursor() == 0 && this->gamePlay.getNumberOfPlayers() > 1) {

                    bool isValidAttack = currentHand.isValidAttack();

                    this->gamePlay.setCardCursor(isValidAttack ? Constants::CardCursor_Attack : Constants::CardCursor_Yield);

                }
                else if (this->gamePlay.getCardCursor() == 0 && this->gamePlay.getNumberOfPlayers() == 1) {

                    bool canReplenish = currentHand.getCardIndex() < 7 && this->deck.getIndex(DeckTypes::Tavern) >= 0;
                    bool isValidAttack = currentHand.isValidAttack();

                    if (isValidAttack) {
                        this->gamePlay.setCardCursor(Constants::CardCursor_Attack);
                    }
                    else {
                        this->gamePlay.setCardCursor(Constants::CardCursor_Yield);
                    }

                }
                else if (this->gamePlay.getCardCursor() > 0 && this->gamePlay.getCardCursor() <= currentHand.getCardIndex()) {

                    this->gamePlay.decCardCursor();

                }
                else if (this->gamePlay.getCardCursor() >= Constants::CardCursor_Attack && currentHand.getCardIndex() >= 0) {

                    this->gamePlay.setCardCursor(currentHand.getCardIndex());

                }

            }

            if (PC::buttons.pressed(BTN_RIGHT)) {

                if (this->gamePlay.getCardCursor() >= Constants::CardCursor_Attack && currentHand.getCardIndex() >= 0) {

                    this->gamePlay.setCardCursor(0);

                }
                else if (this->gamePlay.getCardCursor() < currentHand.getCardIndex()) {

                    this->gamePlay.incCardCursor();

                }
                else if (this->gamePlay.getNumberOfPlayers() > 1) {

                    bool isValidAttack = currentHand.isValidAttack();

                    this->gamePlay.setCardCursor(isValidAttack ? Constants::CardCursor_Attack : Constants::CardCursor_Yield);

                }
                else {

                    bool canReplenish = currentHand.getCardIndex() < 7 && this->deck.getIndex(DeckTypes::Tavern) >= 0;
                    bool isValidAttack = currentHand.isValidAttack();

                    if (isValidAttack) {
                        this->gamePlay.setCardCursor(Constants::CardCursor_Attack);
                    }
                    else  {
                        this->gamePlay.setCardCursor(Constants::CardCursor_Yield);
                    }

                }

            }

            if (PC::buttons.pressed(BTN_UP) && this->gamePlay.getCardCursor() < 10) {

                if (!currentHand.isMarked(this->gamePlay.getCardCursor())) {

                    currentHand.markCard(this->gamePlay.getCardCursor());

                }

            }

            if (PC::buttons.pressed(BTN_UP) && (this->gamePlay.getCardCursor() == Constants::CardCursor_Yield || this->gamePlay.getCardCursor() == Constants::CardCursor_Replenish)) {

                bool isValidAttack = currentHand.isValidAttack();

                if (isValidAttack) {

                    this->gamePlay.setCardCursor(Constants::CardCursor_Attack);

                }
                else {

                    this->gamePlay.setCardCursor(Constants::CardCursor_Yield);

                }

            }

            if (PC::buttons.pressed(BTN_DOWN) && this->gamePlay.getCardCursor() < 10) {

                if (currentHand.isMarked(this->gamePlay.getCardCursor())) {

                    currentHand.markCard(this->gamePlay.getCardCursor());
                    
                }

            }

            if (PC::buttons.pressed(BTN_DOWN) && this->gamePlay.getCardCursor() == Constants::CardCursor_Attack && this->gamePlay.getNumberOfPlayers() > 1) {

                this->gamePlay.setCardCursor(Constants::CardCursor_Yield);

            }

            if (PC::buttons.pressed(BTN_DOWN) && this->gamePlay.getCardCursor() > 10 && this->gamePlay.getNumberOfPlayers() == 1) {

                bool canReplenish = currentHand.getCardIndex() < 7 && this->deck.getIndex(DeckTypes::Tavern) >= 0;

                if (canReplenish) {
                    this->gamePlay.setCardCursor(Constants::CardCursor_Replenish);
                }

            }

            if (PC::buttons.pressed(BTN_A)) {

                switch (this->gamePlay.getCardCursor()) {

                    case Constants::CardCursor_Attack:
                        
                        this->gamePlay.setHealthToDiscard(currentEnemy.getAttack() - currentEnemy.getShieldVal() - currentHand.getShieldValue());
                        this->deck.print();
                        this->gameState = GameState::Game_Step2_Activate;
                        currentHand.setCardsAdded(0);


                        // Set delays .. hearts done first.

                        if (currentHand.getMarkedSuit(CardSuit::Hearts) && currentHand.getEnemyCardSuit() != CardSuit::Hearts && this->deck.getIndex(DeckTypes::Discard) >= 0) {

                            this->gamePlay.setHeartsCounter(20);
                            this->playSoundEffect(SoundEffect::Deal);

                        }

                        if (currentHand.getMarkedSuit(CardSuit::Diamonds) && currentHand.getEnemyCardSuit() != CardSuit::Diamonds && this->deck.getIndex(DeckTypes::Tavern) >= 0) {

                            this->gamePlay.setDiamondsCounter(11);
                            this->playSoundEffect(SoundEffect::Deal);

                        }

                        // If the player has played a shield save it for the life of the current enemy ..

                        if (currentHand.getMarkedSuit(CardSuit::Spades)) {
                            currentEnemy.setShield(true);
                            currentEnemy.setShieldVal(currentEnemy.getShieldVal() + currentHand.getShieldValue());
                        }

                        break;

                    case Constants::CardCursor_Yield:

                        currentHand.clearMarks();
                        currentHand.setCardsAdded(0);
                        this->gamePlay.setCounter(0);
                        this->gamePlay.setCardCursor(0);
                        this->gamePlay.setHealthToDiscard(currentEnemy.getAttack() - currentEnemy.getShieldVal());

                        if (currentHand.getHealth() < this->gamePlay.getHealthToDiscard()) {

                            this->gameState = GameState::Game_Over;
                            this->gamePlay.setCounter(Constants::GameOver_Delay);

                        }
                        else {
                        
                            this->gameState = GameState::Game_Step4_SufferDamage;
                        
                        }

                        break;

                    case Constants::CardCursor_Replenish:

                        uint8_t cardsToReplenish = 7 - currentHand.getCardIndex();
                        if (this->deck.getIndex(DeckTypes::Tavern) + 1 < cardsToReplenish) cardsToReplenish = this->deck.getIndex(DeckTypes::Tavern) + 1;                  

                        if (cardsToReplenish > 0) {

                            uint8_t cardsReplenished = 0;

                            for (uint8_t i = 0; i < cardsToReplenish; i++) {

                                if (this->deck.getIndex(DeckTypes::Tavern) >= 0) {
                                    Card card;
                                    this->deck.dealCard(DeckTypes::Tavern, card);
                                    currentHand.addCard(card);
                                    cardsReplenished++;
                                }
                            }

                            currentHand.setCardsAdded(cardsReplenished);

                            this->gamePlay.setReplenish(this->gamePlay.getReplenish() - 1);
                            this->gamePlay.setCounter((Constants::DealDelay * currentHand.getCardsAdded()) + (Constants::DealDelay - 2));
                            this->gamePlay.setDiamondsCounter(11);
                            this->gamePlay.setCardCursor(0);
                            this->gameState = GameState::Game_Step0_AddCards;
                            this->playSoundEffect(SoundEffect::Deal);


                        }
                        
                        break;
                }

            }
            
            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step2_Activate:

            // Play hearts ..

            if (this->gamePlay.getHeartsCounter() > 0) {

                this->gamePlay.decHeartsCounter();

                if (this->gamePlay.getHeartsCounter() == 0) {

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

            if (this->gamePlay.getHeartsCounter() == 0 && this->gamePlay.getDiamondsCounter() > 0) {

                this->gamePlay.decDiamondsCounter();
                    
                if (this->gamePlay.getDiamondsCounter() == 0) {

                    uint8_t playerIdx = currentPlayer;

                    for (uint8_t i = 0; i < currentHand.getAttackValue(false); i++) {

                        if (this->deck.getIndex(DeckTypes::Tavern) >= 0 && this->hands[playerIdx].getCardIndex() - this->hands[playerIdx].getMarkedCardCount() + 1 < this->hands[playerIdx].getMaxNumberOfCards()) {
   
                            Card card;
                            this->deck.dealCard(DeckTypes::Tavern, card);
                            this->hands[playerIdx].addCard(card);

                            if (playerIdx != this->gamePlay.getCurrentPlayer()) {
                                this->hands[playerIdx].incCardsAdded();
                            }

                        }

                        playerIdx++;
                        playerIdx = playerIdx % this->gamePlay.getNumberOfPlayers();
                        
                    } 

                }

            }


            // Progress to next phase?

            if (this->gamePlay.getHeartsCounter() == 0 && this->gamePlay.getDiamondsCounter() == 0) {

                this->gamePlay.setCounter((2 * Constants::AttackInterval) + 1);
                this->gameState = GameState::Game_Step3_DealDamage_Init;
                this->playSoundEffect(SoundEffect::EnemyDeath);

            }

            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step3_DealDamage_Init:

            this->gamePlay.decCounter();

            if ((this->gamePlay.getCounter() % Constants::AttackInterval) == 0 && this->gamePlay.getCounter() > 0) {

                this->attacks.launchAttach();

            }
            else if (this->gamePlay.getCounter() == 0) {

                uint8_t attack = currentHand.getAttackValue(true);
                this->gamePlay.getPreviousEnemy().init(currentEnemy.getCardIndex());
                

                // Handle enemy death if it has occurred ..

                if (attack == currentEnemy.getHealth()) {

                    bool endOfGame = this->changeAttackers(currentEnemy);

                    if (!endOfGame) {

                        this->gamePlay.setEnemyTavernCounter(19);
                        this->gamePlay.setEnemyDiscardCounter(0);
                        this->enemyKilled = EnemyKilledType::Tavern;
                        this->nextCounter = 50;
                        this->nextGameState = GameState::Game_Step5_EnemyDead;
                        this->gameState = GameState::Game_Step3_DealDamage_DeadEnemy;

                    }
                    else {

                        this->nextCounter = 0;
                        this->gameState = GameState::Winner_Init;

                    }

                }
                else if (attack > currentEnemy.getHealth()) {

                    bool endOfGame = this->changeAttackers(currentEnemy);

                    if (!endOfGame) {

                        this->gamePlay.setEnemyTavernCounter(0);
                        this->gamePlay.setEnemyDiscardCounter(18);
                        this->enemyKilled = EnemyKilledType::Discard;
                        this->nextCounter = 50;
                        this->nextGameState = GameState::Game_Step5_EnemyDead;                    
                        this->gameState = GameState::Game_Step3_DealDamage_DeadEnemy;

                    }
                    else {

                        this->nextCounter = 0;
                        this->gameState = GameState::Winner_Init;

                    }   

                }                
                else {

                    currentEnemy.print();
                    currentEnemy.setHealth(currentEnemy.getHealth() - attack);
                    this->gamePlay.setCounter(0);

                    this->discardPlayersCards(currentHand);

                    if (this->gamePlay.getHealthToDiscard() == 0) {

                        this->gamePlay.setCounter(0);

                        if (this->gamePlay.getNumberOfPlayers() > 1) {

                            currentPlayer++;
                            currentPlayer = currentPlayer % this->gamePlay.getNumberOfPlayers();
                            currentHand.setShieldValue(0);
                            currentHand.clearMarks();

                            this->gameState = GameState::Game_SwapPlayers_Init;      
                            this->gamePlay.setCurrentPlayer(currentPlayer);
                            this->gamePlay.setCardCursor(0);
                                                                        
                        }
                        else {

                            bool endOfGame = this->setCardCursor(currentHand);

                            if (endOfGame) {
                                this->gameState = GameState::Game_Over;
                                this->gamePlay.setCounter(Constants::GameOver_Delay);
                            }
                            else {
                                this->gameState = GameState::Game_Step1_Play;    
                                currentHand.clearMarks();                
                            }

                        }

                    }
                    else {

                        this->gamePlay.setCounter(0);
                        this->gameState = GameState::Game_Step4_SufferDamage;                    

                    }


                    currentHand.clearMarks();
                    this->gamePlay.setCardCursor(0);


                    // If the player does not have enough points left, then they have died ..

                    if (this->gameState == GameState::Game_Step4_SufferDamage && currentHand.getHealth() < this->gamePlay.getHealthToDiscard()) {

                        this->gameState = GameState::Game_Over;
                        this->gamePlay.setCounter(Constants::GameOver_Delay);

                    }

                }

            }

            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step3_DealDamage_DeadEnemy:

            if (this->gamePlay.getEnemyDiscardCounter() > 0 || this->gamePlay.getEnemyTavernCounter() > 0) {

                this->gamePlay.decEnemyDiscardCounter();
                this->gamePlay.decEnemyTavernCounter();

                if (this->gamePlay.getEnemyDiscardCounter() == 0 && this->gamePlay.getEnemyTavernCounter() == 0 ) {

                    this->gameState = this->nextGameState;
                    this->gamePlay.setCounter(this->nextCounter);

                    this->discardPlayersCards(currentHand);


                    // Discard the enemy if it is dead ..

                    switch (enemyKilled) {

                        case EnemyKilledType::Discard:
                            this->deck.addCard(DeckTypes::Discard, this->gamePlay.getPreviousEnemy());
                            this->deck.print();
                            break;

                        case EnemyKilledType::Tavern:
                            this->deck.addCard(DeckTypes::Tavern, this->gamePlay.getPreviousEnemy());
                            this->deck.print();
                            break;

                        default: break;

                    }

                    currentHand.clearMarks();
                    this->gamePlay.setCardCursor(0);

                }

            }

            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step4_SufferDamage:

            switch (this->gamePlay.getCounter()) {

                case  0:
                    if (PC::buttons.pressed(BTN_LEFT)) {

                        if (this->gamePlay.getCardCursor() > 0 && this->gamePlay.getCardCursor() <= currentHand.getCardIndex()) {

                            this->gamePlay.decCardCursor();

                        }

                    }

                    if (PC::buttons.pressed(BTN_RIGHT)) {

                        if (this->gamePlay.getCardCursor() < currentHand.getCardIndex()) {

                            this->gamePlay.incCardCursor();

                        }

                    }

                    if (PC::buttons.pressed(BTN_UP)) {

                        this->playSoundEffect(SoundEffect::Deal);
                        Card card = currentHand.getCard(this->gamePlay.getCardCursor());
                        currentHand.removeCard(this->gamePlay.getCardCursor());
                        this->deck.addCard(DeckTypes::Discard, card);

                        int8_t pointsToDiscard = this->gamePlay.getHealthToDiscard() - card.getHealthPoints();
                        if (pointsToDiscard < 0) pointsToDiscard = 0;
                        this->gamePlay.setHealthToDiscard(pointsToDiscard);

                        if (pointsToDiscard == 0 ) {

                            this->gamePlay.setCounter(this->gamePlay.getNumberOfPlayers() > 1 ? 50 : 1);

                        }
                        else if (currentHand.getCardIndex() == -1) {

                            this->gamePlay.setCounter(50);

                        }
                        else {

                            if (this->gamePlay.getCardCursor() > currentHand.getCardIndex()) {
                                this->gamePlay.setCardCursor(currentHand.getCardIndex());
                            }

                        }

                    }

                    break;

                default:

                    this->gamePlay.decCounter();

                    if (this->gamePlay.getCounter() == 0) {

                        int8_t pointsToDiscard = this->gamePlay.getHealthToDiscard();

                        if (pointsToDiscard == 0) { 


                            // Swap players if more than one player is playing ..

                            if (this->gamePlay.getNumberOfPlayers() > 1) {
                        
                                currentPlayer++;
                                currentPlayer = currentPlayer % this->gamePlay.getNumberOfPlayers();
                                currentHand.setShieldValue(0);
                                currentHand.clearMarks();

                                this->gameState = GameState::Game_SwapPlayers_Init;
                                this->gamePlay.setCurrentPlayer(currentPlayer);
                                this->gamePlay.setCardCursor(0);

                            }
                            else {

                                currentHand.setShieldValue(0);
                                currentHand.clearMarks();
                                    
                                bool endOfGame = this->setCardCursor(currentHand);

                                if (endOfGame) {
                                    this->gameState = GameState::Game_Over;
                                    this->gamePlay.setCounter(Constants::GameOver_Delay);               
                                }
                                else {
                                    this->gameState = GameState::Game_Step1_Play;                    
                                }
                                
                            }

                        }
                        else if (currentHand.getCardIndex() == -1) {

                            this->gameState = GameState::Game_Over;
                            this->gamePlay.setCounter(Constants::GameOver_Delay);

                        }

                    }

                    break;

            }

            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Step5_EnemyDead:

            this->gamePlay.decCounter();

            switch (this->gamePlay.getCounter()) {

                case 0:
                    {
                        bool endOfGame = this->setCardCursor(currentHand);

                        if (endOfGame) {
                            this->gameState = GameState::Game_Over;
                            this->gamePlay.setCounter(Constants::GameOver_Delay);
                        }
                        else {
                            this->gameState = GameState::Game_Step1_Play;
                            currentHand.clearMarks();                
                        }

                    }
                    break;

                default:
                    break;

            }

            break;

        // ------------------------------------------------------------------------------------------------------------
        
        case GameState::Game_Over:

            if (this->gamePlay.getCounter() > 0) this->gamePlay.setCounter(this->gamePlay.getCounter() - 8);

            if (this->gamePlay.getCounter() < 176 && PC::buttons.pressed(BTN_A)) {

                this->gameState = GameState::Title_Init;

            }

            break;

    }

    this->renderScreen(currentHand, currentEnemy);
    this->attacks.update();
    
}

void Game::discardPlayersCards(Hand &currentHand) {
   
    // Discard players cards ..

    for (uint8_t i = currentHand.getCardIndex() + 1; i > 0; i--) {

        if (currentHand.isMarked(i - 1)) {

            Card& card = currentHand.getCard(i - 1);
            this->deck.addCard(DeckTypes::Discard, card);
            currentHand.removeCard(i - 1);

        }

    }

}

bool Game::setCardCursor(Hand &currentHand) { // returns end of game

    if (this->gamePlay.getNumberOfPlayers() > 1) {

        if (this->hands[0].getCardIndex() < 0 && this->hands[1].getCardIndex()) {

            return true;

        }
        else if (currentHand.getCardIndex() < 0) {

            this->gamePlay.setCardCursor(Constants::CardCursor_Yield);

        }
        else {

            this->gamePlay.setCardCursor(0);

        }

    }
    else {

        if (currentHand.getCardIndex() < 0) {

            if (this->gamePlay.getReplenish() > 0) {

                this->gamePlay.setCardCursor(Constants::CardCursor_Replenish);

            }
            else {

                return true;
            }

        }
        else {

            this->gamePlay.setCardCursor(0);

        }

    }

    return false;

}