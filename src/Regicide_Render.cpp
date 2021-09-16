#include "Regicide.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderCard(int16_t x, int16_t y, Card &card, bool highlight) { 

    PD::drawBitmap(x, y, highlight ? Images::Card_Front_Highlight : Images::Card_Front_Normal);

    PD::setColor(0, 14);

    switch (card.getNumber() % 13) {

        case 0:    
            PD::setCursor(x + 5, y + 4);
            PD::print("A");
            break;

        case 1 ... 8:    
            PD::setCursor(x + 5, y + 4);
            PD::print(static_cast<uint16_t>((card.getNumber() % 13) + 1));
            PD::drawBitmap(x + 26, y + 64, Images::LargeNumbers_Inverted[(card.getNumber() % 13) + 1]);
            break;

        case 9:    
            PD::setCursor(x + 2, y + 4);
            PD::print("1");
            PD::setCursor(x + 7, y + 4);
            PD::print("0");
            PD::drawBitmap(x + 26, y + 64, Images::LargeNumbers_Inverted[10]);
            break;

        case 10:    
            PD::setCursor(x + 4, y + 4);
            PD::print("J");
            PD::drawBitmap(x + 4, y + 7, Images::Jacks[static_cast<uint8_t>(card.getSuit())]);
            break;

        case 11:    
            PD::setCursor(x + 4, y + 4);
            PD::print("Q");
            break;

        case 12:    
            PD::setCursor(x + 4, y + 4);
            PD::print("K");
            break;


    }

    PD::drawBitmap(x + 3, y + 14, Images::Suits_Coloured[static_cast<uint8_t>(card.getSuit())]);
    PD::drawBitmap(x + 26, y + 54, Images::Suits_Coloured[static_cast<uint8_t>(card.getSuit())], ROT180, FLIPV);


}


void Game::renderPlayerHand(uint8_t playerIdx, int16_t x, int16_t y, uint8_t selecteIndex, uint8_t cardsToSuppress) { 

    for (uint8_t i = 0; i <= this->hands[playerIdx].getCardIndex() - cardsToSuppress; i++) {

        Card card = this->hands[playerIdx].getCard(i);
        bool marked = this->hands[playerIdx].isMarked(i);

        this->renderCard(x, y - (marked ? 10 : 0), card, i == selecteIndex);
        x = x + 17;

    }

}


void Game::renderCastleDeck(int16_t x, int16_t y, uint8_t numberOfCards) { 

    uint8_t endCard = this->deck.getIndex(DeckTypes::Castle);
    uint8_t startCard = endCard > 3 ? endCard - 3 : 0;


    if (endCard == 0) {

        PD::drawBitmap(x + 2, y, Images::Card_Placeholder);
        x = x + 3;

    }
    else {

        for (uint8_t i = startCard; i <= endCard; i++) {

            Card card = this->deck.getCard(DeckTypes::Castle, i);
            this->renderCard(x, y, card, false);
            x = x + 2;

        }

    }

    this->renderCardCount(x, y, numberOfCards);

}


void Game::renderTavernDeck(int16_t x, int16_t y, uint8_t numberOfCards) { 

    uint8_t endCard = this->deck.getIndex(DeckTypes::Tavern);
    uint8_t startCard = endCard > 3 ? endCard - 3 : 0;

    if (endCard == 0) {

        PD::drawBitmap(x + 2, y, Images::Card_Placeholder);
        x = x + 3;

    }
    else {

        for (uint8_t i = startCard; i <= endCard; i++) {

            PD::drawBitmap(x, y, Images::Card_Back);
            x = x + 2;

        }

    }

    this->renderCardCount(x, y, numberOfCards);

}

void Game::renderDiscardDeck(int16_t x, int16_t y, uint8_t numberOfCards) { 

    int8_t endCard = this->deck.getIndex(DeckTypes::Discard) + 1;
    uint8_t startCard = endCard > 3 ? endCard - 3 : 0;

    if (endCard == 0) {

        PD::drawBitmap(x + 2, y, Images::Card_Placeholder);
        x = x + 3;

    }
    else {

        for (uint8_t i = startCard; i < endCard; i++) {

            Card card = this->deck.getCard(DeckTypes::Discard, i);
            this->renderCard(x, y, card, false);
            x = x + 2;

        }

    }

    this->renderCardCount(x, y, numberOfCards);

}

void Game::renderCardCount(int16_t x, int16_t y, uint8_t numberOfCards) {

    PD::drawBitmap(x + 32, y + 66, Images::Counter);
    x = x + 39;

    {
        uint8_t digits[3] = {};

        extractDigits(digits, numberOfCards);

        for (uint8_t i = 0; i < 2; ++i) {
            PD::drawBitmap(x, y + 68, Images::SmallNumbers[digits[i]]);
            x = x - 5;
        }

    }

}

void Game::renderAttackButton(ButtonState state) {

    PD::drawBitmap(152, 151, Images::Buttons_Attack[static_cast<uint8_t>(state)]);


}

void Game::renderYieldButton(ButtonState state) {

    PD::drawBitmap(152, 164, Images::Buttons_Yield[static_cast<uint8_t>(state)]);

}

void Game::renderLegend(Hand &currentHand) {

    PD::drawBitmap(151, 105, Images::LegendPanel);

    uint8_t selected = currentHand.getMarkedSuit(CardSuit::Hearts);
    PD::drawBitmap(158, 109, selected ? Images::Suits_Coloured[static_cast<uint8_t>(CardSuit::Hearts)] : Images::Suits_Disabled[static_cast<uint8_t>(CardSuit::Hearts)]);
    PD::drawBitmap(170, 110, selected ? Images::Legend_Heal_Highlight : Images::Legend_Heal_Grey);

    selected = currentHand.getMarkedSuit(CardSuit::Diamonds);
    PD::drawBitmap(158, 119, selected ? Images::Suits_Coloured[static_cast<uint8_t>(CardSuit::Diamonds)] : Images::Suits_Disabled[static_cast<uint8_t>(CardSuit::Diamonds)]);
    PD::drawBitmap(170, 120, selected ? Images::Legend_Draw_Highlight : Images::Legend_Draw_Grey);

    selected = currentHand.getMarkedSuit(CardSuit::Clubs);
    PD::drawBitmap(158, 129, selected ? Images::Suits_Coloured[static_cast<uint8_t>(CardSuit::Clubs)] : Images::Suits_Disabled[static_cast<uint8_t>(CardSuit::Clubs)]);
    PD::drawBitmap(170, 130, selected ? Images::Legend_Damage_Highlight : Images::Legend_Damage_Grey);

    selected = currentHand.getMarkedSuit(CardSuit::Spades);
    PD::drawBitmap(158, 139, selected ? Images::Suits_Coloured[static_cast<uint8_t>(CardSuit::Spades)] : Images::Suits_Disabled[static_cast<uint8_t>(CardSuit::Spades)]);
    PD::drawBitmap(170, 140, selected ? Images::Legend_Shield_Highlight : Images::Legend_Shield_Grey);

}
