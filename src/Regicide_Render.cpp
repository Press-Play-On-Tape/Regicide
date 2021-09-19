#include "Regicide.h"
#include "utils/Utils.h"

using PC = Pokitto::Core;
using PD = Pokitto::Display;


void Game::renderCard_Blank(int16_t x, int16_t y) { 

    PD::drawBitmap(x, y, Images::Card_Front_Normal_Half);

}

void Game::renderCard(int16_t x, int16_t y, Card &card, bool highlight, bool logo) { 

    PD::drawBitmap(x, y, highlight ? Images::Card_Front_Highlight : Images::Card_Front_Normal);

    PD::setColor(0, 14);

    switch (card.getNumber() % 13) {

        case 0:    
            PD::setCursor(x + 5, y + 4);
            PD::print("A");
            PD::drawBitmap(x + 28, y + 60, Images::LargeNumbers_Inverted[0]);
            PD::drawBitmap(x + 28, y + 48, Images::Suits_Coloured_Rot[static_cast<uint8_t>(card.getSuit())]);
            if (logo) PD::drawBitmap(x + 8, y + 23, Images::Logo);
            break;

        case 1 ... 8:    
            PD::setCursor(x + 5, y + 4);
            PD::print(static_cast<uint16_t>((card.getNumber() % 13) + 1));
            PD::drawBitmap(x + 28, y + 60, Images::LargeNumbers_Inverted[(card.getNumber() % 13) + 1]);
            PD::drawBitmap(x + 28, y + 48, Images::Suits_Coloured_Rot[static_cast<uint8_t>(card.getSuit())]);
            if (logo) PD::drawBitmap(x + 8, y + 23, Images::Logo);
            break;

        case 9:    
            PD::setCursor(x + 2, y + 4);
            PD::print("1");
            PD::setCursor(x + 7, y + 4);
            PD::print("0");
            PD::drawBitmap(x + 28, y + 60, Images::LargeNumbers_Inverted[10]);
            PD::drawBitmap(x + 28, y + 48, Images::Suits_Coloured_Rot[static_cast<uint8_t>(card.getSuit())]);
            if (logo) PD::drawBitmap(x + 8, y + 23, Images::Logo);
            break;

        case 10:    
            PD::setCursor(x + 4, y + 4);
            PD::print("J");
            PD::drawBitmap(x + 4, y + 7, Images::Jacks[static_cast<uint8_t>(card.getSuit())]);
            break;

        case 11:    
            PD::setCursor(x + 4, y + 4);
            PD::print("Q");
            PD::drawBitmap(x + 4, y + 7, Images::Queens[static_cast<uint8_t>(card.getSuit())]);
            break;

        case 12:    
            PD::setCursor(x + 4, y + 4);
            PD::print("K");
            PD::drawBitmap(x + 4, y + 7, Images::Kings[static_cast<uint8_t>(card.getSuit())]);
            break;


    }

    PD::drawBitmap(x + 3, y + 14, Images::Suits_Coloured[static_cast<uint8_t>(card.getSuit())]);


}


void Game::renderPlayerHand(uint8_t playerIdx, int16_t x, int16_t y, uint8_t selectedIndex, uint8_t cardsToSuppress) { 

    uint8_t spacing = 18;
    uint8_t offset = 0;
    bool drawSpacer = false;

    switch (this->hands[playerIdx].getCardIndex() - cardsToSuppress + 1) {

        case 1:
            offset = 72 - Constants::CardWidth_Half;
            break;

        case 2:
            offset = 72 - (Constants::CardWidth_Half + 9);
            break;

        case 3:
            offset = 72 - (Constants::CardWidth_Half + 18);
            break;

        case 4:
            offset = 72 - (Constants::CardWidth_Half + 27);
            break;

        case 5:
            offset = 72 - (Constants::CardWidth_Half + 36);
            break;

        case 6:
            offset = 72 - (Constants::CardWidth_Half + 45);
            break;

        case 7:
            offset = 2;
            spacing = 17;
            break;

        case 8:
            offset = 0;
            spacing = 15;
            break;

        case 9:
            offset = 0;
            spacing = 13;
            drawSpacer = true;
            break;

        case 10:
            offset = 0;
            spacing = 13;
            drawSpacer = true;
            break;

        case 11:
            offset = 0;
            spacing = 13;
            drawSpacer = true;
            break;


    }

    for (uint8_t i = 0; i <= this->hands[playerIdx].getCardIndex() - cardsToSuppress; i++) {

        Card card = this->hands[playerIdx].getCard(i);
        bool marked = this->hands[playerIdx].isMarked(i);

        this->renderCard(x + offset, y - (marked ? 10 : 0), card, i == selectedIndex, false);
        x = x + spacing;

    }

    if (drawSpacer) {
        PD::setColor(3);
        PD::drawFastVLine(146, 140, 40);
    }

}


void Game::renderCastleDeck(int16_t x, int16_t y, uint8_t numberOfCards, bool displayTopCard) { 

    uint8_t endCard = this->deck.getIndex(DeckTypes::Castle);
    uint8_t startCard = endCard > 3 ? endCard - 3 : 0;


    if (endCard == 0) {

        PD::drawBitmap(x + 2, y, Images::Card_Placeholder);
        x = x + 3;

    }
    else {

        for (uint8_t i = startCard; i <= endCard; i++) {

            if (i < endCard) {
                this->renderCard_Blank(x, y);
            }
            else if (!displayTopCard) {
                PD::drawBitmap(x, y, Images::Card_Back);
            }
            else {
                Card card = this->deck.getCard(DeckTypes::Castle, i);
                this->renderCard(x, y, card, false, false);
            }
            
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

void Game::renderDiscardDeck(int16_t x, int16_t y, uint8_t numberOfCards, bool displayTopCard) { 

    int8_t endCard = this->deck.getIndex(DeckTypes::Discard) + 1;
    uint8_t startCard = endCard > 3 ? endCard - 3 : 0;

    if (endCard == 0) {

        PD::drawBitmap(x + 2, y, Images::Card_Placeholder);
        x = x + 3;

    }
    else {

        for (uint8_t i = startCard; i < endCard; i++) {

            if (i < endCard - 1) {
                this->renderCard_Blank(x, y);
            }
            else {

                if (!displayTopCard) {
                    PD::drawBitmap(x, y, Images::Card_Back);
                }
                else {
                    Card card = this->deck.getCard(DeckTypes::Discard, i);
                    this->renderCard(x, y, card, false, true);
                }

            }
            
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

    selected = currentHand.getMarkedSuit(CardSuit::Spades) || this->deck.getShield();
    PD::drawBitmap(158, 139, selected ? Images::Suits_Coloured[static_cast<uint8_t>(CardSuit::Spades)] : Images::Suits_Disabled[static_cast<uint8_t>(CardSuit::Spades)]);
    PD::drawBitmap(170, 140, selected ? Images::Legend_Shield_Highlight : Images::Legend_Shield_Grey);

}

void Game::renderCaption(Caption caption) {

    this->renderCaption(caption, Caption::None);

}

void Game::renderCaption(Caption caption1, Caption caption2) {

    PD::setColor(0);

    if (caption2 == Caption::None) {
        PD::fillRect(1, 116, 145, 8);
    }
    else {
        PD::fillRect(1, 116, 145, 18);
    }

    PD::drawBitmap(2, 117, Images::Captions[static_cast<uint8_t>(caption1)]);

    if (caption2 != Caption::None) {
        PD::drawBitmap(2, 127, Images::Captions[static_cast<uint8_t>(caption2)]);
    }

}
