#pragma once

#include "../utils/Enums.h"
#include "../utils/Utils.h"

struct Attack {

    private:

        uint8_t index;
        uint8_t x;
        uint8_t y;


    public: // Properties

        uint8_t getX()                      { return this->x; }
        uint8_t getY()                      { return this->y; }
        uint8_t getIndex()                  { return this->index; }

        void setX(uint8_t val)              { this->x = val; }
        void setY(uint8_t val)              { this->y = val; }
        void setIndex(uint8_t val)          { this->index = val; }


    public: // Properties

        void update() {

            if (this->index > 0) this->index--;
        }

};