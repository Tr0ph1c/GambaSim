#pragma once

#define EVENT_GOODLUCK 1
#define EVENT_GUARANTEEDWIN 2
#define EVENT_LOWERALLIN 4
#define EVENT_BADLUCK 8
#define EVENT_HIGHRISK 16

#include "InventorySystem.h"
#include "Cases.h"

class Player {
    public:
    size_t day;
    float highscore; // highscore
    float winnings; // money used to gamble
    float luck; // multiplier on case win chance
    uint8_t event_flags;
    bool action_taken;

    Inventory inventory; // the player's inventory
    
    Player ();

    float DoRoll ();
    bool SellCase (const Case& _case);
    void OpenCase (const Case& _case);
    void BigGamba ();

    void OpenCaseOnIndex (int index);
    void SellCaseOnIndex (int index);
    void BuyCase ();

    void ClearEvents ();
    std::string PrintEvent ();
};
