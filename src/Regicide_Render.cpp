#include "Regicide.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderCard(int16_t x, int16_t y, Card &card, bool highlight) { 

    PD::drawBitmap(x, y, highlight ? Images::Card_Front_Highlight : Images::Card_Front_Normal);

    PD::setCursor(x + 6, y + 4);
    PD::setColor(7);

    switch (card.getNumber() % 13) {

        case 0:    
            PD::print("A");
            break;

        case 1 ... 8:    
            PD::print(static_cast<uint16_t>((card.getNumber() % 13) + 1));
            break;

        case 9:    
            PD::print("10");
            break;

        case 10:    
            PD::print("J");
            break;

        case 11:    
            PD::print("Q");
            break;

        case 12:    
            PD::print("K");
            break;
    
    }

    PD::drawBitmap(x + 4, y + 14, Images::Suits[static_cast<uint8_t>(card.getSuit())]);


}


void Game::renderPlayerHand(uint8_t playerIdx, int16_t x, int16_t y, uint8_t selecteIndex) { 

    for (uint8_t i = 0; i <= this->hands[playerIdx].getCardIndex(); i++) {

        Card card = this->hands[playerIdx].getCard(i);
        bool marked = this->hands[playerIdx].isMarked(i);

        this->renderCard(x, y - (marked ? 10 : 0), card, i == selecteIndex);
        x = x + 17;

    }

}


void Game::renderCastleDeck(int16_t x, int16_t y) { 

    uint8_t endCard = this->deck.getIndex(DeckTypes::Castle);
    uint8_t startCard = endCard > 3 ? endCard - 3 : 0;


    if (endCard == 0) {

        PD::drawBitmap(x, y, Images::Card_Placeholder);

    }
    else {

        for (uint8_t i = startCard; i <= endCard; i++) {

            Card card = this->deck.getCard(DeckTypes::Castle, i);
            this->renderCard(x, y, card, false);
            x = x + 2;

        }

    }

}


void Game::renderTavernDeck(int16_t x, int16_t y) { 

    uint8_t endCard = this->deck.getIndex(DeckTypes::Tavern);
    uint8_t startCard = endCard > 3 ? endCard - 3 : 0;

    if (endCard == 0) {

        PD::drawBitmap(x, y, Images::Card_Placeholder);

    }
    else {

        for (uint8_t i = startCard; i <= endCard; i++) {

            PD::drawBitmap(x, y, Images::Card_Back);
            x = x + 2;

        }

    }

}

void Game::renderDiscardDeck(int16_t x, int16_t y) { 

    int8_t endCard = this->deck.getIndex(DeckTypes::Discard) + 1;
    uint8_t startCard = endCard > 3 ? endCard - 3 : 0;

    if (endCard == 0) {

        PD::drawBitmap(x, y, Images::Card_Placeholder);

    }
    else {

        for (uint8_t i = startCard; i < endCard; i++) {

            Card card = this->deck.getCard(DeckTypes::Discard, i);
            this->renderCard(x, y, card, false);
            x = x + 2;

        }

    }

}

void Game::renderAttackButton(ButtonState state) {

    switch (state) {

        case ButtonState::Disabled:

            PD::drawBitmap(147, 150, Images::Button_Grey);
            PD::setCursor(168, 152);
            PD::setColor(5);
            PD::print("Attack");
            break;

        case ButtonState::Enabled:

            PD::drawBitmap(147, 150, Images::Button);
            PD::setCursor(168, 152);
            PD::setColor(7);
            PD::print("Attack");
            break;

        case ButtonState::Highlighted:

            PD::drawBitmap(147, 150, Images::Button_Highlight);
            PD::setCursor(168, 152);
            PD::setColor(7);
            PD::print("Attack");
            break;

    }

}

void Game::renderYieldButton(ButtonState state) {

    switch (state) {

        case ButtonState::Disabled:

            PD::drawBitmap(147, 164, Images::Button_Grey);
            PD::setCursor(168, 166);
            PD::setColor(5);
            PD::print("Yield");
            break;

        case ButtonState::Enabled:

            PD::drawBitmap(147, 164, Images::Button);
            PD::setCursor(168, 166);
            PD::setColor(7);
            PD::print("Yield");
            break;

        case ButtonState::Highlighted:

            PD::drawBitmap(147, 164, Images::Button_Highlight);
            PD::setCursor(168, 166);
            PD::setColor(7);
            PD::print("Yield");
            break;

    }

}
