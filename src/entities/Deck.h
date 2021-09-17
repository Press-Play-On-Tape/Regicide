#pragma once

#include "Card.h"
#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct Deck {

    private:

        bool shield = false;

        Card castleDeck[12];
        Card tavernDeck[42];
        Card discardDeck[42];
        GameMode mode = GameMode::TwoPlayers;

        int8_t tavernDeckCount = 40; // 40 two players, 41 three players, 42 four players
        int8_t tavernDeckIndex = 40;
        int8_t castleDeckIndex = 11;
        int8_t discardDeckIndex = -1;

    private:

        void shuffleCards(Card cards[], uint8_t startCard, uint8_t endCard) {

            for (uint8_t i = 0; i < (endCard - startCard) * 3; i++) {

                uint8_t rnd1 = random(startCard, endCard);
                uint8_t rnd2 = random(startCard, endCard);

                uint8_t tmp = cards[rnd1].getCardIndex();
                cards[rnd1].init(cards[rnd2].getCardIndex());
                cards[rnd2].init(tmp); 

            }

        } 

    public: // Properties

        bool getShield()                { return this->shield; }
        void setShield(bool val)        { this->shield = val; }

    public: // Methods

        Deck() { };

        void init(GameMode gameMode) {

            this->mode = gameMode;

            // Shuffle castle deck ..

            for (uint8_t i = 0; i < 4; i++) {

                this->castleDeck[i].init(12 + (i * 13), 20, 40); 
                this->castleDeck[i + 4].init(11 + (i * 13), 15, 30); 
                this->castleDeck[i + 8].init(10 + (i * 13), 10, 20); 

            }

            this->shuffleCards(this->castleDeck, 0, 4);
            this->shuffleCards(this->castleDeck, 4, 8);
            this->shuffleCards(this->castleDeck, 8, 12);


            // Shuffle tavern deck ..

            tavernDeckCount = 40;
            if (this->mode == GameMode::ThreePlayers)   this->tavernDeckCount = 41;
            if (this->mode == GameMode::FourPlayers)    this->tavernDeckCount = 42;
            
            for (uint8_t i = 0, j = 0; i < 52; i++) {

                if ((i % 13) < 10) {
                    this->tavernDeck[j].init(i); 
                    j++;
                }

            }

            this->tavernDeck[40].init(Cards::Joker);
            this->tavernDeck[41].init(Cards::Joker);

            this->castleDeckIndex = 11;
            this->tavernDeckIndex = this->tavernDeckCount -1;

            this->shuffleCards(this->tavernDeck, 0, this->tavernDeckCount);
            this->print();

        }

        void shuffleDiscardDeck() {

            this->shuffleCards(this->discardDeck, 0, this->discardDeckIndex + 1);

        }

        void dealCard(DeckTypes deck, Card &card) {

            switch (deck) {

                case DeckTypes::Castle:
                    card = this->castleDeck[this->castleDeckIndex];
                    card.print();
                    this->castleDeck[this->castleDeckIndex].init(Cards::NoCard);
                    this->castleDeckIndex--;
                    this->shield = false;
                    break;

                case DeckTypes::Tavern:
                    card = this->tavernDeck[this->tavernDeckIndex];
                    card.print();
                    this->tavernDeck[this->tavernDeckIndex].init(Cards::NoCard);
                    this->tavernDeckIndex--;
                    break;

                case DeckTypes::Discard:
                    card = this->discardDeck[this->discardDeckIndex];
                    card.print();
                    this->discardDeck[this->discardDeckIndex].init(Cards::NoCard);
                    this->discardDeckIndex--;
                    break;

            }
            
        }

        Card& getCard(DeckTypes deck, uint8_t index) {

            switch (deck) {

                case DeckTypes::Castle:
                    return this->castleDeck[index];

                case DeckTypes::Tavern:
                    return this->tavernDeck[index];

                default:
                    return this->discardDeck[index];

            }                    
            
        }

        int8_t getIndex(DeckTypes deck) {

            switch (deck) {

                case DeckTypes::Castle:
                    return this->castleDeckIndex;

                case DeckTypes::Tavern:
                    return this->tavernDeckIndex;

                default:
                    return this->discardDeckIndex;

            }              
            
        }

        void addCard(DeckTypes deck, Card card) {

            switch (deck) {

                case DeckTypes::Castle:
                    this->castleDeckIndex++;
                    this->castleDeck[this->castleDeckIndex].init(card.getCardIndex());
                    break;

                case DeckTypes::Tavern:
                    this->tavernDeckIndex++;
                    this->tavernDeck[this->tavernDeckIndex].init(card.getCardIndex());
                    break;

                case DeckTypes::Discard:
                    this->discardDeckIndex++;
                    this->discardDeck[this->discardDeckIndex].init(card.getCardIndex());
                    break;

            }

        }

        void addCardToBottom(DeckTypes deck, Card card) {

            switch (deck) {

                case DeckTypes::Castle:

                    for (int8_t i = this->castleDeckIndex; i >= 0; i--) {
                        this->castleDeck[i + 1].init(this->castleDeck[i].getCardIndex());
                    }
                    this->castleDeck[0].init(card.getCardIndex());
                    this->castleDeckIndex++;
                    break;

                case DeckTypes::Tavern:
                    for (int8_t i = this->tavernDeckIndex; i >= 0; i--) {
                        this->tavernDeck[i + 1].init(this->tavernDeck[i].getCardIndex());
                    }
                    this->tavernDeck[0].init(card.getCardIndex());
                    this->tavernDeckIndex++;
                    break;

                case DeckTypes::Discard:
                    for (int8_t i = this->discardDeckIndex; i >= 0; i--) {
                        this->discardDeck[i + 1].init(this->discardDeck[i].getCardIndex());
                    }
                    this->discardDeck[0].init(card.getCardIndex());
                    this->discardDeckIndex++;
                    break;

            }

        }

        void print() {

            #ifdef DEBUG
                
                printf("Castle Deck: ");

                for (uint8_t i = 0; i < 12; i++) {

                    this->castleDeck[i].print();
                    
                }

                printf("\n");

                printf("Tavern Deck: ");

                for (uint8_t i = 0; i < this->tavernDeckCount; i++) {

                    this->tavernDeck[i].print();
                    
                }

                printf("\n");

                printf("Discard Deck: ");

                for (uint8_t i = 0; i <= this->discardDeckIndex; i++) {

                    this->discardDeck[i].print();
                    
                }

                printf("\n");

            #endif
        }
        
};
